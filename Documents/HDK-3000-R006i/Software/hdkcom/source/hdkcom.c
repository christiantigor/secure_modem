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
#include <windows.h> /* for Sleep() */

#include "pcutil.h"
#include "pcargs.h"
#include "comport.h"
#include "a3kpacket.h"
#include "hdkpacket.h"
#include "cmode.h"

static void 
usage( char *name )
{
	static char usagestr[] =
"%s [-port <COM> <baud>] [Main Options][Sub Options] <infile> <outfile>\n"
"\n"
"[-port com baud]     *The COM port and baud rate must always be specified first.\n\n"
"Exactly one Main Option must be specified, Main Options are:\n"
" [-enc]              *Switch the HDK into packet mode and encode the speech in <infile> by sending\n"
"                      speech packets to the HDK.  Channel packets are read back from the HDK and\n"
"                      the channel data is stripped from the packets and written to <outfile>.  When\n"
"                      complete, the HDK is switched into IDLE mode.\n"
" [-dec]              *Switch the HDK into packet mode and send channel packets to the HDK taking\n"
"                      channel data from the file <infile>.  Speech data is extracted from the\n"
"                      speech packets which are received from the HDK and written to the file\n"
"                      <outfile>. When complete, the HDK is switched into IDLE mode.\n"				
" [-encdec]           *Switch the HDK into packet mode and encode the speech in <infile> by sending\n"
"                      speech packets to the HDK.  Channel packets are read back from the HDK and\n"
"                      sent back to the HDK for decoding.  Speech data is extracted from the speech\n"
"                      packets which are received from the HDK and written to the file <outfile>.\n"
"                      When complete, the HDK is switched into IDLE mode.\n"
" [-play]             *Switch the HDK into codec mode, then begin sending channel packets to the\n"
"                      HDK.  The channel packets are created using channel data from the file\n"
"                      <infile>.  The HDK decodes the packets and the resulting speech samples\n"
"                      are sent to the codec interface.  When complete, the HDK is switched into\n"
"                      idle mode. <outfile> is not used.\n"
" [-record seconds]   *Switch the HDK into codec mode, then begin extracting channel data from\n"
"                      each channel packet that is output by the HDK.  The channel data is written\n"
"                      to file <outfile>.  <infile> is not used.  The program will record for the\n"
"                      number of seconds specified by the decimal integer seconds.  When complete,\n"
"                      the HDK is switched into idle mode.\n"
" [-playrecord]       *Switch the HDK into codec mode, then begin sending channel packets to the\n"
"                      HDK, while simultaneously receiving channel packets to the HDK.  Channel\n"
"                      packets sent to the HDK are formed using channel data from <infile> and\n"
"                      the decoded speech samples are played out via the codec interface. Channel\n"
"                      data received from the HDK is stored in <outfile> and is produced by \n"
"                      encoding the speech samples received via the codec interface.  When all,\n"
"                      the data from <infile> has been read, the HDK is switched into idle mode.\n"
" [-mode <mode>]       *where mode is one of idle,dualhdk,dualhdkskew,loopback,a3kdirect\n"
"                      Switch the HDK into the specified mode.  The HDK will remain in the mode\n"
"                      specified, until it is changed by a subequent request to change the mode.\n"
"                      idle - for this mode, the HDK is just waiting to switch to another mode.\n"
"                      loopback - for this mode, the HDK configures the AMBE-3000, and switches it\n"
"                          to codec mode.  The AMBE-3000 encodes speech samples received via the\n"
"                          codec interface.  Packets from the AMBE-3000 are received via the MSP\n"
"                          and then sent back to the AMBE-3000 for decoding.  The decoded speech\n"
"                          samples are output via the codec interface.\n"
"                      dualhdk - for this mode, the HDK configures the AMBE-3000, and switches it\n"
"                          to codec mode.  The AMBE-3000 encodes speech samples received via the\n"
"                          codec interface.  Packets from the AMBE-3000 are received via the MSP\n"
"                          and sent out over P2 which is assumed to be connected to another HDKs\n"
"                          P2.  Simultaneously the MSP receives channel packets from P2 and sends\n"
"                          it to the AMBE-3000, which decodes the packets.  The decoded speech\n"
"                          samples are output via the codec interface.\n"
"                      dualhdkskew - This mode is the same as dualhdk mode except that skew control\n"
"                          is enable on the AMBE-3000.  The AMBE-3000, produces packets at the same\n"
"                           rate whcih packets are received.\n"
"                      a3kdirect - for this mode, the HDK configures the AMBE-3000 to operate in\n"
"                          packet mode using the UART interface (P1).  This allows packets to be\n"
"                          sent directly to the AMBE-3000 without having the MSP involved.  For\n"
"                          example, if P1 is connected to a PC, a custom program or a terminal\n"
"                          program running on the PC can send/receive packets to/from the AMBE-3000\n\n"
"Multiple Sub Options may also be specified, Sub Options are:\n"
" [-r rate]            *where rate is a decimal integer between 0 and 62.\n"
"                       rate specifies the rate index for one of the AMBE-3000 built-in vocoder\n"
"                       rates\n"
" [-r custom]          *where custom has the form 0xNNNN 0xNNNN 0xNNNN 0xNNNN 0xNNNN 0xNNNN\n"
"                       custom specifies 6 custom rate words in hexadecimal format\n"
" [-uart]              *specifies that the MSP to AMBE-3000 interface is the UART interface.  P1 is\n"
"                       assumed to be connected to P2 via a Null Modem Jumper Cable.  This option\n"
"                       may be combined with any of the Main Options except for [-mode dualhdk],\n"
"                       [-mode daulhdkskew], or [-mode a3kdirect].  The default MSP to AMBE-3000\n"
"                       interface is via the parallel port (no jumper needed)\n"
" [-ns state]          *noise suppresion off (state=0) or on (state=1) (default=on)\n";

        fprintf( stderr, usagestr, name );
	exit ( 3 );
}

/*
 * Default coder values:
 * 
 * VAD_LEVEL     : nominal voice activation level
 * TONE_AMP      : nominal generated tone amplitude
 * TONE_INDEX    : default generated tone index
 * SD_BITS_NOM   : nominal number of soft decision bits
 * SD_BITS_MAX   : max number of soft decision bits
 */
#define VAD_LEVEL_MIN      -90
#define VAD_LEVEL          -25
#define VAD_LEVEL_MAX        3
#define TONE_AMP           -10
#define TONE_INDEX         128
#define SD_BITS_MIN          1
#define SD_BITS              1
#define SD_BITS_MAX          4

#define SPEECH_BUF_SZ     164
short  speech_buf[SPEECH_BUF_SZ];

#define CHAN_BUF_SZ     (9600/50)
short    chan_buf[CHAN_BUF_SZ];

PC_OPTIONS  opts;

