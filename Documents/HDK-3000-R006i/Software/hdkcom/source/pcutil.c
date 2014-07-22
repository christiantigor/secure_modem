/******************************************************************************
 * DVSI CONFIDENTIAL PROPRIETARY
 ******************************************************************************
 * AMBE-3000 HDK
 * (c) Copyright, Digital Voice Systems Inc., 2008
 * All Rights Reserved
 *
 * DVSI claims certain rights, including patent rights under
 * U.S. Patents #6,199,037 B1, #6,161,089, #5,870,045, #5,826,222,
 * #5,754,974, #5,715,365, #5,701,390, #5,649,050, #5,630,011,
 * #5,247,579, and #5,226,084, and under other U.S. and foreign
 * patents and patents pending, in the AMBE^(TM) speech coding
 * technology embodied in this software.  Any use of this software
 * or technology requires a separate written license from DVSI.
 * 	
 * AMBE is a registered trademark of Digital Voice Systems, Inc.
 * AMBE+ and AMBE+2 are trademarks of Digital Voice Systems, Inc.
 ******************************************************************************/

#include "assert.h"
#include <stdio.h>
#include <string.h>
#include "pcutil.h"
#include "version.h"

/*
 * all I/O is in 16-bit words
 */
#define SIZEINT           2
#define SIZEBIT           1
#define PACKED_BITS_SZ  256 /* bytes */

 
static char cpyrt_str[] = 
"********************************************************\n"
" DVSI CONFIDENTIAL PROPRIETARY                          \n"
"                                                        \n"
" DVSI AMBE/AMBE+/AMBE+2 Speech Coder                    \n"
" %sVersion %s, %s                                       \n"
"                                                        \n"
" (C) Copyright, Digital Voice Systems, Inc., %s         \n"  
" All Rights Reserved                                    \n"
"                                                        \n"
" Notice: This software is protected by US and foreign   \n"
"         patents (including US #5,226,084, #5,247,579   \n"
"         #5,491,772, #5,517,511) and patents pending.   \n"
"         Any use of this software requires a seperate   \n"
"         written licence from DVSI.                     \n"
"                                                        \n"
" AMBE, AMBE+, and AMBE+2 are a trademarks of            \n"
" Digital Voice Systems, Inc.                            \n"
"********************************************************\n";

/******************************************************************************
 * Output the DVSI copyright notice.
 */

/*proto*/

void
DVSI_copyright( void )
{
	char copyrightrange[10] = __PRODORIGYEAR__; 
	/*
	 * the copyrightyear is the ORIGYEAR string if it is still the
	 * first year, otherwise it becomes a range of years.
	 */
	
	if( strcmp( __PRODORIGYEAR__, __DATE__+7 ) ) {
		strcat( copyrightrange, "-" );
		strcat( copyrightrange, __DATE__+7 );
	}
	
	printf( cpyrt_str, __PRODNAME__, __PRODVERSION__, __DATE__, copyrightrange );
}

/******************************************************************************
 * Read len speech samples from the input file fpi and put the samples
 * in buf.
 */
/*proto*/
short 
   get_speech( short      *buf,
	       short  nsamples,
	       FILE       *fpi,
	       short   compand )
{
	unsigned int n;

	/*
	 * if the input file is companded, then it is read as
	 * one byte per sample
	 */
	if (compand) {
		char cbuf[168];
		short i;
		n = (short) fread( cbuf, SIZEBIT, nsamples, fpi );	
		for ( i = 0; i < n; i++ )
			buf[i] = (short)cbuf[i];
	} else {
		n = fread( buf, SIZEINT, nsamples, fpi );
	}

	if ( n < (unsigned int) nsamples ) {
		short     i;
		short *pbuf = buf + n;

		for ( i = 0; i < (short)(nsamples-n); i++ )
			*pbuf++ = 0;
	}

	return( (short) n );
}



/******************************************************************************
 * Write len speech samples in buf to the output file fpo.
 */

/*proto*/
short 
   put_speech( const short      *buf,
	       short        nsamples,
	       FILE             *fpo,
	       short         compand )
{
	short n;

	/*
	 * if the output file is companded, then it is written out as
	 * one byte per sample
	 */
	if (compand) {
		char cbuf[168];
		short i;
		for ( i = 0; i < nsamples; i++ )
			cbuf[i] = (char)buf[i];
		n = (short) fwrite( cbuf, SIZEBIT, nsamples, fpo );
	} else {
		n = (short) fwrite( buf, SIZEINT, nsamples, fpo );
	}

	return ( n );
}


/******************************************************************************
 */
/*proto*/
short
put_bits( const short  *buf,
	  short       nbits,
	  FILE         *fpo )
{
	unsigned char cbuf[PACKED_BITS_SZ];
	short            i;

	for ( i = 0; i < nbits; i++ ) {
		cbuf[i] = (unsigned char) buf[i];
	}

	return fwrite( cbuf, SIZEBIT, nbits, fpo );
}

/******************************************************************************
 */
/*proto*/
short
get_bits( short          *buf,
	  short         nbits,
	  FILE           *fpi )
{
	unsigned char cbuf[PACKED_BITS_SZ];
	short            i;
	short   nbits_read;

	nbits_read = fread( cbuf, SIZEBIT, nbits, fpi );

	for ( i = 0; i < nbits_read; i++ )
		buf[i] = (short) cbuf[i];

	for ( /* i = nbits_read */; i < nbits; i++ )
		buf[i] = 0;

	return nbits_read;
}






#if 0
/******************************************************************************
 * take the bits in cbuf (8 bits per byte) and unpack them into 
 * sbuf (1 bit per word).
 */

