#ifndef __pcargs_p_h__
#define __pcargs_p_h__
#ifdef __cplusplus
extern "C"
#endif


void
   ambe_close_files( PC_OPTIONS *a );
#ifdef __cplusplus
extern "C"
#endif

const short *
   ambe_get_user_qentry( void );
#ifdef __cplusplus
extern "C"
#endif


int
   ambe_read_args( PC_OPTIONS *a,
		   int	    argc,
		   char       *argv[]);
#endif /* __pcargs_p_h__ */