static void
get_options( PC_OPTIONS    *o,
	     int         argc,
	     char       *argv[] )
{
	/*
	 * set default options and read in command line args
	 */
	o->verbose        = 0;
	o->run_encoder    = 0;
	o->run_decoder    = 0;
	o->rate           = 32; /* ambe3000, 4800 bps */
	o->vad_level      = VAD_LEVEL;
	o->nsprsn_enabled = 1;
	o->tone_on        = 0;
	o->tone_amp       = TONE_AMP;
	o->tone_index     = TONE_INDEX;
	o->sd_bits        = SD_BITS;
	o->sd_dist        = 0;
	o->hd_errs        = 0;
	o->dtx	          = -1;
	o->echo_canceller_enabled = 0;
	o->tone_det_enabled = 1; /*tone detection on by default*/
	o->compand        = ARGS_COMPAND_LINEAR;
	o->play		  = 0;
	o->record         = 0;
	o->codec	  = 0;
	o->passthru	  = 0;
	o->seconds        = 0;
	o->packetif	  = PACKET_PPT;
	o->hdkmode	  = 0;
	o->sendhdkmode    = 0;
	o->waitkey        = 0;
	o->lowpower       = 0;
	o->getversion     = 0;
	o->a3kdirect      = 0;
	o->delayed_read_packets = 1;
	o->comport_name   = 0;
	o->fpi_name       = NULL;
	o->fpi            = NULL;
	o->fpo_name       = NULL;
	o->fpo            = NULL;
			
	if ( ambe_read_args( o, argc, argv ) < 0 ) {
		DVSI_copyright();
		usage( argv[0] );
	}

	if ((!o->run_encoder) &&
	    (!o->run_decoder) &&
	    (!o->play) &&
	    (!o->record) &&
	    (!o->sendhdkmode) &&
	    (!o->getversion)) {
		printf( "get_options: no main option specified.\n" );
		usage( argv[0] );
	}
	
	/*
	 * make sure important options have the proper values
	 */

	if (o->sendhdkmode)
		return; //dont do the rest if we are just sending an hdk control packet

	if (o->getversion)
		return;
	
	if ((!o->codec) || (o->play)) { //no input file required for record
		if ( !o->fpi ) {
			DVSI_copyright();
			printf( "get_options: no input file specified.\n" );
			usage( argv[0] );
		}
	}

	if ((!o->codec) || (o->record)) { //no output file required otherwise
		if ( !o->fpo ) {
			DVSI_copyright();
			printf( "get_options: no output file specified.\n" );
			usage( argv[0] );
		}
	}
	
}


/*
 * set encoder channel data output to all ones to signal dtx off
 */
static void
signal_dtx_off( short *cbuf,
		short  len )
{
	short i;
	for ( i = 0; i < len; i++ )
		cbuf[i] = 1;
}

/*
 * handle discontionuous transmission and comfort noise update
 */
static void
dtx_update( short  *cni_count,
	    short acni_frames,
	    short       *cbuf,
	    short      status,
	    short   totalbits )
{
	short cni = *cni_count;

	/*
	 * If VOICE_ACTIVE_FLAG is set the frame must be transmitted
	 * to the decoder.  Note that VOICE_ACTIVE_FLAG is true for
	 * the following frames:
	 * 1.  The frame is a voice frame.
	 * 2.  The frame is the first silence frame after a voice burst.
	 * 3.  The encoder determined that the SID frame needs to be
	 *     transmitted because of changes in the background noise.
	 */
	if (status & VOICE_ACTIVE_FLAG ) {

		cni = acni_frames;

	}

	/*
	 * if VOICE_ACTIVE_FLAG is not set then it is not neccessary
	 * to transmit the frame.  The code below causes the unrequired
	 * frames to be transmitted at a regular interval.  Every
	 * (acni_frames+1)th frame is transmitted.  For instance:
	 * if acni_frames=0 then all unrequired SID frames are transmitted.  
	 * if acni_frames=1 then every other unrequired SID frame is transmitted
	 * if acni_frames=2 then every third unrequired SID frame is transmitted
	 * ...
	 * acni_frames>=10000 is a special case.  If acni_frames >= 10000 then
	 * unrequired SID frames are never transmitted.  Note that for this
	 * case cni is always equal to acni_frames.
	 */
	else  {
		if ( cni >= 10000 ) {

			ASSERT( cni == acni_frames );
			
			/*
			 * signal no channel data (DTX off)
			 */
			signal_dtx_off( cbuf, totalbits );
		} else if ( cni > 0 ) {
			/*
			 * signal no channel data (DTX off)
			 */
			cni--;
			signal_dtx_off( cbuf, totalbits );
		} else {
			/* 
			 * reset count for next update (in frames) 
			 */
			cni = acni_frames;
		}
	}
		
	*cni_count = cni;
}



/*
 * return the number of channel bits for the specified rate index.
 */
static short
   nchanbits( short rate )
{
	if (rate == 64) {
		const short *custom_ratewords = ambe_get_user_qentry();
		return (custom_ratewords[5] & 0x00ff );
	} else {
		switch(rate) {
			case  0: return(  2400 /50);
			case  1: return(  3600 /50);
			case  2: return(  4800 /50);
			case  3: return(  4800 /50);
			case  4: return(  9600 /50);
			case  5: return(  2400 /50);
			case  6: return(  9600 /50);
			case  7: return(  4800 /50);
			case  8: return(  4800 /50);
			case  9: return(  7200 /50);
			case 10: return(  6400 /50);
			case 11: return(  3600 /50);
			case 12: return(  8000 /50);
			case 13: return(  8000 /50);
			case 14: return(  4000 /50);
			case 15: return(  4000 /50);
			case 16: return(  3600 /50);
			case 17: return(  4000 /50);
			case 18: return(  4800 /50);
			case 19: return(  6400 /50);
			case 20: return(  8000 /50);
			case 21: return(  9600 /50);
			case 22: return(  4000 /50);
			case 23: return(  4800 /50);
			case 24: return(  4800 /50);
			case 25: return(  4800 /50);
			case 26: return(  6400 /50);
			case 27: return(  7200 /50);
			case 28: return(  8000 /50);
			case 29: return(  9600 /50);
			case 30: return(  9600 /50);
			case 31: return(  2000 /50);
			case 32: return(  6400 /50);
			case 33: return(  3600 /50);
			case 34: return(  2450 /50);
			case 35: return(  3400 /50);
			case 36: return(  2250 /50);
			case 37: return(  2400 /50);
			case 38: return(  3000 /50);
			case 39: return(  3600 /50);
			case 40: return(  4000 /50);
			case 41: return(  4400 /50);
			case 42: return(  4800 /50);
			case 43: return(  6400 /50);
			case 44: return(  7200 /50);
			case 45: return(  8000 /50);
			case 46: return(  9600 /50);
			case 47: return(  2700 /50);
			case 48: return(  3600 /50);
			case 49: return(  4000 /50);
			case 50: return(  4800 /50);
			case 51: return(  4400 /50);
			case 52: return(  4800 /50);
			case 53: return(  6000 /50);
			case 54: return(  7200 /50);
			case 55: return(  4000 /50);
			case 56: return(  4800 /50);
			case 57: return(  4800 /50);
			case 58: return(  6400 /50);
			case 59: return(  7200 /50);
			case 60: return(  8000 /50);
			case 61: return(  9600 /50);
			default: return 0;
		}
	}
}


static char *
   put_byte( char   *p,
	     char byte )
{
	*p++ = byte;
	return p;
}

static char *
   put_word( char    *p,
	     short word )
{
	p = put_byte( p, (char)(word>>8) );
	p = put_byte( p, (char)word );
	return p;
}

static char *
   put_long( char        *p,
	     long long_word )
{
	p = put_word( p, (short)(long_word>>8) );
	p = put_word( p, (short) long_word );
	return p;
}

static short
   make_packet( char *packet,
		char *raw_packet, //without header,len,type,parity
		char *packet_end,
		char pkt_type   )
{
	short packet_len = packet_end - raw_packet + 2; //dont include header,length, and type
	char parity = 0;
	short i;

	*packet++ = PKT_HEADER;
	*packet = (packet_len >> 8) & 0x00ff;
	parity ^= *packet++;
	*packet = (packet_len) & 0x00ff;
	parity ^= *packet++;
	*packet =  pkt_type;
	parity ^= *packet++;
	for ( i = 0; i < packet_len-2; i++ ) {
		*packet++ = *raw_packet;
		parity ^= *raw_packet++;
	}

	*packet++ = PKT_PARITYBYTE;
	parity ^= PKT_PARITYBYTE;
	*packet++ = parity;

	return packet_len+4; //return length including header,length,type
}


