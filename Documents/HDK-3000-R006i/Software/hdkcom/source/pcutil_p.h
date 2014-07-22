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

#ifndef __pcutil_p_h__
#define __pcutil_p_h__
#ifdef __cplusplus
extern "C"
#endif


void
DVSI_copyright( void );
#ifdef __cplusplus
extern "C"
#endif

short 
   get_speech( short      *buf,
	       short  nsamples,
	       FILE       *fpi,
	       short   compand );
#ifdef __cplusplus
extern "C"
#endif

short 
   put_speech( const short      *buf,
	       short        nsamples,
	       FILE             *fpo,
	       short         compand );
#ifdef __cplusplus
extern "C"
#endif

short
put_bits( const short  *buf,
	  short       nbits,
	  FILE         *fpo );
#ifdef __cplusplus
extern "C"
#endif

short
get_bits( short          *buf,
	  short         nbits,
	  FILE           *fpi );
#ifdef __cplusplus
extern "C"
#endif

short
   get_packed_bits( short    *buf,
		    short   nbits,
		    short sd_bits,
		    FILE     *fpi );
#ifdef __cplusplus
extern "C"
#endif

short
   put_packed_bits( const short    *buf,
		    short         nbits,
		    short       sd_bits,
		    FILE           *fpo );

#endif /* __pcutil_p_h__ */
