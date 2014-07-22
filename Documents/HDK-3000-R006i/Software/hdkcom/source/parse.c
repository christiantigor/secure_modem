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
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <ctype.h>

#include "parse.h"

/******************************************************************************
 * skip white space and return the next "word".  a word is a contiguous set of
 * characters without any white space.
 */
/*proto*/

int
get_word( const char    *s,
	  const char **ptr,
	  char          *t,
	  int         tlen )
{
	const char     *es;
	char           *et;
	int        wordlen;

	ASSERT( s );
	ASSERT( t );
	ASSERT( tlen > 0 );

	es = s;
	while ( *es && isspace(*es) )
		es++;

	wordlen = 0;
	et      = t;
	while ( *es && !isspace(*es) ) {
		wordlen++;
		if ( wordlen >= tlen )
			break;

		*et++ = *es++;
	}
	*et = 0; /* null terminate */

	if ( ptr )
		*ptr = es;

	return ( ((*t == 0) || (wordlen >= tlen)) ? 0 : 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_ulong( char             *s,
	     char          **ptr,
	     int            base,
	     unsigned long    *i )
{
	char          *es;
	unsigned long val = strtoul( s, &es, base );
	
	if ( es == s )
		return ( 0 );
	
	*i = val;
	
	if ( ptr )
		*ptr = es;

	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_long( char    *s,
	    char **ptr,
	    int   base,
	    long    *i )
{
	char *es;
	long val = strtoul( s, &es, base );
	
	if ( es == s )
		return ( 0 );
	
	*i = val;

	if ( ptr )
		*ptr = es;

	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_int( char    *s,
	   char **ptr,
	   int   base,
	   int     *i )
{
	long val;

	if ( !valid_long(s,ptr,base,&val) )
		return ( 0 );

	/*
	 * check the unsigned value on the positive side to catch negative values
	 * specified in hex, etc.
	 */
	if ( (val < INT_MIN) || (val > UINT_MAX) )
		return ( 0 );
	
	*i = (int) val;
	
	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_uint( char            *s,
	    char         **ptr,
	    int           base,
	    unsigned int    *i )
{
	unsigned long val;

	if ( !valid_ulong(s,ptr,base,&val) )
		return ( 0 );
	
	if ( val > UINT_MAX )
		return ( 0 );
	
	*i = (unsigned int) val;
	
	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_short( char     *s,
	     char  **ptr,
	     int    base,
	     short    *i )
{
	long val;
	
	if ( !valid_long(s,ptr,base,&val) )
		return ( 0 );
	
	/*
	 * check the unsigned value on the positive side to catch negative values
	 * specified in hex, etc.
	 */
	if ( (val < SHRT_MIN) || (val > USHRT_MAX) )
		return ( 0 );
	
	*i = (short) val;
	
	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_ushort( char              *s,
	      char           **ptr,
	      int             base,
	      unsigned short    *i )
{
	unsigned long val;
	
	if ( !valid_ulong(s,ptr,base,&val) )
		return ( 0 );
	
	if ( val > USHRT_MAX )
		return ( 0 );
	
	*i = (unsigned short) val;
	
	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_char( char    *s,
	    char **ptr,
	    int   base,
	    char    *i )
{
	long val;
	
	if ( !valid_long(s,ptr,base,&val) )
		return ( 0 );
	
	/*
	 * check the unsigned value on the positive side to catch negative values
	 * specified in hex, etc.
	 */
	if ( (val < CHAR_MIN) || (val > UCHAR_MAX) )
		return ( 0 );
	
	*i = (char) val;
	
	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_uchar( char             *s,
	     char          **ptr,
	     int            base,
	     unsigned char    *i )
{
	unsigned long val;
	
	if ( !valid_ulong(s,ptr,base,&val) )
		return ( 0 );
	
	if ( val > UCHAR_MAX )
		return ( 0 );
	
	*i = (unsigned char) val;
	
	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_double( char      *s,
	      char   **ptr,
	      double    *f )
{
	char   *es;
	double val = strtod( s, &es );
	
	if ( es == s )
		return ( 0 );
	
	*f = val;
	
	if ( ptr )
		*ptr = es;

	return ( 1 );
}

/******************************************************************************
 */
/*proto*/

int
valid_float( char     *s,
	     char  **ptr,
	     float    *f )
{
	double val;

	if ( !valid_double(s,ptr,&val) )
		return ( 0 );

	if ( val != 0.0 ) {
		double abs_val = (val < 0.0) ? -val : val;
		if ( (abs_val < FLT_MIN) || (abs_val > FLT_MAX) )
			return ( 0 );
	}

	*f = (float) val;

	return ( 1 );
}

/*****************************************************************************/