static short
   encode_speech_packet( char          *packet,
			 short     *speech_buf,
			 short         channel,
			 short       nchannels,
			 unsigned char samples,
			 short           cmode,
			 short         compand )
{
	char sp_packet[340];
	char *p = sp_packet;
	short i;

	if (nchannels > 1)
		p = put_byte( p, (char)(PKT_CHANNEL0+channel) );
	p = put_byte( p, PKT_SPEECHD );
	p = put_byte( p, samples );
	if (compand) {
		for( i = 0; i < samples; i++ ) {
			p = put_byte( p, (char) (speech_buf[i] & 0x00ff) );
		}
	} else {
		for( i = 0; i < samples; i++ ) {
			p = put_word( p, speech_buf[i] );
		}
	}
	p = put_byte( p, PKT_CMODE );
	p = put_word( p, cmode );

	return make_packet( packet, sp_packet, p, PKT_SPEECH );
}


static char *
   get_byte( char *p, char *c )
{
	*c = *p++;
	return p;
}
static char *
   get_ubyte( char *p, unsigned char *c )
{
	*c = (unsigned char)*p++;
	return p;
}

static char *
   get_string( char *p, char *string )
{
	char c;

	do {
		c = *string++ = *p++ & 0x00ff;
	} while (c != 0);
	return p;
}

static char *
   get_word( char *p, short *wd )
{
	*wd = ((short)(*p++)) << 8;
	*wd += *p++ & 0x00ff;
	return p;
}

static char *
   get_addr( char *p, long *addr )
{

	*addr =   (((long)(*p++)) & 0x00ff) << 16;
	*addr +=  (((long)(*p++)) & 0x00ff) <<  8;
	*addr +=  (((long)(*p++)) & 0x00ff) <<  0;
	return p;
}

static char *
   get_long( char *p, long *lword )
{
	*lword =   (((long)(*p++)) & 0x00ff) << 24;
	*lword +=  (((long)(*p++)) & 0x00ff) << 16;
	*lword +=  (((long)(*p++)) & 0x00ff) <<  8;
	*lword +=  (((long)(*p++)) & 0x00ff) <<  0;
	return p;
}


static void
   print_packet( char     *packet,
		 short packet_len )
{
	printf("packet_len=%d\n", packet_len );
	{
		short i;
		for (i=0;i<packet_len;i++) {
			printf("%02x ", packet[i] & 0x00ff );
			if (((i % 24) == 23) || (i==packet_len-1))
				printf("\n");
		}
	}
	printf("\n");
}


static void
   put_packet( char	      *packet,
	       short              len,
	       CommPortClass *comPort )
{
	WritePacketPort( packet, len, comPort );

}


static short
   get_packet( char           *packet,
	       short          timeout,
	       CommPortClass *comPort )
{
	int packet_len;


	ReadPacketPort( packet, &packet_len, timeout, comPort );
		
	return packet_len;
}


short
   get_a3k_version( char *prod_id, char *version_string, CommPortClass *comPort )
{
	char packet[70];
	char *p = packet;
	char chk_header, chk_type, chk_field;
	short plen;

	p = put_byte( p, PKT_HEADER );
	p += 2;				//skip space for len
	p = put_byte( p, PKT_CONTROL );
	p = put_byte( p, PKT_PRODID );
	p = put_byte( p, PKT_VERSTRING );
	p = put_byte( p, PKT_PARITYBYTE );
	p = put_byte( p, 4 ^ PKT_CONTROL ^ PKT_PRODID ^ PKT_VERSTRING ^ PKT_PARITYBYTE );

	put_word(packet+1, (short)(p-packet-4) );
	put_packet( packet, (short)(p-packet), comPort );

	plen = get_packet( packet, 0, comPort );

	p = packet;
	p = get_byte( p, &chk_header );
	if (chk_header != PKT_HEADER)
		return -1;
	p += 2; //skip len
	p = get_byte( p, &chk_type );
	if (chk_type != PKT_CONTROL)
		return -3;
	p = get_byte( p, &chk_field);
	if (chk_field != PKT_PRODID)
		return -4;
	p = get_string( p, prod_id );
	p = get_byte( p, &chk_field);
	if (chk_field != PKT_VERSTRING)
		return -5;
	p = get_string( p, version_string );

	return 0;
}


/*
 * this function sends a stopcodec packet and then waits until a
 * stopcodec response is received.  If any other packets are received
 * before the expected response, then they are discarded.
 */
short
   a3k_stopcodec( CommPortClass *comPort )
{
	char packet[400];//needs to be large to prevent error when passthru is enabled
	char *p = packet;
	char chk_header, chk_type, chk_field;
	short chk_len;
	short plen;
	char expect_response[8] = { 0x61, 0x00, 0x04, 0x00, 0x2b, 0x00, 0x2f, 0x00 };
	short trials = 0;

startover:
	p = put_byte( p, PKT_HEADER );
	p += 2;				//skip space for len
	p = put_byte( p, PKT_CONTROL );
	p = put_byte( p, PKT_STOPCODEC );
	p = put_byte( p, PKT_PARITYBYTE );
	p = put_byte( p, 3 ^ PKT_CONTROL ^ PKT_STOPCODEC ^ PKT_PARITYBYTE );

	put_word(packet+1, (short)(p-packet-4) );
	put_packet( packet, (short)(p-packet), comPort );

	
	while (1) {
		short i;

		/*
		 * 100 millisecond timeout
		 */
		plen = get_packet( packet, 100, comPort );

		/*
		 * if we waited one second and did not receive any
		 * packets, then something is wrong.
		 */
		if (plen == 0) {
			if (trials > 5) {
				printf("stopcodec: timeout\n");
				return -1;
			} else {
				printf("start over\n");
				goto startover;
			}
		}

		//print_packet( packet, plen );
			      
		if (plen != 8) {
			trials++;
			if (trials > 5) {
				printf("stopcodec: expected response not received, wrong length\n");
				return -2;
			}
			continue;
		} else {
			short errors = 0;
			for ( i = 0; i < 8; i++ ) {
				if (packet[i] != expect_response[i])
					errors++;
			}
		
			if (errors) {
				trials++;
				if (trials > 5) {
					printf("stopcodec: expected response not received, packet mismatch\n");
					return -2;
				}
				continue;
			} else {
				return 0;
			}
		}
	}
}