static void
   unpack_bits( short                 *sbuf,  /* unpacked bit buffer (1 bit per word)   */
		const unsigned char   *cbuf,  /* packed bit buffer (8 bits per word)    */
		short               cbuf_sz ) /* size of cbuf in bytes                  */
{
	short   *s;
	short    i;

	s = sbuf;

	for ( i = 0; i < cbuf_sz; i++ ) {

		unsigned char c = cbuf[i];
		short         j;

		s += 8-1;

		for ( j = 0; j < 8; j++ ) {
			*s--   = c & 1;
			c    >>= 1;
		}

		s += 8+1; /* pointer to NEXT bit */
	}
}

/******************************************************************************
 */

/*proto*/
short
   get_packed_bits( short    *buf,
		    short   nbits,
		    short sd_bits,
		    FILE     *fpi )
{
	unsigned char   cbuf[PACKED_BITS_SZ];
	short         nbytes;
	short              n;

	/*
	 * if the number of soft decision bits is not one, don't pack
	 * the buffer.
	 */
	nbytes = (sd_bits > 1) ? nbits : (nbits >> 3);

	n      = fread( cbuf, SIZEBIT, nbytes, fpi );

	if ( n < 0 ) 
		n = 0;

	if ( n < nbytes ) {
		short i;
		for ( i = n; i < nbytes; i++ )
			cbuf[i] = 0;
	}

	if ( sd_bits > 1 ) {
		short i;
		for ( i = 0; i < nbytes; i++ ) 
			buf[i] = cbuf[i];

	} else
		unpack_bits( buf, cbuf, nbytes );

	return (n == 0) ? 0 : nbits;
}

/******************************************************************************
 */

static void
   pack_bits( unsigned char   *cbuf,  /* packed bit buffer (8 bits per word)    */
	      const short     *sbuf,  /* unpacked bit buffer (1 bit per word)   */
	      short         sbuf_sz ) /* size of sbuf in words (number of bits) */
{
	const short     *s;
	short        nbits;
	short       nbytes;
	short            i;

	nbits  = sbuf_sz;
	nbytes = (nbits >> 3);
	s      = sbuf;

	for ( i = 0; i < nbytes; i++ ) {
		short         j;
		unsigned char v = 0;

		for ( j = 0; j < 8; j++ ) {
			v <<= 1;
			v  += *s++;
		}

		cbuf[i] = v;
	}
}

/******************************************************************************
 */

/*proto*/
short
   put_packed_bits( const short    *buf,
		    short         nbits,
		    short       sd_bits,
		    FILE           *fpo )
{
	unsigned char   cbuf[PACKED_BITS_SZ];
	short         nbytes;
	short              n;

	if ( sd_bits > 1 ) {
		short i;

		nbytes = nbits;

		for ( i = 0; i < nbits; i++ )
			cbuf[i] = (unsigned char) buf[i];

	} else {

		nbytes = (nbits >> 3);

		pack_bits( cbuf, buf, nbits );
	}

	n = (short) fwrite( cbuf, SIZEBIT, nbytes, fpo );

	return ( nbits );
}

#else





/******************************************************************************
 */

/*proto*/
short
   get_packed_bits( short    *buf,
		    short   nbits,
		    short sd_bits,
		    FILE     *fpi )
{
	unsigned char   cbuf[PACKED_BITS_SZ];
	short         nbytes = 0;
	short              n;
	short  bits_per_byte;
	short mask = (1<<sd_bits)-1;
	short i;
	short total;

	if (sd_bits == 1) {
		bits_per_byte = 8;
	} else {
		bits_per_byte = 2;
	}

	/*
	 * first figure out how many bytes we need to read from the
	 * file.
	 */
	total = 0;
	while (total < nbits) {
		total += bits_per_byte;
		nbytes++;
	}

	ASSERT( nbytes <= PACKED_BITS_SZ );

	n      = fread( cbuf, SIZEBIT, nbytes, fpi );

	if ( n < 0 ) 
		n = 0;

	if ( n < nbytes ) {
		for ( i = n; i < nbytes; i++ )
			cbuf[i] = 0;
	}

	for ( i = 0; i < nbytes; i++ ) {
		unsigned char v = cbuf[i];
		short j;
		for ( j = bits_per_byte-1; j >= 0; j-- ) {
			buf[j] = v & mask;
			v >>= sd_bits;
		}
		buf += bits_per_byte;
	}

	if ( n < nbytes )
		return bits_per_byte*n;
	else
		return nbits;
}

/******************************************************************************
 */

/*proto*/
short
   put_packed_bits( const short    *buf,
		    short         nbits,
		    short       sd_bits,
		    FILE           *fpo )
{
	unsigned char   cbuf[PACKED_BITS_SZ];
	short         nbytes = 0;
	short              n;
	short  bits_per_byte;

	/*
	 * coming in the bits are not packed and we have to pack them
	 * first.  This code currently only handles sd_bits=1 or
	 * sd_bits=4
	 */

	if (sd_bits == 1) {
		bits_per_byte = 8;
	} else {
		bits_per_byte = 2;
	}

	while (nbits > 0) {
		unsigned char v = 0;
		short j;
		for ( j = 0; j < bits_per_byte; j++ ) {
			v <<= sd_bits;
			if (nbits > 0) {
				v += *buf++;
				nbits--;
			}
		}
		cbuf[nbytes] = v;
		nbytes++;
	}

	n = (short) fwrite( cbuf, SIZEBIT, nbytes, fpo );

	ASSERT( n == nbytes );

	return ( nbits );
}










#endif