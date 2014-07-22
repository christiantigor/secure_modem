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

/*
 * Flags for cmode
 */
#define DTMF_FRAME_FLAG			(1 << 15)	// 1=dtmf was detected or received
#define DTMF_SEND_FLAG			(1 << 14)	// 1=forces tone to be transmitted or synthesized
#define ECHO_CANCEL_ENABLE_FLAG		(1<<13)		//1=enables echo cancller
#define TONE_DET_ENABLE_FLAG		(1 << 12)	// 1=enables tone detection in encoder
#define DTX_ENABLE_FLAG			(1 << 11)       // 1=enables silence frames in encoder
#define VAD_FLAG			(1 << 10)
#define ECHO_SUPPRESS_ENABLE_FLAG	(1<<9)		//1=enables echo suppressor
#define COMPAND_ENABLE_FLAG		(1<<8)		//1=enables companding
#define COMPAND_SELECT_FLAG		(1<<7)		//0=u-law,1=a-law
#define NS_ENABLE_FLAG			(1 <<  6)	// 1=enables noise suppression in encoder
#define DATA_INVALID_FLAG		(1 <<  5)
#define RESERVE04_FLAG			(1 <<  4)
#define CNI_FRAME_FLAG			(1 <<  3)
#define LOST_FRAME_FLAG			(1 <<  2)
#define VOICE_ACTIVE_FLAG		(1 <<  1)
#define CMODE_RSRV0_FLAG		(1 <<  0)