static void
   decode_channel_packet( short  *chan_buf,
			  short     *cmode,
			  char     *packet,
			  short packet_len,
			  short  echanbits )
{
	char *p = packet;
	char b;
	short len;
	char type;
	
	p = get_byte( p, &b );
	if (b != PKT_HEADER) {
		printf("channel packet error: expecting header byte\n");
		print_packet( packet, packet_len );
		exit(0);
	}
	p = get_word( p, &len );
	if (len+4 != packet_len) {
		printf("channel packet error: length field error\n");
		printf("len=%d, packet_len=%d\n", len, packet_len );
		print_packet( packet, packet_len );
		exit(0);
	}
	p = get_byte( p, &type );
	if (type != PKT_CHANNEL) {
		printf("channel packet error: unexpected packet type\n");
		print_packet( packet, packet_len );
		exit(0);
	}
	packet_len -= 4;
	while (packet_len > 0) {
		char field;
		p = get_byte( p, &field );
		packet_len--;
		if ((field >= PKT_CHANNEL0) && (field <= PKT_CHANNEL2)) {

		} else if (field == PKT_CHAND) {

			short i;
			short bits = 0;
			short sdbits = 1;
			short mask = (1<<sdbits)-1;
			short val = 0;
			unsigned char len;

			p = get_ubyte( p, &len ); //len is the number of bits (not bytes)

			if (len != echanbits) {
				printf("channel packet error: unexpected PKT_CHAND length\n");
				printf("len=%d\n");
				printf("echanbits=%d\n", echanbits );
				print_packet( packet, packet_len );
				exit(0);
			}

			packet_len--;

			/*
			 * note that the channel bits are packed
			 * without wasting any bits, even for
			 * soft-decision. They are unpacked
			 * here. The first bit is in the msb of
			 * the first word.
			 */

			for (i=0; i< len; i++ ) {
				if (bits < sdbits) {
					unsigned char tmp;
					val <<= bits;		//all available bits are now in the lsbs of ms byte
					p = get_ubyte( p, &tmp );
					val += tmp;
					val <<= (sdbits-bits);	//now the lowest sdbits bits of the ms byte are the next bit
					packet_len--;
					bits += 8;		//how many bits are in val that have not been read yet
				}
				chan_buf[i] = (val >> 8) & mask;
				val <<= sdbits;
				bits -= sdbits;
			}


		} else if (field == PKT_ECMODE) {
			p = get_word( p, cmode );
			packet_len -= 2;
		} else if (field == PKT_CMODE) {
			p = get_word( p, cmode );
			packet_len -= 2;
		} else if (field == PKT_ETIME) {
			//this program ignores this, would be nice to
			//use it
			long etime;
			p = get_long( p, &etime );
			packet_len -= 4;
		} else if (field == PKT_DTIME) {
			//this program ignores this, at least for now
			long dtime;
			p = get_long( p, &dtime );
			packet_len -= 4;
		} else if (field == PKT_EWS) {
			//this program ignores this, at least for now
			char tmp;
			p = get_byte( p, &tmp );
			p = get_byte( p, &tmp );
			packet_len -= 2;
		} else if (field == PKT_WS) {
			//this program ignores this, at least for now
			char tmp;
			p = get_byte( p, &tmp );
			p = get_byte( p, &tmp );
			packet_len -= 2;

		} else if (field == PKT_DWS) {
			//this program ignores this, at least for now
			char tmp;
			p = get_byte( p, &tmp );
			p = get_byte( p, &tmp );
			packet_len -= 2;
		} else if (field == PKT_PARITYBYTE) {
			//this program ignores this, at least for now
			char tmp;
			p = get_byte( p, &tmp );
			packet_len -= 1;
		} else {
			printf("channel packet error: unexpected field = %d\n", field );
			print_packet( packet, packet_len );
			exit(0);
		}

	}

}

/*
 * this creates a reset packet to send to the a3k
 */
static short
   encode_reset_packet( char *packet )
{
	char reset_packet[10];
	char *p = reset_packet;

	p = put_byte( p, PKT_RESET );

	return make_packet( packet, reset_packet, p, PKT_CONTROL );
}

static short
   encode_control_packet( char      *packet,
			  PC_OPTIONS     *o )
{
	char ctrl_packet[200];
	char *p = ctrl_packet;
	short ecmode = 0;
	
	p = put_byte( p, PKT_LOWPOWER );
	p = put_byte( p, o->lowpower );

	p = put_byte( p, PKT_COMPAND );
	p = put_byte( p, (char)o->compand );

	p = put_byte( p, PKT_CHANNEL0 );
	p = put_byte( p, PKT_INIT );
	p = put_byte( p, PKT_INIT_ENCODER|PKT_INIT_DECODER|PKT_INIT_ECHO );


	if (o->rate == 64) {
		short i;
		const short *custom_ratewords = ambe_get_user_qentry();
		p = put_byte( p, PKT_RATEP );
		for ( i = 0; i < 6; i++ )
			p = put_word( p, custom_ratewords[i] );
	} else {
		p = put_byte( p, PKT_RATET );
		p = put_byte( p, (char)o->rate );
	}
	
	p = put_byte( p, PKT_ECMODE );
	if (o->tone_det_enabled)
		ecmode |= 0x1000;
	if (o->nsprsn_enabled)
		ecmode |= 0x0040;
	if (o->dtx)
		ecmode |= 0x0800;
	if (o->echo_canceller_enabled)
		ecmode |= 0x2000;
	
	//use 0x2000 to enable echo canceller
	//use 0x0200 to enable echo suppressor
	//use 0x0100 to enable companding
	//use 0x0080 to select a-law companding
	//use 0x4000 to force a tone
	p = put_word( p, ecmode );

	/*
	 * if DTX is enabled, we must output cmode for every channel
	 * packet
	 */
	if (o->dtx) {
		p = put_byte( p, PKT_ENCOUT_FORMAT );
		p = put_word( p, 0x0001 );
	}

	if ((o->sd_dist > 0) && (o->hd_errs > 0)) {
		p = put_byte( p, PKT_ERRTHRESH );
		p = put_word( p, o->sd_dist );
		p = put_word( p, o->hd_errs );
	}

	/*
	 * modify this to set the echo canceller enable bit in ecmode if the
	 * echo canceller is enabled and to set the noise suppressor, dtx,
	 * and tone detect, and compand bits appropriately according to the
	 * specified options
	 */
	
	return make_packet( packet, ctrl_packet, p, PKT_CONTROL );

}

static short
   check_ready_packet( char     *packet,
		       short packet_len )
{
	char *p = packet;
	char b;
	short len;
	char type;
	char field;

	if (packet_len != 7) {
		printf("ready packet error: incorrect packet length\n");
		return 1;
	}

	p = get_byte( p, &b );
	if (b != PKT_HEADER) {
		printf("ready packet error: expecting header byte\n");
		return 2;
	}

	p = get_word( p, &len );
	if (len+4 != packet_len) {
		printf("ready packet error: length field error\n");
		return 3;
	}
	p = get_byte( p, &type );
	if (type != PKT_CONTROL) {
		printf("ready packet error: unexpected packet type\n");
		return 4;
	}
	p = get_byte( p, &field );
	if (field != PKT_READY) {
		printf("ready packet error: expected PKT_READY field\n");
		return 5;
	}

	return 0;
}

static short
   check_response_packet( char     *packet,
			  short packet_len,
			  short    verbose )
{
	char *p = packet;
	char b;
	short len;
	char type;

	p = get_byte( p, &b );
	if (b != PKT_HEADER) {
		if (verbose) {
			printf("response packet error: expecting header byte\n");
			print_packet( packet, packet_len );
		}
		return 1;
	}
	p = get_word( p, &len );
	if (len+4 != packet_len) {
		if (verbose) {
			printf("response packet error: length field error\n");
			print_packet( packet, packet_len );
		}
		return 2;
	}
	p = get_byte( p, &type );
	if (type != PKT_CONTROL) {
		if (verbose) {
			printf("response packet error: unexpected packet type\n");
			print_packet( packet, packet_len );
		}
		return 3;
	}
	packet_len -= 4;
	while (packet_len > 0) {
		char field;
		p = get_byte( p, &field );
		packet_len--;


#define CHECK_FOR_OK(s)	{ char tmp; p = get_byte( p, &tmp ); if (tmp != PKT_RESPONSE_OK) {\
				if (verbose) { \
					printf("response packet error: %s error (field=%d) \n", s, field );\
					print_packet( packet, packet_len );\
				} \
				return 4;\
			} }

		if (field == PKT_FLASHCONFIG) {
			CHECK_FOR_OK("PKT_FLASHCONFIG");
			packet_len--;
		} else if (field == PKT_PLLCONFIG) {
			CHECK_FOR_OK("PKT_PLLCONFIG");
			packet_len--;
		} else if (field == PKT_LSPCLKCONFIG) {
			CHECK_FOR_OK("PKT_LSPCLKCONFIG");
			packet_len--;
		} else if (field == PKT_RATET) {
			CHECK_FOR_OK("PKT_RATET");
			packet_len--;
		} else if (field == PKT_RATEP) {
			CHECK_FOR_OK("PKT_RATEP");
			packet_len--;
		} else if (field == PKT_VADLEVEL) {
			CHECK_FOR_OK("PKT_VADLEVEL");
			packet_len--;
		} else if (field == PKT_LOWPOWER) {
			CHECK_FOR_OK("PKT_LOWPOWER");
			packet_len--;
		} else if (field == PKT_SDBITS) {
			CHECK_FOR_OK("PKT_SDBITS");
			packet_len--;
		} else if (field == PKT_INIT) {
			CHECK_FOR_OK("PKT_INIT");
			packet_len--;
		} else if (field == PKT_STARTCODEC) {
			CHECK_FOR_OK("PKT_STARTCODEC");
			packet_len--;
		} else if (field == PKT_COMPAND) {
			CHECK_FOR_OK("PKT_COMPAND");
			packet_len--;
		} else if (field == PKT_ECMODE) {
			CHECK_FOR_OK("PKT_ECMODE");
			packet_len--;
		} else if (field == PKT_DCMODE) {
			CHECK_FOR_OK("PKT_DCMODE");
			packet_len--;
		} else if (field == PKT_CHANNEL0) {
			CHECK_FOR_OK("PKT_CHANNEL0");
			packet_len--;
		} else if (field == PKT_CHANNEL1) {
			CHECK_FOR_OK("PKT_CHANNEL1");
			packet_len--;
		} else if (field == PKT_CHANNEL2) {
			CHECK_FOR_OK("PKT_CHANNEL2");
			packet_len--;
		} else if (field == PKT_ENCOUT_FORMAT) {
			CHECK_FOR_OK("PKT_ENCOUT_FORMAT");
			packet_len--;
		} else if (field == PKT_CODECCFG) {
			CHECK_FOR_OK("PKT_CODECCFG");
			packet_len--;
		} else if (field == PKT_ERRTHRESH) {
			CHECK_FOR_OK("PKT_ERRTHRESH");
			packet_len--;
		} else if (field == PKT_PARITYBYTE) {
			//the parity has already been checked, throw
			//away parity byte
			char parity;
			p = get_byte( p, &parity );
			packet_len -= 1;

		} else {
			if (verbose ) {
				printf("response packet error: field %d unrecognized\n", field );
				print_packet( packet, packet_len );
			}
			return 5;
		}
	}

	return 0;
}

