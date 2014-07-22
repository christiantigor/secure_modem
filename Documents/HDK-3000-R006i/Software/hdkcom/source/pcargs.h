#ifndef _PCARGS_H_
#define _PCARGS_H_

#include "comport.h"

/******************************************************************************
 * DVSI CONFIDENTIAL PROPRIETARY
 ******************************************************************************
 * DVSI AMBE+2^(TM) Speech Coder
 * (c) Copyright, Digital Voice Systems Inc., 2002
 * All Rights Reserved
 *
 * DVSI claims certain rights, including patent rights under
 * U.S. Patents #5,226,084, #5,247,579, #5,491,772, #5,517,511 
 * and under other U.S. and foreign patents pending, in the 
 * AMBE+2^(TM) speech coding technology embodied in this software.  
 * Any use of this software or technology requires a separate 
 * written license from DVSI.
 * 	
 * AMBE is a trademark of Digital Voice Systems, Inc.
 ******************************************************************************
 *****************************************************************************/


struct pc_options_ref {
	short verbose;          /* TRUE = verbose output                */
	short run_encoder;      /* TRUE = run the encoder               */
	short run_decoder;      /* TRUE = run the decoder               */
	short rate;             /* vocoder rate                         */
	short enc_ws;           /* encoder speech input length          */
	short enc_ws_rseed;     /* seed for random enc_len              */
	short dec_ws;           /* decoder speech output length         */
	short dec_ws_rseed;     /* seed for random dec_len              */
	short vad_level;        /* voice detection level in dBm0        */
	short nsprsn_enabled;   /* enable noise suppression? 1=yes 0=no */
	short tone_det_enabled; /* TRUE = tone detection enabled        */
	short tone_on;          /* TRUE = generate a tone               */
	short tone_amp;         /* tone amplitude                       */
 	short tone_index;       /* tone index                           */
	short sd_bits;          /* number of soft decision bits         */
	short sd_dist;          /* soft decision repeat threshold       */
	short hd_errs;          /* hard decision repeat threshold       */
	short dtx;		/* use DTX, specify cni update period	*/
	short echo_canceller_enabled;
	short compand;		//0=linear,1=u-law,2=undefined,3=A-law
	short delayed_read_packets;
	short play;
	short record;
	short codec;
	short passthru;
	short seconds;
	short packetif;
	short hdkmode;
	short sendhdkmode;
	short lowpower;
	short waitkey;
	short getversion;
	short a3kdirect;
	char *comport_name;	/* COM port to open (example="COM4")	*/
	long comport_baudrate;
	CommPortClass *comPort;
	
	char  *fpi_name;        /* input data file name                 */
	FILE  *fpi;		/* data input file                      */
	char  *fpo_name;        /* output data file name                */
	FILE  *fpo;		/* data output file                     */
};

/*
 * note that if bit 0 is 1, then companding is selected and the type
 * of companding is specified by bit 1
 */
#define ARGS_COMPAND_LINEAR	0
#define ARGS_COMPAND_ULAW	1
#define ARGS_COMPAND_ALAW	3

typedef struct pc_options_ref PC_OPTIONS;

extern char ambe_usagestr[];

#include "pcargs_p.h"

/*****************************************************************************/
#endif
