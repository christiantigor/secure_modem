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

#ifndef __parse_p_h__
#define __parse_p_h__
#ifdef __cplusplus
extern "C"
#endif


int
get_word( const char    *s,
	  const char **ptr,
	  char          *t,
	  int         tlen );
#ifdef __cplusplus
extern "C"
#endif


int
valid_ulong( char             *s,
	     char          **ptr,
	     int            base,
	     unsigned long    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_long( char    *s,
	    char **ptr,
	    int   base,
	    long    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_int( char    *s,
	   char **ptr,
	   int   base,
	   int     *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_uint( char            *s,
	    char         **ptr,
	    int           base,
	    unsigned int    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_short( char     *s,
	     char  **ptr,
	     int    base,
	     short    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_ushort( char              *s,
	      char           **ptr,
	      int             base,
	      unsigned short    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_char( char    *s,
	    char **ptr,
	    int   base,
	    char    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_uchar( char             *s,
	     char          **ptr,
	     int            base,
	     unsigned char    *i );
#ifdef __cplusplus
extern "C"
#endif


int
valid_double( char      *s,
	      char   **ptr,
	      double    *f );
#ifdef __cplusplus
extern "C"
#endif


int
valid_float( char     *s,
	     char  **ptr,
	     float    *f );
#endif /* __parse_p_h__ */