static void
   a3k_reset_packet( CommPortClass *comPort )
{
	char packet[512];
	int packet_len;
	packet_len = encode_reset_packet( packet );
	WritePacketPort( packet, packet_len, comPort );
	/*
	 * a3k sends a ready packet after it is reset.
	 * wait for it and check it.
	 */
	ReadPacketPort( packet, &packet_len, 0, comPort );
	check_ready_packet( packet, (short)packet_len );
}



static short
   a3k_control_packet( PC_OPTIONS          *o,
		       CommPortClass *comPort )
{
	char packet[512];
	int packet_len;
	short error;

	packet_len = encode_control_packet( packet, o );

	/*
	 * send the packet to the a3k via COM port
	 */
	WritePacketPort( packet, packet_len, comPort );

	/*
	 * Now read back a packet
	 */
	if (ReadPacketPort( packet, &packet_len, 0, comPort )) {
		printf("error reading port, trying to read control packet\n");
	}

	/*
	 * Now extract data from the packet
	 */
	error = check_response_packet( packet, (short)packet_len, 1 );

	return error;  //returns 0 for no error
}

static short
   a3k_startcodec( PC_OPTIONS          *o,
		   CommPortClass *comPort )
{
	char codec_packet[100];
	char *p = codec_packet;
	char packet[100];
	int packet_len;
	short error;

	p = put_byte( p, PKT_STARTCODEC );
	//skew control enabled if lsb is 1
	//passthru enabled if bit 1 is 1
	//mcbsp used instead of spi if bit 2 is 1
	p = put_byte( p, (char)(o->passthru<<1) );

	packet_len = make_packet( packet, codec_packet, p, PKT_CONTROL );

	/*
	 * send the packet to the a3k via COM port
	 */
	WritePacketPort( packet, packet_len, comPort );

	/*
	 * Now read back a packet
	 */

	if (ReadPacketPort( packet, &packet_len, 0, comPort )) {
		printf("error reading port, trying to read start codec response packet\n");
	}


	/*
	 * Now extract data from the packet
	 */
	error = check_response_packet( packet, (short)packet_len, 1 );

	return error;  //returns 0 for no error
}



static void
   a3k_encode_packet( short        *chan_buf,
		      short        echanbits,
		      short      *speech_buf,
		      short	          ws,
		      short	      *cmode,
		      short          compand,
		      short               wp,
		      short               rp,
		      CommPortClass *comPort )
{
	char packet[512];
	int packet_len;

	if (wp) {
		packet_len = encode_speech_packet( packet, speech_buf, 0, 1, (unsigned char)ws, *cmode, compand );

		/*
		 * send the packet to the a3k via COM port
		 */
		WritePacketPort( packet, packet_len, comPort );
	}

	if (rp) {
		/*
		 * Now read back a packet
		 */
		rp = ReadPacketPort( packet, &packet_len, 0, comPort );

		if (rp)
			printf("error reading port, trying to read channel packet\n");

		/*
		 * Now extract data from the packet
		 */
		decode_channel_packet( chan_buf, cmode, packet, (short)packet_len, echanbits );
		
	}
}

static short
   encode_channel_packet( char     *packet,
			  short  *chan_buf,
			  short     sdbits,
			  short      cmode,
			  unsigned char ws,
			  short  dchanbits )
{
	char ch_packet[200];
	char *p = ch_packet;

	if (sdbits == 4) 
		p = put_byte( p, PKT_CHAND4 );
	else
		p = put_byte( p, PKT_CHAND );

	{
		short i;
		short bits = 0;
		short mask = (1<<sdbits)-1;
		short val = 0;
		short byte;
		
		p = put_byte( p, (char)dchanbits );
		
		/*
		 * note that the channel bits are packed
		 * without wasting any bits, even for
		 * soft-decision. They are packed
		 * here. The first bit is in the msb of
		 * the first word.
		 */		
		for ( i = 0; i < dchanbits; i++ ) {
			val <<= sdbits;
			val += (chan_buf[i] & mask);
			bits += sdbits;
			if (bits >= 8) {
				byte = (val >> (bits-8)); //write out 8 msbs
				p = put_byte( p, (char)byte );
				bits -= 8;
			}
		}

		if (bits > 0) {
			byte = (val << (8-bits)); //write out last partial byte with 0 in lsbs
			p = put_byte( p, (char)byte );
		}
	}
	

	p = put_byte( p, PKT_WS );
	p = put_byte( p, ws );
//	printf("cmode=%d\n", cmode );
	p = put_byte( p, PKT_CMODE );
	p = put_word( p, cmode );

	return make_packet( packet, ch_packet, p, PKT_CHANNEL );

}

