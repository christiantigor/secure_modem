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
 * packet types:
 */
#define PKT_CONTROL	0
#define PKT_CHANNEL	1
#define PKT_SPEECH	2

/*
 * many control packet fields send either PKT_RESPONSE_OK or
 * PKT_RESPONSE_ERROR as a response.
 */
#define PKT_RESPONSE_OK		0
#define PKT_RESPONSE_ERROR	1

#define PKT_INIT_ENCODER	0x0001
#define PKT_INIT_DECODER	0x0002
#define PKT_INIT_ECHO		0x0004


#define PKT_SPEECHD		0x00
#define PKT_CHAND		0x01
#define PKT_CMODE		0x02
#define PKT_WS			0x03
#define PKT_TIME		0x04
#define PKT_ECMODE		0x05
#define PKT_DCMODE		0x06
#define PKT_PKTNUM		0x07
#define PKT_TONE		0x08
#define PKT_RATET		0x09
#define PKT_RATEP		0x0a
#define PKT_INIT		0x0b
#define PKT_SDBITS		0x0c
#define PKT_FASTMODE		0x0d
#define PKT_FLASHCONFIG		0x0e
#define PKT_ROMWAIT		0x0f
#define PKT_LOWPOWER		0x10
#define NOTUSED0		0x11
#define NOTUSED1		0x12
#define PKT_EDELAY		0x13
#define PKT_DDELAY		0x14
#define PKT_ENCOUT_FORMAT	0x15
#define PKT_DECOUT_FORMAT	0x16
#define PKT_CHAND4		0x17
#define NOTUSED2		0x18
#define PKT_VADLEVEL		0x19
#define PKT_ERRTHRESH		0x1a
#define PKT_ETIME		0x1b
#define PKT_DTIME		0x1c
#define PKT_EWS			0x1d
#define PKT_DWS			0x1e
#define PKT_PLLCONFIG		0x1f
#define NOTUSED3		0x20
#define NOTUSED4		0x21
#define NOTUSED5		0x22
#define NOTUSED6		0x23
#define PKT_IDLE		0x24
#define PKT_STANDBY		0x25
#define PKT_CONFIG		0x26
#define PKT_LSPCLKCONFIG	0x27
#define NOTUSED7		0x28
#define PKT_CUSTOMCONTROL	0x29
#define PKT_STARTCODEC		0x2a	//sets a3k config to codec mode, configures codec hardware, starts up codec software, enables codec interrupt
#define PKT_STOPCODEC		0x2b	//sets a3k config to packet mode, disables codec interrupt
#define NOTUSED8		0x2c
#define PKT_TESTPUT		0x2d	//PKT_TESTPUT/mode/len/data sets test mode to "mode" then writes len words of test init data
#define PKT_TESTGET		0x2e	//PKT_TESTGET/mode/len sets test mode to "mode" then reads len words of test data for response
#define PKT_PARITYBYTE		0x2f
#define PKT_PRODID		0x30
#define PKT_VERSTRING		0x31
#define PKT_COMPAND		0x32	//specify linear(=0), u-law(=1), or a-law(=3)
#define PKT_RESET		0x33
#define PKT_RESETSOFTCFG	0x34
#define PKT_HALT		0x35
#define PKT_GETCFG		0x36	//responds with current reading from config pins
#define PKT_READCFG		0x37	//rereads the config pins and puts them in response
#define PKT_CODECCFG		0x38	//tell a3k how to configure the codec
#define PKT_READY		0x39	//a3k tells user that reset is complete, ready to receive packets.
#define PKT_CONTROL_ONOFF	0x3A	//can disable or reenable the decoding of control packets
#define PKT_MAXPKTLEN		0x3B	//the a3k will not accept packets with length greater than this
#define PKT_MINPKTLEN		0x3C	//the a3k will not accept packets with length less than this
#define PKT_EALLOW		0x3D	//execute eallow instruction
#define PKT_EDIS		0x3E	//execute edis instruction
#define PKT_PARITYMODE		0x3F	//enable/disable parity byte (possible CRC in the future)
#define PKT_CHANNEL0		0x40
#define PKT_CHANNEL1		0x41
#define PKT_CHANNEL2		0x42

#define PKT_WRITEI2C		0x44
#define PKT_READI2C		0x45
#define PKT_CLRCODECRESET	0x46
#define PKT_SETCODECRESET	0x47
#define PKT_DISCARDNCODEC	0x48
#define PKT_DELAYNUS		0x49
#define PKT_DELAYNNS		0x4a


#define PKT_HEADER		((short)('a'))





