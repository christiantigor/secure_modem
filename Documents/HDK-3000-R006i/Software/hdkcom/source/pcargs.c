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

#define AMBE_ALLOW_NATIVE_TYPES

#include "assert.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdkpacket.h"
#include "parse.h"
#include "pcargs.h"

/******************************************************************************
 * Open the input and output encoder/decoder files in the options structure.
 */

static void
   open_files( PC_OPTIONS *a )
{
	if ( a->fpi_name && *a->fpi_name ) {
		if ( (a->fpi = fopen(a->fpi_name,"rb")) == (FILE *) 0 ) {
			fprintf( stderr, "Can't open input data file %s\n",
				 a->fpi_name );
			exit(1);
		}
	}

	if ( a->fpo_name && *a->fpo_name ) {
		if ( (a->fpo = fopen(a->fpo_name,"wb")) == (FILE *) 0 ) {
			fprintf( stderr, "Can't open output data file %s\n",
				 a->fpo_name );
			exit(1);
		}
	}

}

/******************************************************************************
 * Open the input and output encoder/decoder files in the options structure.
 */

/*proto*/

void
   ambe_close_files( PC_OPTIONS *a )
{

	if (a->fpi)
		fclose( a->fpi );
	if (a->fpo)
		fclose( a->fpo );
}

/******************************************************************************
 * allow compressed rate specifications
 */

static short qentry[6];

static int
   ambe_read_rate( short      *rate,
		   int         argc,
		   char       *argv[] )
{
	int r;
	int i = 0;

	if ( (i >= argc) || !valid_int(argv[i],0,0,&r) ) {
		*rate = -1;
		goto return_args_used;
	}

	if ( (argv[i][0] == '0') && (argv[i][1] == 'x') ) {
		/*
		 * if rate is in hex, assume the rate arg is a compress qtable entry
		 */
		qentry[i] = (short) r;

		for ( i = 1; i < 6; i++ ) {
			if ( (i >= argc) || !valid_int(argv[i],0,0,&r) ) {
				*rate = -1;
				goto return_args_used;
			} else {
				qentry[i] = (short) r;
			}
		}

		*rate = 64; /* special user-specified number */
		i--;        /* return no of args use minus one */

	} else {
		/*
		 * assume the rate is valid
		 */
		*rate = (short) r;
	}

return_args_used:
	return i;
}

/*proto*/
const short *
   ambe_get_user_qentry( void )
{
	return qentry;
}

/******************************************************************************
 * Parse the arguments in argv and initialize the options structure 
 * appropriately.
 */

/*proto*/