static void
   decode_speech_packet( short     *speech_buf,
			 short          *cmode,
			 char          *packet,
			 unsigned char samples,
			 short	    packet_len,
			 short         compand )
{
	char *p = packet;
	char b;
	short len;
	char type;
#if 0
	printf("received speech packet:\n");
	print_packet( packet, packet_len );	
#endif
	
	p = get_byte( p, &b );
	if (b != PKT_HEADER) {
		printf("speech packet error: expecting header byte\n");
		print_packet( packet, packet_len );	
		exit(0);
	}
	p = get_word( p, &len );
	if (len+4 != packet_len) {
		printf("speech packet error: length field error\n");
		print_packet( packet, packet_len );	
		exit(0);
	}
	p = get_byte( p, &type );
	if (type != PKT_SPEECH) {
		printf("speech packet error: unexpected packet type %d\n", type );
		print_packet( packet, packet_len );			
		exit(0);
	}
	packet_len -= 4;
	while (packet_len > 0) {
		char field;
		p = get_byte( p, &field );
		packet_len--;
		if (field == PKT_SPEECHD) {
			short i;
			unsigned char samples_r;
			p = get_ubyte( p, &samples_r );
			if (samples != samples_r) {
				printf("speech packet error: received samples=%d, expected samples=%d\n", samples_r, samples );
				print_packet( packet, packet_len );	
				exit(0);
			}
			if (compand) {
				for ( i = 0; i < samples_r; i++ ) {
					char c;
					p = get_byte( p, &c );
					speech_buf[i] = c;
				}
			} else {
				for ( i = 0; i < samples_r; i++ )
					p = get_word( p, speech_buf+i );
			}
			packet_len -= (1 + 2*samples_r ); 
		} else if (field == PKT_CMODE) {
			p = get_word( p, cmode );
			packet_len -= 2;
		} else if (field == PKT_TIME) {
			//this program ignores this, would be nice to
			//use it
			long time;
			p = get_long( p, &time );
			packet_len -= 4;
		} else if (field == PKT_WS) {
			//this program ignores this, at least for now
			char ws;
			p = get_byte( p, &ws );
			packet_len -= 1;

		} else if ((field >= PKT_CHANNEL0) && (field <= PKT_CHANNEL2)) {
			//if the HDK uses an AMBE3003 then this field
			//appears in speech packets
		} else if (field == PKT_PARITYBYTE) {
			//the parity has already been checked, throw
			//away parity byte
			char parity;
			p = get_byte( p, &parity );
			packet_len -= 1;
		} else {
			printf("speech packet error: unexpected field = %d\n", field );
			print_packet( packet, packet_len );	
			exit(0);
		}

	}
}

static short
   a3k_decode_packet( short      *speech_buf,
		      short        dchanbits,
		      short        *chan_buf,
		      short	          ws,
		      short	      *cmode,
		      short          compand,
		      short          sd_bits,
		      short               wp,
		      short               rp,
		      CommPortClass *comPort )
{
	char packet[512];
	int packet_len;
	
	if (wp) {

		packet_len = encode_channel_packet( packet, chan_buf, sd_bits, *cmode, (unsigned char)ws, dchanbits );

		/*
		 * send the packet to the a3k via COM port
		 */
		WritePacketPort( packet, packet_len, comPort );
	}

	if (rp) {
		/*
		 * Now read back a packet
		 */

		if (ReadPacketPort( packet, &packet_len, 0, comPort ))
			printf("error reading port, trying to read speech packet\n");

		/*
		 * Now extract data from the packet
		 */
		decode_speech_packet( speech_buf, cmode, packet, (unsigned char)ws, (short)packet_len, compand );
	}
	
	return *cmode;
}



short e_w_last = 0;  
short e_r_last = 0;

/*
 * run the encoder
 */
static short
   a3k_run_encoder( short        *chan_buf,
		    short        echanbits,
		    short      *speech_buf,
		    PC_OPTIONS          *o,
		    short             *cni )
{
	short write_packet;
	short read_packet;
	short wshift = 160;
	short cmode = 0;
	
	if ( o->tone_on )
		cmode = DTMF_SEND_FLAG;

	if ( o->dtx >= 0 )
		cmode |= DTX_ENABLE_FLAG;

	if ( o->nsprsn_enabled )
		cmode |= NS_ENABLE_FLAG;

	if ( o->tone_det_enabled )
		cmode |= TONE_DET_ENABLE_FLAG;

	if ( o->compand == 1 )
		cmode |= COMPAND_ENABLE_FLAG;
	else if (o->compand == 3)
		cmode |= (COMPAND_ENABLE_FLAG | COMPAND_SELECT_FLAG);
	
	if ((o->codec == 0)||(o->passthru && o->play)) {
		if ( get_speech( speech_buf, wshift, o->fpi, o->compand ) <= 0 )
			write_packet = 0;
		else
			write_packet = 1;
	} else
		write_packet = 0; //dont write a speech packet, if codec is enabled unless its in passthru mode

	cmode |= TONE_DET_ENABLE_FLAG;

	if (o->codec == 0) {
		if (o->delayed_read_packets == 0)
			read_packet = write_packet;	//read packet if you are writing a packet
		else
			read_packet = e_w_last;		//read packet if you wrote one last time (one frame delay)
	} else {
		read_packet = 1;
	}
	
	//if codec=1 we will get a packet from the a3k regardless of
	//whther record=1. if record=0 then we will just throw away the
	//packet we get.
	
	a3k_encode_packet( chan_buf,
			   echanbits,
			   speech_buf,
			   wshift,
			   &cmode,
			   o->compand,
			   write_packet,
			   read_packet,
			   o->comPort );

	
	if (read_packet) {

		if ( o->dtx >= 0 )
			dtx_update( cni, o->dtx, chan_buf, cmode, echanbits );

		if ( !o->run_decoder ) {
			short rem;
			short echanbytes;
			short i;

			/*
			 * need to pad with 0's to get an integral number of
			 * bytes.
			 */
			rem = (echanbits & 0x0007);
			echanbytes = echanbits >> 3;
			if (rem != 0)
				echanbytes++;

			for ( i = 0; i < 8-rem; i++ )
				chan_buf[echanbits+i] = 0;

			if ((o->codec == 0)||((o->record)&&(!o->passthru)))
				put_packed_bits( chan_buf, (short)(echanbytes*8), o->sd_bits, o->fpo );

		}

	}

	e_w_last = write_packet;
	e_r_last = read_packet;

	/*
	 * return 1 when the encoder has finished processing.
	 * return 0 if we still have to send packets or receive
	 * packets.
	 */
	if ((read_packet == 0) && (write_packet == 0)) {
		return 1;
	}
	else
		return 0;
}

/*
 * look for all ones in the decoder channel data input as dtx off signal
 */
static short
check_dtx( short *cbuf,
	   short   len )
{
	short allones = 1;
	short       i;

	for ( i = 0; i < len; i++ )
		allones &= cbuf[i];

	return (allones == 1) ? 1 : 0;
}


short d_w_last = 0;
/*
 * run the encoder
 */
static short
   a3k_run_decoder( short      *speech_buf,
		    short        *chan_buf,
		    short        dchanbits,
		    PC_OPTIONS          *o,
		    long       *dtx_frames )
{
	short dtx_off;
	short wshift = 160;
	short cmode = 0;	
	short write_packet;
	short read_packet;
	
	if ( !o->run_encoder ) {

		if ( !o->codec || (o->play && !o->passthru)) {
			if ( get_packed_bits(chan_buf,dchanbits,o->sd_bits,o->fpi) != dchanbits )
				write_packet = 0;
			else
				write_packet = 1;
		} else {
			write_packet = 0;
		}
	} else {

		write_packet = e_r_last; // write a packet if we read one from the encoder.
		
	}

	if (write_packet == 1) {

		dtx_off = (o->dtx >= 0) ? check_dtx( chan_buf, dchanbits ) : 0;
//		printf("dtx_off=%d\n", dtx_off );
		
		*dtx_frames += dtx_off;

		wshift = 160;

		if ( o->tone_on )
			cmode = DTMF_SEND_FLAG;
		else if ( dtx_off )
			cmode = CNI_FRAME_FLAG;
		else
			cmode = 0;
	}

	
	if ( o->compand == 1 )
		cmode |= COMPAND_ENABLE_FLAG;
	else if (o->compand == 3)
		cmode |= (COMPAND_ENABLE_FLAG | COMPAND_SELECT_FLAG);

	if (o->codec == 0) {
		if (o->delayed_read_packets == 0)		
			read_packet = write_packet;	//read packet if you are writing a packet
		else
			read_packet = d_w_last;		//read packet if you wrote one last time (one frame delay)
	} else {
		/*
		 * when codec mode is enabled, dont read back a packet
		 * from the a3k unless passthru mode is enabled
		 */
		read_packet = 0;
			     
	}

	a3k_decode_packet( speech_buf,
			   dchanbits,
			   chan_buf,
			   wshift,
			   &cmode,
			   o->compand,
			   o->sd_bits,
			   write_packet,
			   read_packet,
			   o->comPort );

	if (read_packet) {
		put_speech( speech_buf, wshift, o->fpo, o->compand );
	} 


	d_w_last = write_packet;

	/*
	 * return 1 when the decoder has finished processing.
	 * return 0 if we still have to send packets or receive
	 * packets.
	 */
	if ((read_packet == 0) && (write_packet == 0) && (e_w_last == 0) && (e_r_last == 0)) {
		return 1;
	} else {
		return 0;
	}
}

/*
 * sends a special packet to the hdk to switch the HDK mode
 */
void
   switch_hdk_mode( char *packet,
		    short   mode,
		    CommPortClass *comPort )
{
	int packet_len;

	packet[0] = PKT_HEADER;
	packet[1] = 0;
	packet[2] = 4;
	packet[3] = PKT_HDKTYPE;
	packet[4] = PKT_HDKMODE;
	packet[5] = (char)mode;
	packet[6] = PKT_PARITYBYTE;
	packet[7] = 4 ^ PKT_HDKMODE ^ PKT_HDKTYPE ^ mode ^ PKT_PARITYBYTE;
	packet_len = 4+4;
	/*
	 * send the packet to the hdk via COM port
	 */
	WritePacketPort( packet, packet_len, comPort );

	/*
	 * wait until the hdk sends back a response
	 * telling us that it switched modes.
	 */			
	ReadPacketPort( packet, &packet_len, 0, opts.comPort );//read HDKREADY

	/*
	 * make sure that the hdk responded as expected. if not then
	 * terminate.
	 */

	if (packet[0] != 0x61) {
		printf("HDKREPLY byte 0: expected 0x61\n");
		print_packet( packet, (short)packet_len );
		exit(0);
	}
	if (packet[1] != 0x00) {
		printf("HDKRPLY byte 1: expected 0x00\n");
		print_packet( packet, (short)packet_len );
		exit(0);
	}
	if (packet[2] != 0x01) {
		printf("HDKREPLY byte 2: expected 0x01\n");
		print_packet( packet, (short)packet_len );
		exit(0);
	}
	if (packet[3] != 0x04){
		printf("HDKREPLY byte 3: expected 0x04\n");
		print_packet( packet, (short)packet_len );
		exit(0);
	}
	if (packet[4] != 0x01){
		printf("HDKREPLY byte 4: expected 0x01\n");
		print_packet( packet, (short)packet_len );
		exit(0);
	}

}

/*
 * sends a special packet to the hdk to query for the MSP program
 * version info.  MSP sends back a null-terminated string.
 */
void
   get_hdk_version( char *verstring,
		    CommPortClass *comPort )
{
	int packet_len;
	char packet[50];
	char *cp;
	
	packet[0] = PKT_HEADER;
	packet[1] = 0;
	packet[2] = 3;
	packet[3] = PKT_HDKTYPE;
	packet[4] = PKT_HDKVERSION;
	packet[5] = PKT_PARITYBYTE;
	packet[6] = 3 ^ PKT_HDKVERSION ^ PKT_HDKTYPE ^ PKT_PARITYBYTE;
	packet_len = 3+4;
	/*
	 * send the packet to the hdk via COM port
	 */
	WritePacketPort( packet, packet_len, comPort );

	/*
	 * wait until the hdk sends back a response
	 * with the version string
	 */			
	ReadPacketPort( packet, &packet_len, 0, opts.comPort );//read HDKREADY

	//no error checking on the packet for now
	cp = packet+5;
	while (*verstring++ = *cp++);


}

#define COM4_RXBUFFER_LEN	2048
#define COM4_BAUD_RATE		230400L
#define COM4_DATA_BITS		8L
#define COM4_TIMEOUT		3000L

char com4_rxbuffer[COM4_RXBUFFER_LEN+1];