int
   ambe_read_args( PC_OPTIONS *a,
		   int	    argc,
		   char       *argv[])
{
	int i;

	/*
	 * set default options here
	 */
	a->enc_ws_rseed = 1234;
	a->dec_ws_rseed = 1234;

#define ARG_IS(str) !strcmp(str,argv[i])

#define CHK_ARG( chk_fn, result, errstr )			\
								if ( (i >= argc) || !chk_fn(argv[i],0,0,&(result)) ) {	\
								printf( errstr );				\
								goto return_error;				\
								}

	i = 1;
	while ( i < argc ) {


		if ( ARG_IS("-enc") ) {

			a->run_encoder = 1;
			a->run_decoder = 0;

		} else if ( ARG_IS("-dec") ) {

			a->run_encoder = 0;
			a->run_decoder = 1;

		} else if ( ARG_IS("-decsd") ) {

			a->run_encoder = 0;
			a->run_decoder = 1;
			a->sd_bits = 4;
			
		} else if ( ARG_IS("-encdec") ) {

			a->run_encoder = 1;
			a->run_decoder = 1;

		} else if (ARG_IS("-playrecord")) {

			a->codec = 1;
			a->play = 1;
			a->record = 1;
			
		} else if (ARG_IS("-play")) {

			a->codec = 1;
			a->play = 1;
			
		} else if (ARG_IS("-playsd")) {

			a->codec = 1;
			a->play = 1;
			a->sd_bits = 4;
			
		} else if (ARG_IS("-record")) {
			long seconds;

			i++;
			a->codec = 1;
			a->record = 1;
			CHK_ARG( valid_long, seconds,
				 "Invalid value specified for codecrecord seconds\n" )

			a->seconds = seconds;
			
		} else if (ARG_IS("-passthru")) {
			/*
			 * passthru can be combined with -play,
			 * -record, -playrecord.  -passthru can
			 * also be combined with -mode loopback
			 */
			a->passthru = 1;
		} else if (ARG_IS("-a3kdirect")) {
			/*
			 * -a3kdirect flag is used to tell hdkcom
			 * to talk directly to the a3k via P1,
			 * rather than to have packets relayed
			 * from the MSP to the a3k (via either
			 * uart or PPT).  Since in a3kdirect
			 * mode, none of the packets go to the
			 * MSP, the mode of the hdk board can not
			 * be changed.  The mode of the hdk
			 * board should always be a3kdirect, when
			 * this command line switch is used.
			 */
			a->a3kdirect = 1;

		} else if (ARG_IS("-mode")) {
			long hdkmode;
			i++;
			a->sendhdkmode = 1;

			if (ARG_IS("idle")) {
				hdkmode = HDKMODE_IDLE;
			} else if (ARG_IS("codec")) {
				hdkmode = HDKMODE(CODEC_MODE, a->packetif, a->passthru, SKEW_OFF, ECHO_OFF);
			} else if (ARG_IS("packet")) {
				hdkmode = HDKMODE(PACKET_MODE, a->packetif, PASSTHRU_OFF, SKEW_OFF, ECHO_OFF);
			} else if (ARG_IS("loopback")) {
				hdkmode = HDKMODE(LOOPBACK_MODE, a->packetif, a->passthru, SKEW_OFF, ECHO_OFF);
			} else if (ARG_IS("dualhdk")) {
				hdkmode = HDKMODE_DUALHDK;
			} else if (ARG_IS("dualhdkskew")) {
				hdkmode = HDKMODE_DUALHDKSKEW;
			} else if (ARG_IS("a3kdirect")) {
				hdkmode = HDKMODE_DSPUART;
			} else {
				CHK_ARG( valid_long, hdkmode,
				 "Invalid value specified for hdkmode\n" )
			}
			
			a->hdkmode = hdkmode;
			a->run_encoder = 0;
			a->run_decoder = 0;
			
#define PACKET_UART	0
#define PACKET_PPT	1
#define PACKET_MCBSP	2
		} else if (ARG_IS("-ppt")) {

			a->packetif = PACKET_PPT;

		} else if (ARG_IS("-uart")) {

			a->packetif = PACKET_UART;
			
		} else if (ARG_IS("-lowpower")) {

			a->lowpower = 1;
				     
		} else if ( ARG_IS("-r") ) {

			i++;

			if ( i >= argc ) {
				goto return_error;
			} else {

				i += ambe_read_rate( &a->rate, argc - i, argv + i );

				if ( a->rate < 0 ) {
					printf( "Invalid vocoder rate.\n" );
					goto return_error;
				}
			}

		} else if ( ARG_IS("-elen") ) {

			i++;

			if ( i >= argc ) {
				goto return_error;
			} else if ( ARG_IS("random") ) {
				a->enc_ws = -1;
			} else {
				long len;

				CHK_ARG( valid_long, len,
					 "Invalid encoder speech length.\n" )

						a->enc_ws = (short) len;
			}

		} else if ( ARG_IS("-dlen") ) {

			i++;

			if ( i >= argc ) {
				goto return_error;
			} else if ( ARG_IS("random") ) {
				a->dec_ws = -1;
			} else {
				long len;

				CHK_ARG( valid_long, len,
					 "Invalid decoder speech length.\n" )

						a->dec_ws = (short) len;
			}

		} else if ( ARG_IS("-fec") ) {

			int sd_dist;
			int hd_errs;

			i++;
			CHK_ARG( valid_int, sd_dist, "Invalid soft decision repeat distance.\n" )

					a->sd_dist = (short) sd_dist;

			i++;
			CHK_ARG( valid_int, hd_errs, "Invalid hard decision repeat distance.\n" )

					a->hd_errs = (short) hd_errs;

		} else if ( ARG_IS("-vad") ) {

			long lvl;

			i++;
			CHK_ARG( valid_long, lvl, "Invalid vad level.\n" );

			a->vad_level = (short) lvl;

		} else if ( ARG_IS("-ns") ) {

			i++;

			if ( ARG_IS("1") ) 
				a->nsprsn_enabled = 1;
			else if ( ARG_IS("0") )
				a->nsprsn_enabled = 0;
			else {
				a->nsprsn_enabled = 1;
				i--;
			}


		} else if ( ARG_IS("-tone_det_off") ) {

			a->tone_det_enabled = 0;

		} else if ( ARG_IS("-ec") ) {

			a->echo_canceller_enabled = 1;

		} else if ( ARG_IS("-tone") ) {

			long amp;
			long idx;

			i++;
			CHK_ARG( valid_long, idx, "Invalid tone index.\n" );

			a->tone_index = (short) idx;

			i++;
			CHK_ARG( valid_long, amp,
				 "Invalid tone amplitude.\n" );

			a->tone_amp = (short) amp;

			a->tone_on    = 1;


		} else if ( ARG_IS("-sdbits") ) {

			long sdbits;

			i++;
			CHK_ARG( valid_long, sdbits,
				 "Invalid soft decision size.\n" );

			a->sd_bits = (short) sdbits;

		} else if ( ARG_IS("-dtx") ) {

			int dtx;

			i++;
			CHK_ARG( valid_int, dtx,
				 "Invalid dtx value.\n" );

			a->dtx = (short) dtx;

		} else if ( ARG_IS("-port") ) {

			long baudrate;

			i++;

			a->comport_name = argv[i];

			i++;
			CHK_ARG( valid_long, baudrate,
				 "Invalid COM port baud rate.\n" );

			a->comport_baudrate = baudrate;


		} else if ( ARG_IS("-ulaw") ) {

			a->compand = ARGS_COMPAND_ULAW;

		} else if ( ARG_IS("-alaw") ) {

			a->compand = ARGS_COMPAND_ALAW;
			
		} else if ( ARG_IS("-delay0") ) {

			a->delayed_read_packets = 0;

		} else if ( ARG_IS("-delay1") ) {

			a->delayed_read_packets = 1;

		} else if ( ARG_IS("-version") ) {

			a->getversion = 1;

		} else if ( ARG_IS("-vv") ) {

			a->verbose = 2;

		} else if ( ARG_IS("-v") ) {

			a->verbose = 1;
			
		} else if ( ARG_IS("-q") ) {

			a->verbose = -1;

		} else if (ARG_IS("-w") ) {

			a->waitkey = 1;
			
		} else {
			short input_file_expected;
			short output_file_expected;

			if ((!a->codec)|| (a->play))
				input_file_expected = 1;
			else
				input_file_expected = 0;

			if ((!a->codec)|| (a->record))
				output_file_expected = 1;
			else
				output_file_expected = 0;
		
			if ( argv[i][0] == '-' ) {
				goto return_error;

			} else if (( a->fpi_name == NULL ) && (input_file_expected)) {
				a->fpi_name = argv[i];

			} else if (( a->fpo_name == NULL ) && (output_file_expected)) {
				a->fpo_name = argv[i];

			} else
				goto return_error;
		}

		i++;
	}

	open_files( a );

	return ( 0 );

return_error:
	return ( -1 );
}

/*****************************************************************************/