int
main( int   argc,
      char *argv[] )
{
	long       frame = 0;
	long  dtx_frames = 0;
	short        cni = 0;
	short  echanbits = 0;
	short  dchanbits = 0;
	short seconds = 0;
	
	ERR_CODE error;

	
	com4_rxbuffer[COM4_RXBUFFER_LEN] = '*';

	if (com4_rxbuffer[COM4_RXBUFFER_LEN] != '*' ) {
		printf("error: receive buffer overflowed\n");
		printf("com4_rxbuffer[%d]=0x%0x\n", COM4_RXBUFFER_LEN, com4_rxbuffer[COM4_RXBUFFER_LEN] );
	} 
	
	get_options( &opts, argc, argv );

	if (opts.verbose >= 0)
		DVSI_copyright();

	if (opts.waitkey) {
		printf("Hit any key to continue...\n");
		fgetc( stdin );
	}
	
	echanbits = dchanbits = nchanbits( opts.rate );
	ASSERT( echanbits <= CHAN_BUF_SZ );
	ASSERT( dchanbits <= CHAN_BUF_SZ );
	
	if (opts.comport_name == 0) {
		printf("no COM port specified, or invalid comport\n");
		exit(0);
	}

		error = OpenPort( opts.comport_name,
				  com4_rxbuffer,
				  COM4_RXBUFFER_LEN,
				  opts.comport_baudrate,
				  COM4_DATA_BITS,
				  COM4_TIMEOUT,
				  &opts.comPort );

	
	if (error) {
		printf("error %d openning comport %s\n", error, opts.comport_name );
		exit(0);
	}

	if (opts.getversion) {
		char packet[7];
		char product_id[20];
		char version_data[48];
		
		/*
		 * switch the HDK to packet mode, using PPT interface.
		 * But, if the HDK is in a3kdirect mode skip this,
		 * the version packet is sent directly to the a3k.
		 */
		if (!opts.a3kdirect)
			switch_hdk_mode( packet, 9, opts.comPort );

		get_a3k_version( product_id, version_data, opts.comPort );
		printf("Product=<%s>, Version=<%s>\n", product_id, version_data );

		/*
		 * Unless the board is in a3k direct mode, query
		 * version data from the MSP.  If it is in a3kdirect
		 * mode then skip this step, we can not access the
		 * version info from the MSP because we are only
		 * talking to the a3k (MSP is bypassed).
		 */
		if (!opts.a3kdirect) {
			/*
			 * switch the HDK back to idle mode
			 */
			switch_hdk_mode( packet, HDKMODE_IDLE, opts.comPort );
		
			/*
			 * we also need to create a way to get the version from
			 * the MSP
			 */
			get_hdk_version( version_data, opts.comPort );
			printf("Product=<HDK-3000>, Version=<%s>\n", version_data );
		}
		
		ClosePort( opts.comPort );
		exit(0);

	}
	
	if (opts.sendhdkmode) {
		char packet[7];
		int packet_len;
		/*
		 * create an hdkcontrol packet that tells the
		 * hdk to change to the specified mode.  Then
		 * send the packet to the HDK.  Note that
		 * the "-mode" command line argument should not
		 * be used together with "-a3kdirect", but in
		 * case it is we just skip sending the packet
		 * to change hdk mode.  And since we just exit
		 * after this, the command accomplishes nothing.
		 */
		printf("switching to mode %d\n", opts.hdkmode );
		if (!opts.a3kdirect)
			switch_hdk_mode( packet, opts.hdkmode, opts.comPort );

		ClosePort( opts.comPort );
		exit(0);
	} else if (opts.codec && opts.passthru) {
		/*
		 * This is the code for codec mode with passthru
		 * enabled.
		 */
		long frame = 0;
		char packet[350];
		int packet_len;
		short speech_buf_in[160];
		short mode = (opts.packetif == PACKET_PPT) ? HDKMODE_CODEC_PASSTHRU_PPT : HDKMODE_CODEC_PASSTHRU_UART;

		if (!opts.a3kdirect)
			switch_hdk_mode( packet, mode, opts.comPort );

		a3k_control_packet( &opts, opts.comPort );

		a3k_startcodec( &opts, opts.comPort );
		/*
		 * this loop terminates when the input file
		 * runs out, or when the number of seconds
		 * elapsed reaches the time specified for
		 * record.
		 */
		for ( ; ; ) {
			short rp;
			short ecmode = 0;
			short dcmode = 0;

			if (opts.play) {
				if ( get_speech( speech_buf_in, 160, opts.fpi, opts.compand ) <= 0 )
					break;
			} else {
				short i;
				for ( i = 0; i < 160; i++)
					speech_buf_in[i] = 0;
			}

			rp = ReadPacketPort( packet, &packet_len, 0, opts.comPort );

			if (rp) {
				printf("error reading port, trying to read speech packet\n");
				exit(0);
			}

			decode_speech_packet( speech_buf, &dcmode, packet, (unsigned char)160, (short)packet_len, 0 );

			packet_len = encode_speech_packet( packet, speech_buf_in, 0, 1, (unsigned char)160, ecmode, 0 );

			WritePacketPort( packet, packet_len, opts.comPort );

			if (opts.record) {
				/*
				 * the first 120 samples from the codec
				 * are not good, so we just thow away
				 * the first 160
				 */
			//	if (frame > 0) {
					put_speech( speech_buf, 160, opts.fpo, opts.compand );
			//	}
			}

			if ((frame % 50) == 49) {
				seconds++;
				printf(".%d", seconds );
			}

			frame++;
			if ((opts.record) && (!opts.play)) {
				if (frame == 50*opts.seconds/*+1*/)
					break;
			}
		}

		printf("\n");
		if (0 != a3k_stopcodec( opts.comPort )) {
			printf("codec could not be stopped\n");
		}
		
		if (!opts.a3kdirect)
			switch_hdk_mode( packet, HDKMODE_IDLE, opts.comPort );

		ambe_close_files( &opts );

		ClosePort( opts.comPort );
		return ( 0 );



	} else if (opts.codec) {
		/*
		 * this is the code for codec mode with passthru
		 * disabled.
		 */
		long frame = 0;
		char packet[100];
		char product_id[20];
		char version_data[48];
		int packet_len;
		short mode = (opts.packetif == PACKET_PPT) ? HDKMODE_CODEC_PPT : HDKMODE_CODEC_UART;			
		short rem = (echanbits & 0x0007);
		short chanbytes = echanbits >> 3;
		if (rem != 0)
			chanbytes++;


		if (!opts.a3kdirect)
			switch_hdk_mode( packet, mode, opts.comPort );

//		get_a3k_version( product_id, version_data, opts.comPort );
//		printf("Product=<<<%s>>>, Version=<<<%s>>>\n", product_id, version_data );

		a3k_control_packet( &opts, opts.comPort );

		a3k_startcodec( &opts, opts.comPort );

		/*
		 * this loop terminates when the input file
		 * runs out, or when the number of seconds
		 * elapsed reaches the time specified for
		 * record.
		 */
		for ( ; ; ) {
			short rp;
			short ecmode;
			short dcmode = 0;
			short i;

			/*
			 * Now read back a packet
			 */
			rp = ReadPacketPort( packet, &packet_len, 0, opts.comPort );

			if (rp)
				printf("error reading port, trying to read channel packet\n");

				
			/*
			 * Now extract data from the packet
			 */
			decode_channel_packet( chan_buf, &dcmode, packet, (short)packet_len, echanbits );

			/*
			 * need to pad with 0's to get an integral number of
			 * bytes.
			 */
			for ( i = 0; i < 8-rem; i++ )
				chan_buf[echanbits+i] = 0;

			if (opts.record)
				put_packed_bits( chan_buf, (short)(chanbytes*8), opts.sd_bits, opts.fpo );				

			/*
			 * now read the channel data from a file, if
			 * available.  if no channel data from a file
			 * is available then just loop back the
			 * chan_buf that was received.
			 */
			if (opts.play) {

				if ( get_packed_bits(chan_buf,(short)(chanbytes*8),opts.sd_bits,opts.fpi) != chanbytes*8 )
					break;
			}

			ecmode = 0;

			if ( opts.nsprsn_enabled )
				ecmode |= NS_ENABLE_FLAG;

			if ( opts.tone_det_enabled )
				ecmode |= TONE_DET_ENABLE_FLAG;


			/*
			 * note that we send the bits that we are
			 * recording to the decoder, but if play is not
			 * enabled then we tell the decoder to mute.
			 * If you don't do this then you hear yourself
			 * while recording.
			 */
			if (!opts.play)
				ecmode |= CNI_FRAME_FLAG;
			
			packet_len = encode_channel_packet( packet, chan_buf, opts.sd_bits, ecmode, (unsigned char)160, echanbits );

			/*
			 * send the packet to the hdk via COM port
			 */
			WritePacketPort( packet, packet_len, opts.comPort );

			if ((frame % 50) == 49) {
				seconds++;
				printf(".%d", seconds );
			}

			frame++;
			if ((opts.record) && (!opts.play)) {
				if (frame/50 == opts.seconds)
					break;
			}
		}

		Sleep( 50 );
		printf("\n");
		if (0 != a3k_stopcodec( opts.comPort )) {
			printf("codec could not be stopped\n");
		}

		if (!opts.a3kdirect)
			switch_hdk_mode( packet, HDKMODE_IDLE, opts.comPort );

		ambe_close_files( &opts );

		ClosePort( opts.comPort );

		return ( 0 );
	} else {
		/*
		 * this is the code for packet mode.
		 */
		char packet[100];
		char product_id[20];
		char version_data[48];
		short mode = (opts.packetif == PACKET_PPT) ? HDKMODE_PACKET_PPT : HDKMODE_PACKET_UART;
		int packet_len;

		if (!opts.a3kdirect)
			switch_hdk_mode( packet, mode, opts.comPort );

		a3k_control_packet( &opts, opts.comPort );
		
//		get_a3k_version( product_id, version_data, opts.comPort );
//		printf("Product=<<<%s>>>, Version=<<<%s>>>\n", product_id, version_data );

		for ( ;; ) {

			if (com4_rxbuffer[COM4_RXBUFFER_LEN] != '*' ) {
				printf("error: receive buffer overflowed\n");
				printf("com4_rxbuffer[%d]=0x%0x\n", COM4_RXBUFFER_LEN, com4_rxbuffer[COM4_RXBUFFER_LEN] );
			} 

			if ( opts.verbose > 1 )
				printf( "frame: %ld\n", frame );


			if ( opts.run_encoder ) {

				static short encdone = 0;

				if (!encdone) {
					encdone = 
					a3k_run_encoder( chan_buf,
						echanbits,
						speech_buf,
						&opts,
						&cni );
				} else {
					e_r_last = 0;
				}
				
				if (!opts.run_decoder) {
					if (encdone)
						break;
					/*
					 * if the decoder is running
					 * but the encoder is done,
					 * wait till decoder finishes.
					 */
				}

			}

		
			if ( opts.run_decoder ) {
				short decdone;

				decdone = 
					 a3k_run_decoder( speech_buf,
					chan_buf,
					dchanbits,
					&opts,
					&dtx_frames );

				if ( decdone )
					break;
			}


			if ((frame % 50) == 49) {
				seconds++;
				printf(".%d", seconds );
			}
			frame++;

		}
		printf("\n");

				if (!opts.a3kdirect)
			switch_hdk_mode( packet, HDKMODE_IDLE, opts.comPort );


	}

	ClosePort( opts.comPort );

	ambe_close_files( &opts );

	return ( 0 );
}

/******************************************************************************/
