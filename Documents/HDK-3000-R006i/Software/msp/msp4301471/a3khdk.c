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

#define xstr(s) str(s)
#define str(s) #s

//#define REVISION1 1
/*
 * This string gets sent from the MSP to the PC when you query for the version using -version
 */
const char *hdk_version_string = "1.0.3 " __DATE__ " " xstr(__TI_COMPILER_VERSION__);


#include "msp430x14x1.h"
#include "a3kpacket.h"
#include "hardware.h"

#define PKT_HDKTYPE	0x04	//this is the type byte for HDK packets

#define PKT_HDKMODE	0x00
#define PKT_HDKREADY	0x01
#define PKT_HDKVERSION	0x02

#define IDLE_MODE	0
#define	PACKET_MODE	1
#define	CODEC_MODE	2
#define LOOPBACK_MODE	3
#define DUALHDK_MODE	4
#define DSPUART_MODE	5

#define PACKET_UART	0
#define PACKET_PPT	1
#define PACKET_MCBSP	2

#define DONTCARE	0

#define PASSTHRU_OFF	0
#define PASSTHRU_ON	1

#define SKEW_OFF	0
#define SKEW_ON		1

#define ECHO_OFF	0
#define ECHO_ON		1


/*
 * HDK Mode definitions
 */
 
#define HDKMODE(mode,packetif,passthru,skew,echo) ((mode)|((packetif)<<3)|((passthru)<<5)|((skew)<<6)|((echo)<<7))

#define HDKMODE_IDLE			HDKMODE(IDLE_MODE,       0,0,0,0)
#define HDKMODE_FIFOOVERFLOW0		HDKMODE(IDLE_MODE,       0,0,0,1)
#define HDKMODE_FIFOOVERFLOW1		HDKMODE(IDLE_MODE,       0,0,1,1)
#define HDKMODE_FIFOOVERFLOW2		HDKMODE(IDLE_MODE,       0,1,0,1)
#define HDKMODE_FIFOOVERFLOW3		HDKMODE(IDLE_MODE,       0,1,1,1)
#define HDKMODE_PACKET_PPT		HDKMODE(PACKET_MODE,   PACKET_PPT, PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_PACKET_UART		HDKMODE(PACKET_MODE,   PACKET_UART,PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_CODEC_PPT		HDKMODE(CODEC_MODE,    PACKET_PPT, PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_CODEC_UART		HDKMODE(CODEC_MODE,    PACKET_UART,PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_CODEC_PASSTHRU_PPT	HDKMODE(CODEC_MODE,    PACKET_PPT, PASSTHRU_ON ,SKEW_OFF,ECHO_OFF)
#define HDKMODE_CODEC_PASSTHRU_UART	HDKMODE(CODEC_MODE,    PACKET_UART,PASSTHRU_ON ,SKEW_OFF,ECHO_OFF)
#define HDKMODE_LOOPBACK_VOCODER_PPT	HDKMODE(LOOPBACK_MODE, PACKET_PPT, PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_LOOPBACK_VOCODER_UART	HDKMODE(LOOPBACK_MODE, PACKET_UART,PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_LOOPBACK_PASSTHRU_PPT	HDKMODE(LOOPBACK_MODE, PACKET_PPT, PASSTHRU_ON ,SKEW_OFF,ECHO_OFF)
#define HDKMODE_LOOPBACK_PASSTHRU_UART	HDKMODE(LOOPBACK_MODE, PACKET_UART,PASSTHRU_ON ,SKEW_OFF,ECHO_OFF)
#define HDKMODE_DUALHDK			HDKMODE(DUALHDK_MODE,  PACKET_PPT, PASSTHRU_OFF,SKEW_OFF,ECHO_OFF)
#define HDKMODE_DUALHDK_PASSTHRU	HDKMODE(DUALHDK_MODE,  PACKET_PPT, PASSTHRU_ON ,SKEW_OFF,ECHO_OFF)
#define HDKMODE_DUALHDKSKEW		HDKMODE(DUALHDK_MODE,  PACKET_PPT, PASSTHRU_OFF,SKEW_ON, ECHO_OFF)
#define HDKMODE_DUALHDKSKEW_PASSTHRU	HDKMODE(DUALHDK_MODE,  PACKET_PPT, PASSTHRU_ON ,SKEW_ON, ECHO_OFF)
#define HDKMODE_DUALHDKECHO		HDKMODE(DUALHDK_MODE,  PACKET_PPT, PASSTHRU_OFF,SKEW_ON, ECHO_ON )
#define HDKMODE_DUALHDKECHO_PASSTHRU	HDKMODE(DUALHDK_MODE,  PACKET_PPT, PASSTHRU_ON ,SKEW_ON, ECHO_ON )
#define HDKMODE_DSPUART			HDKMODE(DSPUART_MODE,  DONTCARE,   DONTCARE,    DONTCARE,DONTCARE )

#define HDKMODE_UNDEFINED HDKMODE_IDLE


#define ENABLE_UART0_RX_INTERRUPT	(IE1 |= URXIE0)
#define ENABLE_UART1_RX_INTERRUPT	(IE2 |= URXIE1)
#define ENABLE_UART0_TX_INTERRUPT	(IE1 |= UTXIE0)
#define ENABLE_UART1_TX_INTERRUPT	(IE2 |= UTXIE1)

#define DISABLE_UART0_RX_INTERRUPT	(IE1 &= ~URXIE0)
#define DISABLE_UART1_RX_INTERRUPT	(IE2 &= ~URXIE1)
#define DISABLE_UART0_TX_INTERRUPT	(IE1 &= ~UTXIE0)
#define DISABLE_UART1_TX_INTERRUPT	(IE2 &= ~UTXIE1)

//the mode leds are the 7 msbs of p2 and the lsb of p3
#define MODELEDS(x)	P2OUT &= 0xc1; P2OUT |= ~(((x) & 31)<<1); 

//P2OUT = ~((x<<1)|((x>>7)&1)|1) 

#define BOOT_MODE ((P3IN & BIT0) | (P2IN & (BIT7 | BIT6)))


#ifdef REVISION1
const unsigned char bitrev8[256] = {
	0,
	128,
	64,
	192,
	32,
	160,
	96,
	224,
	16,
	144,
	80,
	208,
	48,
	176,
	112,
	240,
	8,
	136,
	72,
	200,
	40,
	168,
	104,
	232,
	24,
	152,
	88,
	216,
	56,
	184,
	120,
	248,
	4,
	132,
	68,
	196,
	36,
	164,
	100,
	228,
	20,
	148,
	84,
	212,
	52,
	180,
	116,
	244,
	12,
	140,
	76,
	204,
	44,
	172,
	108,
	236,
	28,
	156,
	92,
	220,
	60,
	188,
	124,
	252,
	2,
	130,
	66,
	194,
	34,
	162,
	98,
	226,
	18,
	146,
	82,
	210,
	50,
	178,
	114,
	242,
	10,
	138,
	74,
	202,
	42,
	170,
	106,
	234,
	26,
	154,
	90,
	218,
	58,
	186,
	122,
	250,
	6,
	134,
	70,
	198,
	38,
	166,
	102,
	230,
	22,
	150,
	86,
	214,
	54,
	182,
	118,
	246,
	14,
	142,
	78,
	206,
	46,
	174,
	110,
	238,
	30,
	158,
	94,
	222,
	62,
	190,
	126,
	254,
	1,
	129,
	65,
	193,
	33,
	161,
	97,
	225,
	17,
	145,
	81,
	209,
	49,
	177,
	113,
	241,
	9,
	137,
	73,
	201,
	41,
	169,
	105,
	233,
	25,
	153,
	89,
	217,
	57,
	185,
	121,
	249,
	5,
	133,
	69,
	197,
	37,
	165,
	101,
	229,
	21,
	149,
	85,
	213,
	53,
	181,
	117,
	245,
	13,
	141,
	77,
	205,
	45,
	173,
	109,
	237,
	29,
	157,
	93,
	221,
	61,
	189,
	125,
	253,
	3,
	131,
	67,
	195,
	35,
	163,
	99,
	227,
	19,
	147,
	83,
	211,
	51,
	179,
	115,
	243,
	11,
	139,
	75,
	203,
	43,
	171,
	107,
	235,
	27,
	155,
	91,
	219,
	59,
	187,
	123,
	251,
	7,
	135,
	71,
	199,
	39,
	167,
	103,
	231,
	23,
	151,
	87,
	215,
	55,
	183,
	119,
	247,
	15,
	143,
	79,
	207,
	47,
	175,
	111,
	239,
	31,
	159,
	95,
	223,
	63,
	191,
	127,
	255,
};
#endif


/*******************************************************************************
* Software FIFO Structure
*******************************************************************************/	

/*
 * structure definition for a fifo.  Note that fileds that may be
 * changed by ISRs are declared volatile.
 */
typedef struct fifo_t {
	volatile char	*pnew;	// points to newest fifo element
	volatile char	*pold;	// points to oldest fifo element
	volatile short	nelem;	// number of bytes currently in fifo
	short	 blen;		// max length of fifo buffer in elements
	char	*bend;		// points to end of buffer
	char	   *b;		// points to start of buffer
} FIFO;

/*
 * structure definition for uart0 rx isr state
 */
typedef struct uart0rx_t {
	FIFO *fifo;
} UART0RX;

/*
 * structure definition for uart0 tx isr state
 */
typedef struct uart0tx_t {
	FIFO *fifo;
	volatile char active;
} UART0TX;

/*
 * structure definition for uart1 rx isr state
 */
typedef struct uart1rx_t {
	FIFO	           *fifo;	//points to the the fifo where uart1 packets will be stored
} UART1RX;

/*
 * structure definition for uart1 tx isr state
 */
typedef struct uart1tx_t {
	FIFO	  *fifo;		//points to the the fifo from which uart1 packets are transmitted
	volatile char active;		//current state of the uart1tx isr.
} UART1TX;

#define HDKCTLLEN 40
#define HDKREPLEN 40
#define TOA3KBLEN (300)
#define FROMA3KBLEN (300)

typedef struct hdk_t {		
	FIFO hdkcontrolfifo;		//FIFO where hdkcontrol packets from uart0 are stored
	FIFO   hdkreplyfifo;		//FIFO where hdkreply packets to uart0 are placed
	FIFO      toa3kfifo;		//FIFO where packets to the a3k are placed
	FIFO    froma3kfifo;		//FIFO where packets from the a3k are placed
	UART0RX     uart0rx;		//state for the uart0 rx isr
	UART0TX     uart0tx;		//state for the uart0 tx isr
	UART1RX     uart1rx;		//state for the uart1 rx isr
	UART1TX     uart1tx;		//state for the uart1 tx isr
	char  hdkcontrolbuf[HDKCTLLEN];	//buffer for the hdkcontrol fifo
	char    hdkreplybuf[HDKREPLEN];	//buffer for the hdkreply fifo
	char     froma3kbuf[FROMA3KBLEN];	//buffer for the froma3kfifo
	char       toa3kbuf[TOA3KBLEN];	//buffer for the toa3kfifo
	volatile char mode;		//current hdk mode
	volatile char     reset_mode;
	char      isr_relay;
} HDK;

HDK hdk;

#define BAUDRATE28800	0
#define BAUDRATE57600	1
#define BAUDRATE115200	2
#define BAUDRATE230400	3
#define BAUDRATE460800	4

#define BAUDRATESEL BAUDRATE460800

char ubr0x[5] = {
	115/*?*/,
	0x8a,
	0x45,
	0x22,
	0x11,
};

char umctlx[5] = {
	0xbb,
	0xef,
	0xaa,
	0xdd,
	0x52
};

static void
   cpuInit( void )
{
	int delay_x;

	WDTCTL= WDTPW + WDTHOLD;				//Stop watchdog timer

	//Set up ports while waiting for crystal

	//Port 1
	P1SEL = P1SEL_INIT;
	P1OUT = P1OUT_INIT;
	P1DIR = P1DIR_INIT;

	//Port 2
	P2SEL = P2SEL_INIT;
	P2OUT = P2OUT_INIT;
	P2DIR = P2DIR_INIT;
	P2IES = P2IES_INIT;
	P2IFG = 0;
	P2IE  = P2IE_INIT;

	//Port 3
	P3SEL = P3SEL_INIT;
	P3OUT = P3OUT_INIT;
	P3DIR = P3DIR_INIT;

	//Port 4
	P4SEL = P4SEL_INIT;
	P4OUT = P4OUT_INIT;
	P4DIR = P4DIR_INIT;

	//Port 5
	P5SEL = P5SEL_INIT;
	P5OUT = P5OUT_INIT;
	P5DIR = P5DIR_INIT;

	//Port 6
	P6SEL = P6SEL_INIT;
	P6OUT = P6OUT_INIT;
	P6DIR = P6DIR_INIT;

	BCSCTL1 = XTS + XT2OFF;

	//wait for LFXT1 osc to come up
	//clear osc fault flag & set delay count
	//exit loop when no fault for delay count

	for (IFG1 &= ~OFIFG, delay_x = 255; delay_x;) {
		if (IFG1 & OFIFG) {                      //check osc fault flag
			//IT's set
			IFG1 &= ~OFIFG;                  //clear flag
			delay_x = 255;                   //reset delay
		} else
			--delay_x;
	}

	BCSCTL2 = SELM0 + SELM1;

	//Set up UART0
	ME1 |= UTXE0 + URXE0;                   // Enable USART0 TXD/RXD
	UCTL0 |= CHAR;                          // 8-bit character
	UTCTL0 |= SSEL0;                		// UCLK = ACLK
	UBR00 = ubr0x[BAUDRATESEL];
	UBR10 = 0x00;                           // 8MHz 460800
	UMCTL0 = umctlx[BAUDRATESEL];
	UCTL0 &= ~SWRST;                        // Initialize USART state machine


	//Set up UART1
	ME2 |= UTXE1 + URXE1;                   // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                          // 8-bit character
	UTCTL1 |= SSEL0;                		// UCLK = ACLK
	UBR01 = ubr0x[BAUDRATESEL];
	UBR11 = 0x00;                           // 8MHz 460800
	UMCTL1 = umctlx[BAUDRATESEL];
	UCTL1 &= ~SWRST;                        // Initialize USART state machine

	//Timer A init	
	TACTL = 0x0000;
}

void
   delay( void )
{
	volatile unsigned int i;
	i = 1;
	while (i != 0){
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		i--;
	}
}

void
   long_delay( void )
{
	volatile unsigned long i;
	i = 56000;
	while (i != 0){
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		i--;
	}
}
void
   super_long_delay( void )
{
	volatile unsigned long i;
	i = 560000;
	while (i != 0){
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
		i--;
	}
}

static inline char
   ppt_getchar( void )
{
	char c;
	
	/*
	 * make sure PPT_ACK is high first.
	 */
#if 1
	while (!(P1IN & PPT_ACK));
#endif
	/*
	 * from the time we set PPT_RD low until we
	 * read the data, we need this task to be
	 * highest priority (it wont take long).  The
	 * a3k PPT isr will be sitting in a loop
	 * waiting.  It is very important when the PPT
	 * is used, that the device connecting to the
	 * a3k reacts very quickly to PPT_ACK.  I would
	 * highly recommend that PPT_ACK be tied to
	 * an interrupt.  Its not on the vc55 however.
	 */
	 
	/*
	 * now set PPT_RD low (signal is active low)
	 */
	//_disable_interrupts();
	P3OUT &= ~PPT_RD;
	/*
	 * now wait for PPT_ACK to go low.
	 */
#if 1	
	while ((P1IN & PPT_ACK));
#endif	

	/*
	 * now read the data.
	 */
	c = P4IN;
	/*
	 * finally drive PPT_RD high to complete the
	 * transaction.
	 */
	P3OUT |= PPT_RD;
	//_enable_interrupts();

#ifdef REVISION1
	return bitrev8[(unsigned char) c];
#else
	return (unsigned char) c;
#endif
	
}


static void
   ppt_putfirstchar( char c )
{
	/*
	 * make sure PPT_ACK is high first.
	 */
	while (!(P1IN & PPT_ACK));
	/*
	 * now set PPT_WR low (signal is active low)
	 * and also set the 8 data pins at the same
	 * time.
	 */
	P4DIR |= 0xff;

#ifdef REVISION1	
	P4OUT = bitrev8[(unsigned char) c];
#else
	P4OUT = (unsigned char) c;
#endif 	

	//_disable_interrupts();
	P1OUT &= ~0x04;
	P3OUT &= ~PPT_WR;
	
	/*
	 * now wait for PPT_ACK to go low.  (This tells
	 * us that the A3K has read the data).
	 */
	while ((P1IN & PPT_ACK));
	
	/*
	 * finally, set PPT_WR high again.
	 */
	P3OUT |= PPT_WR;
	//_enable_interrupts();
}


static inline void
   ppt_putchar( char c )
{
	/*
	 * make sure PPT_ACK is high first.
	 */
#if 1
	while (!(P1IN & PPT_ACK));
#endif
	/*
	 * now set PPT_WR low (signal is active low)
	 * and also set the 8 data pins at the same
	 * time.
	 */
	P4DIR |= 0xff;
#ifdef REVISION1
	P4OUT = bitrev8[(unsigned char) c];
#else
	P4OUT = (unsigned char) c;
#endif 

	//_disable_interrupts();
	P3OUT &= ~PPT_WR;
	
	/*
	 * now wait for PPT_ACK to go low.  (This tells
	 * us that the A3K has read the data).
	 */
#if 1
	while ((P1IN & PPT_ACK));
#endif	
	/*
	 * finally, set PPT_WR high again.
	 */
	P3OUT |= PPT_WR;
	//_enable_interrupts();
}


/*
 * this function initializes a fifo
 */

static void
   fifo_init( FIFO    *f,
	      short blen,
	      char    *b )
{
	short i;
	for (i=0; i < blen; i++)
		b[i] = 0;
	f->pnew = f->pold = b;
	f->blen = blen;
	f->nelem = 0;
	f->bend = b + blen;
	f->b = b;
}

/*
 * This function adds a character to a fifo if there is free space in
 * the fifo.
 */
static void
   fifo_putc( FIFO *f,
	      char  c )
{
	if (f->blen == f->nelem) {
		return;	//fifo is full!!!
	} 
	_disable_interrupts();
	*f->pnew++ = c;
	if(f->pnew == f->bend)
		f->pnew = f->b;
	f->nelem += 1;
	_enable_interrupts();
}


/*
 * This function gets the next character from a fifo.  It is assumed
 * that the fifo contains at leas one character.  If it does not the
 * function returns a null character.
 */
static char
   fifo_getc( FIFO             *f )
{
	if (f->nelem) {
		char c;
		_disable_interrupts();
		c = *f->pold++;
		if(f->pold == f->bend)
			f->pold = f->b;
		f->nelem -= 1;
		_enable_interrupts();
		return c;
	} else
		return 0;

}

/*
 * This function does not take anything out of the fifo.  It assumes
 * that there is a complete packet in the fifo (or at least the
 * header/length/type).  It just looks at the 4th byte which is the
 * type byte and returns it.  In the event that the fifo does not
 * contain at least 4 bytes, it returns 0x0ff.
 */
static char
   fifo_peekpackettype( FIFO *f)
{

	char i;
	char c;
	volatile char *old = f->pold;
	for ( i = 0; i < 4; i++ ) {
		c = *old++;
		if (old == f->bend)
			old = f->b;
	}
	/*
	 * just return the forth byte.  Note that nelem wasn't
	 * decremented and the fifo pointers are unchanged.
	 * This function peeked into the fifo without changing
	 * it.
	 */
		return c;

}

/*
 * this function discards a packet from the fifo.
 */
static void
   fifo_discardpacket( FIFO *f ){
	/*
	 * one we get len we can just subtract len+1 from elem and
	 * then do a circular wrap around of the fifo pointer.
	 * for now i discard characters one at a time.
	 */
	char c;
	short len;
	short i;
	fifo_getc( f );
	c = fifo_getc( f );
	len = c;
	len <<= 8;
	c = fifo_getc( f );
	len |= (c & 0x00ff);
	len++;	//dont forget the type byte
	for ( i = 0; i < len; i++ ) {
		fifo_getc( f );		
	}
	
}

/*
 * This function just checks the fifo without modifying it, unless it
 * discovers that the header is missing.  When the fifo is missing
 * the header all data is discarded until a header is found.
 */
 
short dropped_packet = 0;
 
static char
   fifo_checkfullpacket( FIFO *f )
{
	short len;
	volatile char *old;
start:
	/*
	 * if there is a character in the fifo and it is not
	 * a header byte then discard it.  Keep going as
	 * long as there are still bytes in the fifo.  if a packet
	 * with bad parity is received it is discarded.
	 */
	while((f->nelem > 0) && ( *f->pold != PKT_HEADER )) {
		fifo_getc( f );
	}

	/*
	 * now we are either out of characters in the fifo
	 * or the first character is a header byte.  If we
	 * dont have at least the header byte and the two
	 * len bytes yet, then just return.
	 */
	if (f->nelem < 3)
		return 0;
 
	/*
	 * we now have the header and two len bytes in the
	 * fifo.
	 */
	old = f->pold + 1;
 
	if (old == f->bend)
		old = f->b;
 
	len = *old++;
	len <<= 8;
	if (old == f->bend)
		old = f->b;
	len |= *old++;
	if (len > 340){
		fifo_getc(f);
		goto start;
	}
	if ( f->nelem >= len+4) {
		/*
		 * we now have received a full packet.  We will
		 * check its parity.  if the parity is bad then
		 * we will discard the packet, and return 0.
		 * If the packet is good then we will return 1.
		 */
		short i;
		char parity = 0;

		parity ^= ((len >> 8) & 0x00ff);
		parity ^= (len & 0x00ff);
	
		if (old == f->bend)
			old = f->b;

		for(i=0;i<len+1;i++) {
			parity ^= *old++;
			if (old == f->bend)
				old = f->b;
		}
		if (parity == 0)
			return 1; //we have a full packet with good parity check
		else {
			fifo_discardpacket( f );
			dropped_packet++;
			return 0; 
		}
	} else
		return 0;
}

static void
   fifo_waitpacket( FIFO *f ){
	short len;
	volatile char *old;

	/*
	 * if there is a character in the fifo and it is not
	 * a header byte then discard it.  Keep going as
	 * long as there are still bytes in the fifo.
	 */
	while((f->nelem > 0) && ( *f->pold != PKT_HEADER )) {
		fifo_getc( f );
	}

	old = f->pold;	//old points to the header byte
	
	while (f->nelem < 3);
	
	old++;		//old points to msb of len
	
	if (old == f->bend)
		old = f->b;

	len = *old++;	//read msb, then old points to lsb of len
	len <<= 8;
	if (old == f->bend)
		old = f->b;
	len |= *old++;

	while( f->nelem < len+4 );
}


/*
 * This function removes a packet from a fifo and places it into a
 * buffer.  It assumes that there is a complete packet in the fifo.
 * returns the packet length.
 */
static short
   fifo_getpacket( char *p,
		   FIFO *f )
{
	short len;
	short i;

	p[0] = fifo_getc( f );	//get the header
	p[1] = fifo_getc( f );	//get the len (msb)
	p[2] = fifo_getc( f );	//get the len (lsb)
	p[3] = fifo_getc( f );	//get the type
	len = p[1];
	len <<= 8;
	len |= (p[2] & 0x00ff);
	p += 4;
	for ( i = 0; i < len; i++ ) {
		*p++ = fifo_getc( f );
	}
	return len+4;
}

/*
 * This function puts a packet from a buffer into a fifo.
 */
static void
   fifo_putpacket( char *p,
		   FIFO *f )
{
	short len;
	short i;

	len = (((short)p[1])<<8)|p[2];
	len += 4;
	
	for ( i = 0; i < len; i++ ) {
		fifo_putc( f, *p++ );
	}
}

char expected_packet[] = { 0x61,0x00,0x0d,0x01,0x01,0x48,0x8c,0x88,0x89,0x8a,0x8c,0x09,0x80,0x02,0x84,0x2f,0xee };


static void
   fifo_forwardpackettoppt( FIFO *f )
{
	char c;
	short len;
	short i;
	ppt_putfirstchar( c = fifo_getc( f ) );
	ppt_putchar( c = fifo_getc( f ) );
	len = c;
	len <<= 8;
	ppt_putchar( c = fifo_getc( f ) );
	len |= (c & 0x00ff);
	len++;	//dont forget the type byte
	for ( i = 0; i < len; i++ ) {
		ppt_putchar( c = fifo_getc( f ) );
	}
	P1OUT |= 0x04;
}

/*
 * This function reads a packet from the a3k's ppt and puts it into a
 * fifo.  This code assumes that the a3k has set TXRDY indicating
 * that it has a packet ready for us to read.
 */
static void
   fifo_putpacketfromppt( FIFO *f )
{
#if 0
	P4DIR &= ~0xff; // Set P4 to Input so we can read PPT pins
	do {
		char c = ppt_getchar();
		/*
		 * fifo_putchar must block if
		 * there is not enough room in
		 * the fifo.  The ppt may be
		 * faster than uart0.
		 */
		fifo_putc( f, c );
	} while (P1IN & TXRDY );
	P4DIR |= 0xff; // Set P4 back to output
#else
	char c;
	short i;
	short len;
	P4DIR &= ~0xff; // Set P4 to Input so we can read PPT pins
	do {
		c = ppt_getchar();
	} while (c != PKT_HEADER);
	fifo_putc( f, c );
	c = ppt_getchar();
	fifo_putc( f, c );
	len = c;
	len <<= 8;
	c = ppt_getchar();
	fifo_putc( f, c );
	len |= c & 0x00ff;
	len++;
	for ( i = 0; i < len; i++ ) {
		fifo_putc( f, ppt_getchar() );
	}
	P4DIR |= 0xff; // Set P4 back to output
#endif
}

/*
 * this function reads a packet from ppt and wraps it back to the ppt
 * without using a buffer.  It alternates read then write.
 */
static void
   ppt_wrap_packet( void )
{
	char c;
	P4DIR &= ~0xff; // Set P4 to Input so we can read PPT pins
	c = ppt_getchar();
	ppt_putfirstchar( c );
	while (P1IN & TXRDY) {
		P4DIR &= ~0xff; // Set P4 to Input so we can read PPT pins
		c = ppt_getchar();
		ppt_putchar( c );
	}
	P1OUT |= 0x04;	
}

static void
   fifo_sendhdkcontrol( char field,
			FIFO    *f )
{
	fifo_putc( f, PKT_HEADER );
	fifo_putc( f, 0 );
	fifo_putc( f, 1 );
	fifo_putc( f, PKT_HDKTYPE );
	fifo_putc( f, field );
	ENABLE_UART0_TX_INTERRUPT;
}


static void
   fifo_sendhdkversion( FIFO    *f )
{
	const char *cp = hdk_version_string;

	fifo_putc( f, PKT_HEADER );
	fifo_putc( f, 0 );
	fifo_putc( f, 2+strlen(hdk_version_string) );
	fifo_putc( f, PKT_HDKTYPE );
	fifo_putc( f, PKT_HDKVERSION );

	do {
		fifo_putc( f, *cp );
	} while (*cp++ != 0);

	ENABLE_UART0_TX_INTERRUPT;
}

/*
 * This function decodes an HDK control packet contained within the
 * fifo.  It assumes that the fifo contains an HDKCONTROL packet.
 *
 * At the present moment, only one field is defined for HDK control
 * packets.  This field allows the HDK mode to be changed.  In the
 * future we may add other HDK control fields.
 */
static void
   fifo_decodehdkcontrolpacket( FIFO *f )
{
	short len;
	char field;
	fifo_getc( f );	//discard header
	len = fifo_getc( f );
	len <<= 8;
	len |= (fifo_getc( f ) & 0x00ff);
	fifo_getc( f ); //discard type

	field = fifo_getc(f);
	len--;
	if (field == PKT_HDKMODE) {
		hdk.mode = fifo_getc(f);
		hdk.reset_mode = 1;
		len--;
	} else if (field == PKT_HDKVERSION) {
		/*
		 * for now we assume that the HDK is always in idle
		 * mode when it receives this packet.
		 */
		fifo_sendhdkversion( hdk.uart0tx.fifo );
	}
	
	while (len > 0) {
		fifo_getc(f);
		len--;
	}
}



char hdkcontroldetect = 0;
const char hdkcontrol[5] = { 0x61, 0x00, 0x04, 0x04, 0x00 };
/*
 * uart0 is connected to tusb.  packets received via this interface are
 * always parsed for HDKCONTROL packets before they are passed to the
 * a3k.  Since the usb interface is fast relative to other interfaces
 * the fifo must be large.
 */
interrupt void uart0_rx_isr(void);

ISR_VECTOR( uart0_rx_isr, ".int09")

volatile char rxflag = 0;

short writeidx = 0;
char rxbuf[8];

interrupt void
   uart0_rx_isr( void )
{
	if (hdk.isr_relay > 1) {
		char rxbyte;

		/*
		 * for this mode, characters received via uart0 are
		 * added to a short buffer.  This mode is used in
		 * conjunction with ppt_monitor to relay bytes
		 * received via uart0 to the a3k PPT.
		 */
		rxbyte = rxbuf[writeidx] = RXBUF0;
		writeidx = (writeidx+1) & 7;
		rxflag++;
		
		/*
		 * detector for hdkcontrol packets.
		 */
		if (hdkcontroldetect == 0) {
			if (rxbyte == 0x61)
				hdkcontroldetect = 1;
		} else if (hdkcontroldetect < 5) {
			if (rxbyte == hdkcontrol[hdkcontroldetect]) 
				hdkcontroldetect++;
			else
				hdkcontroldetect = 0;
		} else if (hdkcontroldetect == 5) {
			hdk.mode = rxbyte;
			hdkcontroldetect=6;
		} else if (hdkcontroldetect == 6) {
			hdkcontroldetect=7;
		} else { /* hdkcontroldetect == 7*/ 
			hdk.reset_mode = 1;
			hdkcontroldetect=0;			
		}


	} else if (hdk.isr_relay == 1) {
		char rxbyte;
		/*
		 * this mode just relays characters received on uart0
		 * to be output on uart1
		 */
		_enable_interrupts();

		TXBUF1 = rxbyte = RXBUF0;

		/*
		 * detector for hdkcontrol packets.
		 */
		if (hdkcontroldetect == 0) {
			if (rxbyte == 0x61)
				hdkcontroldetect = 1;
		} else if (hdkcontroldetect < 5) {
			if (rxbyte == hdkcontrol[hdkcontroldetect]) 
				hdkcontroldetect++;
			else
				hdkcontroldetect = 0;
		} else if (hdkcontroldetect == 5) {
			hdk.mode = rxbyte;
			hdkcontroldetect=6;
		} else if (hdkcontroldetect == 6) {
			hdkcontroldetect=7;
		} else { /* hdkcontroldetect == 7*/ 
			hdk.reset_mode = 1;
			hdkcontroldetect=0;			
		}


	} else {
		*hdk.uart0rx.fifo->pnew = RXBUF0; //read the character from UART0
		hdk.uart0rx.fifo->pnew++;
		if(hdk.uart0rx.fifo->pnew == hdk.uart0rx.fifo->bend)
			hdk.uart0rx.fifo->pnew = hdk.uart0rx.fifo->b;
		hdk.uart0rx.fifo->nelem++;
	}
}



interrupt void uart0_tx_isr( void );

ISR_VECTOR( uart0_tx_isr, ".int08")
interrupt void
   uart0_tx_isr( void )
{
	_enable_interrupts();
 	TXBUF0 = *hdk.uart0tx.fifo->pold;
 	hdk.uart0tx.fifo->pold++;
 
 	if (hdk.uart0tx.fifo->pold == hdk.uart0tx.fifo->bend)
  		hdk.uart0tx.fifo->pold = hdk.uart0tx.fifo->b;
  	_disable_interrupts();
 	hdk.uart0tx.fifo->nelem -= 1;  
 
 	if (hdk.uart0tx.fifo->nelem == 0) {
  		hdk.uart0tx.active = 0;
  		DISABLE_UART0_TX_INTERRUPT;
 	}
}


interrupt void uart1_rx_isr( void );

ISR_VECTOR( uart1_rx_isr, ".int03")
interrupt void
   uart1_rx_isr( void )
{

	if( !hdk.isr_relay) {
		*hdk.uart1rx.fifo->pnew /*= TXBUF0*/ = RXBUF1; //read the character from UART1
		hdk.uart1rx.fifo->pnew++;
		if(hdk.uart1rx.fifo->pnew == hdk.uart1rx.fifo->bend)
			hdk.uart1rx.fifo->pnew = hdk.uart1rx.fifo->b;
		hdk.uart1rx.fifo->nelem++;

	} else {
		_enable_interrupts();
		TXBUF0 = RXBUF1;
	}
}


interrupt void uart1_tx_isr( void );

ISR_VECTOR( uart1_tx_isr, ".int02")
interrupt void
   uart1_tx_isr( void )
{
	_enable_interrupts();

	
 	TXBUF1 = *hdk.uart1tx.fifo->pold;
 
 	hdk.uart1tx.fifo->pold++;
 
 	if (hdk.uart1tx.fifo->pold == hdk.uart1tx.fifo->bend)
  		hdk.uart1tx.fifo->pold = hdk.uart1tx.fifo->b;
  	_disable_interrupts();
 	hdk.uart1tx.fifo->nelem--;  
	_enable_interrupts();
 	if ( hdk.uart1tx.fifo->nelem == 0){
  		hdk.uart1tx.active = 0;
  		DISABLE_UART1_TX_INTERRUPT;
 	}
 
}


interrupt void packet_timer(void);
ISR_VECTOR( packet_timer, ".int06")
interrupt void
   packet_timer( void ){
	P5OUT &= ~TXRQST;
	TACTL = TACLR;
}


static char *
   put_next_byte( char *p, short val )
{
	*p++ =  val;
	return p;
}
static char *
   put_next_word( char *p, short val )
{
	*p++ = (val >> 8) & 0x00ff;
	*p++ = val & 0x00ff;
	return p;
}


static char *
   get_next_byte( char *p, short *val )
{
	*val = *p++ & 0x00ff;
	return p;
}


static char *
   get_next_word( char *p, short *val )
{
	*val = *p++;
	*val <<= 8;
	*val |= *p++;
	return p;
}


static void
   put_packet( char    *packet,
	       char       *end,
	       char       type,
	       char     parity,
	       short interface )
{
	char *p = packet;
	short len = end - packet - 4;
	if (parity)
		len += 2;

	/*
	 * add the header, length, and type
	 */
	p = put_next_byte( p, PKT_HEADER );
	p = put_next_word( p, len );
	p = put_next_byte( p, type );

	/*
	 * from this point on, len is the total length of the
	 * packet including header/len/type
	 */
	len += 4;
	
	/*
	 * add the parity field if enabled. Note that the parity
	 * byte does not cover the header byte.  
	 */
	if (parity) {
		short i;
		char pbyte = 0;
		end = put_next_byte( end, PKT_PARITYBYTE );
		for ( i = 1; i < len - 1; i++ ) {
			pbyte ^= packet[i];
		}
		end = put_next_byte( end, pbyte );
	}

	      
	if (interface == PACKET_UART) {

		fifo_putpacket( packet,
				&hdk.toa3kfifo );

		ENABLE_UART1_TX_INTERRUPT;
		
	} else if (interface == PACKET_PPT) {
		short i;	
		/*
		 * write out a len-byte packet.
		 */
		ppt_putfirstchar( *packet++ );
		for ( i = 1; i < len ; i++ ) {

			ppt_putchar( *packet++ );

		}
		P1OUT |= 0x04;
	} else { //interface == PACKET_MCBSP
		//MCBSP packet interface not implemented yet.
		return; 
	}
}

static short
   get_packet( char    *packet,
	       short interface )
{
	short len;

	if (interface == PACKET_UART) {
	
		fifo_waitpacket( &hdk.froma3kfifo );
		
		return fifo_getpacket( packet,
				&hdk.froma3kfifo );
		
	} else if (interface == PACKET_PPT) {
		char *p = packet;

		P4DIR &= ~0xff; // Set P4 to Input

		while(!(P1IN & TXRDY));		//waiting for packet ready to go high

		/*
		 * keep reading bytes from the A3K PPT until TXRDY goes
		 * low.
		 */
		do {
			*p++ = ppt_getchar();
		} while(P1IN & TXRDY);

		P4DIR |= 0xff; // Set P4 to output

		len = (packet[1] << 8) + packet[2];

		return len+4;
	} else {	/*interface == PACKET_MCBSP*/
		//this interface is not implemented yet.	
	}
	return 0;
}

short ready_packet = 0;
static short
wait_a3k_ready( short interface )
{
    char packet[30];
    short i;
    for (i = 0;i < 30; i++)
    	packet[i] = 0xFF;

    if (interface == PACKET_PPT) {
	    //after reset, it takes some time before TXRDY is valid
	    //we wait for TXRDY to be low
	    while(P1IN & TXRDY);	//waiting for packet ready to go low

    }

    
    get_packet( packet, interface );
    
    if (packet[0] != 0x61)
    	return (1);
    if (packet[1] != 0x0)
    	return (2);
    if (packet[2] != 0x03)
    	return (3);
    if(packet[3] != 0x0)
    	return (4);
    if(packet[4] != 0x39)
    	return (5);
    if(packet[5] != 0x2f)
    	return (6);
    if (packet[6] != (0x3^0x39^0x2f))
    	return (7);
   
    ready_packet++;
    /* we should verify that it is a ready packet, but for now we do not */
   return (0); 
}

/*
 * sending this packet turns the a3k vocoder back on
 */
static short
   config_a3k( short     ratet,
	       short  lowpower,
	       short interface )
{
	/*
	 * we can modify this to put characters into a fifo instead of
	 * a buffer.  We would then modify put_packet and get_packet
	 * to work with a fifo instead of a buffer.  This will save
	 * stack space and save code.  we would need to create
	 * fifo_putword() which puts two characters.
	 */
	char packet[30];
	char *p = packet+4;
	short chk_header, chk_len, chk_type, chk_field, chk_response_ok;
	short plen;

	if (ratet >= 0) {
		p = put_next_byte( p, PKT_RATET );
		p = put_next_byte( p, ratet );
	}
	p = put_next_byte( p, PKT_LOWPOWER );
	p = put_next_byte( p, lowpower );
	p = put_next_byte( p, PKT_INIT );
	p = put_next_byte( p, PKT_INIT_ENCODER|PKT_INIT_DECODER );
	
	put_packet( packet, p, PKT_CONTROL, 1, interface );

	//we expect a 9 byte response packet
	plen = get_packet( packet, interface );
	if (plen == 0) {
		return 1;
	}
	p = packet;
	p = get_next_byte( p, &chk_header );
	if (chk_header != PKT_HEADER)
		return -1;
	p = get_next_word( p, &chk_len  );

	if (ratet >= 0) {
		if (chk_len != 6+2) 
			return -2;
	} else {
		if (chk_len != 6) 
			return -2;
	}
	
	p = get_next_byte( p, &chk_type );
	if (chk_type != PKT_CONTROL)
		return -3;

	if (ratet >= 0) {
		p = get_next_byte( p, &chk_field);
		if (chk_field != PKT_RATET)
			return -4;
		p = get_next_byte( p, &chk_response_ok);
		if (chk_response_ok != PKT_RESPONSE_OK)
			return -5;
	}
	
	p = get_next_byte( p, &chk_field);
	if (chk_field != PKT_LOWPOWER)
		return -6;
	p = get_next_byte( p, &chk_response_ok);
	if (chk_response_ok != PKT_RESPONSE_OK)
		return -7;

	p = get_next_byte( p, &chk_field);
	if (chk_field != PKT_INIT)
		return -8;
	p = get_next_byte( p, &chk_response_ok);
	if (chk_response_ok != PKT_RESPONSE_OK)
		return -9;


	return 0;
}

short
packet_reset_a3k( short     packet_interface,
		  short new_packet_interface )
{
	char packet[30];
	char *p = packet+4;
	short cfg = (1<<13);	//noise suppressor on
	p = put_next_byte( p, PKT_RESETSOFTCFG );
	if (new_packet_interface == PACKET_UART) {
		cfg |= (5<<8);
	} else if (new_packet_interface == PACKET_PPT) {
		cfg |= (6<<8);
	} else {
		cfg |= (7<<8);
	}
	p = put_next_word( p, cfg );
	p = put_next_byte( p, 0 );
	p = put_next_word( p, 0x0700 );
	p = put_next_byte( p, 0 );
	put_packet( packet, p, PKT_CONTROL, 1, packet_interface );
	
	if (hdk.mode != HDKMODE_DSPUART)
		return (wait_a3k_ready( new_packet_interface ));	
	return 0;
}

static short
   config_a3k_codec(short interface )
{
	char packet[50];
	char *p = packet+4;
	short chk_header, chk_len, chk_type, chk_field, chk_response_ok;
	short plen;
	short INPUT_GAIN;
	short INPUT_SEL;
	short ADCGAIN;

	
	//Check jumper for input selection
	if (P5IN & BIT4){							//Jumper off = handset
		INPUT_GAIN = 0x3;
		INPUT_SEL = 0x2;
		ADCGAIN = 0x3e;		//20 dB
	} else {
		INPUT_GAIN = 0;		//0 dB					//jumper on = line in
		INPUT_SEL = 0x3;
		ADCGAIN = 0x2a;		//0 dB
	}
	
//	INPUT_GAIN = 0x0;


#if 0
	/*
	 * there is two ways to set up the codec.  This is the first
	 * method.  Use PKT_CODECCFG to specify what control registers
	 * to change and the new values.  Then later they will be
	 * sent to the codec when the PKT_CODECSTART is sent.
	 */
	p = put_next_byte( p, PKT_CODECCFG );
	p = put_next_byte( p, 6 );
	p = put_next_word (p, (2<<8)|	(1<<7)|(4<<3));				// set TURBO=1 (SCLK=MCLK/P), keep I2C addr=4
	p = put_next_word (p, (1<<8)|	1|(1<<6) /*|(1<<5)*/ );			// set 16 bit DAC mode, set continuous data transfer mode
	p = put_next_word (p, (4<<8)|	0x80|3);					// set M=3
	p = put_next_word (p, (5<<8)|   ADCGAIN );
	p = put_next_word (p, (5<<8)|	0x80|(7<<3)| INPUT_GAIN);	// sidetone=MUTE / INPUT GAIN = 24dB ==> 0x3
	p = put_next_word (p, (6<<8)|	(INPUT_SEL<<1));			// set input LINE IN = 0x6	 MIC = 0x2
#else
	/*
	 * For the second method, use PKT_CODECCFG to specify that 0
	 * registers are configured by PKT_CODECSTART.  Then use
	 * PKT_SETCODECRESET to take the codec out of reset.  Use
	 * PKT_DELAYNUS to insert delay, then use PKT_WRITEI2C
	 * repeatedly to generate i2c writes.  This sets up the AIC14,
	 * later when PKT_CODECSTART is received, it will not try to
	 * reconfigure the aic14. All it does is enable the codec
	 * interface of the a3k without configuring the aic14 first.
	 * Either method works.  This method is more generic.
	 */
	p = put_next_byte( p, PKT_CODECCFG );
	p = put_next_byte( p, 0 );
	
	p = put_next_byte( p, PKT_SETCODECRESET );

	p = put_next_byte( p, PKT_DELAYNUS );
	p = put_next_word( p, 10 );

#define PKT_WRITEREG( p, reg, val ) p = put_next_byte( p, PKT_WRITEI2C ); p = put_next_byte( p, 3 ); p = put_next_byte( p, 0x80 ); p = put_next_byte( p, reg ); p = put_next_byte( p, val )

	p = PKT_WRITEREG (p, 2,	(1<<7)|(4<<3));				// set TURBO=1 (SCLK=MCLK/P), keep I2C addr=4
	p = PKT_WRITEREG (p, 1,	1|(1<<6) /*|(1<<5)*/ );			// set 16 bit DAC mode, set continuous data transfer mode
	p = PKT_WRITEREG (p, 4,	0x80|3);					// set M=3
	p = PKT_WRITEREG (p, 5,	ADCGAIN );
	p = PKT_WRITEREG (p, 5,	0x80|(7<<3)| INPUT_GAIN);	// sidetone=MUTE / INPUT GAIN = 24dB ==> 0x3
	p = PKT_WRITEREG (p, 6,	(INPUT_SEL<<1));			// set input LINE IN = 0x6	 MIC = 0x2	
#endif
	p = put_next_byte( p, PKT_DISCARDNCODEC );
	p = put_next_word( p, 128 );						//tell the a3k to discard the first 128 codec samples, output 0

	//final delay will delay response packet which puts some time
	//between config_a3k_codec and start_a3k_codec.
	p = put_next_byte( p, PKT_DELAYNUS );
	p = put_next_word( p, 10 );

	
	put_packet( packet, p, PKT_CONTROL, 1, interface );

	
	//we expect a 9 byte response packet
	plen = get_packet( packet, interface );
	if (plen == 0)
		return 1;
	
	return 0;
	
}

/*
 * this sends a packet to the a3k which causes the a3k to
 * 1. take the codec out of reset.
 * 2. send the control words to the aic via i2c to configure it
 * 3. the a3k starts up the codec interface
 */
static short
   start_a3k_codec( short      skew,
		    short  passthru,
		    short interface,
		    short   codecif )
{
	char packet[30];
	char *p = packet+4;
	short chk_header, chk_len, chk_type, chk_field, chk_response_ok;
	short plen;
	
	p = put_next_byte( p, PKT_STARTCODEC );
	p = put_next_byte( p, (skew & 1) | ((passthru & 1)<<1) | ((codecif & 1)<<2) );
	put_packet( packet, p, PKT_CONTROL, 1, interface );

	plen = get_packet( packet, interface );
	if (plen == 0)
		return 1;

	p = packet;
	p = get_next_byte( p, &chk_header );
	if (chk_header != PKT_HEADER)
		return -1;
	p = get_next_word( p, &chk_len );
	if (chk_len != 4) 
		return -2;
	p = get_next_byte( p, &chk_type );	
	if (chk_type != PKT_CONTROL)
		return -3;
	p = get_next_byte( p, &chk_field);
	if (chk_field != PKT_STARTCODEC)
		return -12;
	p = get_next_byte( p, &chk_response_ok);
	if (chk_response_ok != PKT_RESPONSE_OK)
		return -13;

	return 0;
}

short trials;

short
   stop_a3k_codec( short interface )
{
	char packet[30];
	char *p = packet+4;
	short chk_header, chk_len, chk_type, chk_field, chk_response_ok;
	short plen;

	trials = 0;

	p = put_next_byte( p, PKT_STOPCODEC );
	put_packet( packet, p, PKT_CONTROL, 1, interface );

	plen = get_packet( packet, interface );
	if (plen == 0)
		return 1;

	while (packet[3] != PKT_CONTROL) {
		if (trials == 5)
			return -3;
		trials++;

		/*
		 * maybe we got another channel packet at the end.
		 * check one for one more packet, before we go and say
		 * that an error occurred.
		 */
		plen = get_packet( packet, interface );
		if (plen == 0)
			return 1;

	}

	p = packet;
	p = get_next_byte( p, &chk_header );
	if (packet[0] != PKT_HEADER)
		return -1;
	p = get_next_word( p, &chk_len );
	if (chk_len != 2+2) 
		return -2;
	p = get_next_byte( p, &chk_type );
	if (chk_type != PKT_CONTROL)
		return -3;
	p = get_next_byte( p, &chk_field);
	if (chk_field != PKT_STOPCODEC)
		return -4;
	p = get_next_byte( p, &chk_response_ok);
	if (chk_response_ok != PKT_RESPONSE_OK)
		return -5;

	return 0;
}

/*
 * This function monitors the uart0rx fifo.  It can forward the data to
 * the a3k ppt port or it can forward it to uart1.  It can also strip
 * out andd decode HDK control packets.  It can throw away unexpected
 * packets, at times when only HDKCONTROL packets are expected.
 *
 * if no packet is in the fifo the function returns -1.
 *
 * if a packet is in the fifo and it is an HDKCONTROL packet then the
 * HDKCONTROL packet is removed from the fifo and stored in p[].  It is
 * then decoded and the function returns 1.
 * 
 * if a packet is in the fifo but it is not an HDKCONTROL packet, then
 * the function supports the following actions:
 * 
 * action=NONE(0)
 * the packet is left in the fifo, the fifo is unaltered.
 * 
 * action=DISCARD(1)
 * the packet is removed from the fifo.
 *
 * action=TOUART(2)
 * the packet is left in the fifo and transmit_uart1_packet is called,
 * which causes the packet to be sent out of uart1.
 * 
 * action=TOPPT(3)
 * the packet is removed from the fifo, paced in p[], and sent to PPT.
 *
 * returns 0 if there is a packet but it is not an HDKCONTROL packet.
 */
short packets_to_a3k = 0;
short packets_from_a3k = 0;

static void
   uart0_monitor( char action )
{

	if (hdk.uart0tx.fifo->nelem >= 4) {
		hdk.uart0tx.active = 1;
		ENABLE_UART0_TX_INTERRUPT;
	}

	
	if (hdk.uart0rx.fifo->nelem >= 4) {

		if (fifo_peekpackettype(hdk.uart0rx.fifo) == PKT_HDKTYPE) {
			if (fifo_checkfullpacket( hdk.uart0rx.fifo)) {
				fifo_decodehdkcontrolpacket( hdk.uart0rx.fifo ); 
			} 
		} else {
			if (action == 2) {
				if (hdk.uart1tx.active == 0) {
					hdk.uart1tx.active = 1;
				
					ENABLE_UART1_TX_INTERRUPT;
				}

			} else if (action == 3) {

				if (fifo_checkfullpacket( hdk.uart0rx.fifo)) {
					packets_to_a3k++;
					fifo_forwardpackettoppt( hdk.uart0rx.fifo );     
				} 
				
			}	
		}
	}
}

char txflag = 0;
char txbyte;

short readidx = 0;

char txbuf[8];

/*
 * this routine is carefully designed to maximize throughput to the
 * PPT.  Reading a byte from the UART has the greatest priority
 * (It is done by the uart0_rx_isr).  Writing a byte to UART0 has
 * the next highest priority (We want to keep UART0 tx busy at all
 * times for greatest throughput.  Next priority is wrting recieved
 * characters to the PPT.  THis has higher priority than reading
 * from the PPT, since we have to keep up with UART0 or else rxbuf
 * would overflow.  Least priority is reading from the PPT - we
 * read up to 8 characters from the PPT if TXRDY is set and we have
 * nothing else to do.
 */
static void
   ppt_monitor( void )
{
	static char txreadidx = 0;
	static char txwriteidx = 0;

	if (txflag && ((U0IFG & UTXIFG0) != 0)) {			//write to uart if empty and we have data
		goto uarttx;

	} else if (rxflag > 0) {				//write buffered data to ppt if we have some
		goto pptput;
				
	} else if (((P1IN & TXRDY ) != 0) && (txflag < 8)) {		//read data from ppt to buffer if TXRDY=1
		P4DIR &= ~0xff;
		goto pptget;
	} else
		return;						//nothing to do

uarttx:	txflag--;
uartTx:	TXBUF0 = txbuf[txreadidx];
	txreadidx = (txreadidx+1) & 7;
	return;
	

pptput:	{
		char rxcount;
		_disable_interrupts();
		rxcount = rxflag;
		rxflag = 0;
		_enable_interrupts();
		
		P4DIR |= 0xff; // Set P4 to Output so we can read PPT pins		
		do {					
			ppt_putchar( rxbuf[readidx] );
			readidx = (readidx+1) & 7;
			rxcount--;
		} while (rxcount > 0);
		return;
	}

pptget:	do {
		txbuf[txwriteidx] = ppt_getchar(); 
		txwriteidx = (txwriteidx+1) & 7;

		if (U0IFG & UTXIFG0)
			goto uartTx;
		
		txflag++;

		if (txflag >= 4)
			return;


		if (rxflag > 4)
			return;

	} while ((P1IN & TXRDY) != 0);
	return;
}


int TX_PKT = 0;

void
   mode_idle( void )
{
	hdk.isr_relay = 0;
	hdk.uart0rx.fifo = &hdk.hdkcontrolfifo;
	hdk.uart0tx.active = 0;
	hdk.uart0tx.fifo = &hdk.hdkreplyfifo;
	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );
	while (hdk.reset_mode == 0) {
		uart0_monitor( 1 );	//packet is discarded if it is not HDKCONTROL
	}
}

void
   mode_packet_ppt( void )
{
	DISABLE_UART1_RX_INTERRUPT;
	DISABLE_UART1_TX_INTERRUPT;
	
	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart0rx.fifo = &hdk.toa3kfifo;
	hdk.uart0tx.fifo = &hdk.froma3kfifo;
	packet_reset_a3k (PACKET_PPT, PACKET_PPT);
	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	txflag = 0;
	rxflag = 0;
	hdk.isr_relay = 2;

	ENABLE_UART0_RX_INTERRUPT;

	while (hdk.reset_mode == 0) {
		ppt_monitor();
	}

	if (rxflag) {
		ppt_monitor();
	}

	hdk.isr_relay = 0;

	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart0rx.fifo = &hdk.toa3kfifo;
	hdk.uart0tx.fifo = &hdk.froma3kfifo;
	
	packet_reset_a3k (PACKET_PPT, PACKET_PPT);
}

void
   mode_packet_uart( void )
{
	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart0rx.fifo = &hdk.toa3kfifo;
	hdk.uart0tx.fifo = &hdk.froma3kfifo;
	hdk.uart1rx.fifo = &hdk.froma3kfifo;
	hdk.uart1tx.fifo = &hdk.toa3kfifo;

	ENABLE_UART1_RX_INTERRUPT;
	packet_reset_a3k (PACKET_PPT, PACKET_UART);

	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	hdk.isr_relay = 1;
		
	while (hdk.reset_mode == 0);

	hdk.isr_relay = 0;

	packet_reset_a3k (PACKET_UART, PACKET_PPT);
	DISABLE_UART1_RX_INTERRUPT;

}

void
   mode_codec_ppt( void )
{
	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart0rx.fifo = &hdk.toa3kfifo;
	hdk.uart0tx.fifo = &hdk.froma3kfifo;

	packet_reset_a3k (PACKET_PPT, PACKET_PPT);

	config_a3k_codec (PACKET_PPT);

	
	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	while( hdk.uart0tx.fifo->nelem > 0 );
	while( (U0TCTL & TXEPT) == 0);
	DISABLE_UART0_RX_INTERRUPT;
	DISABLE_UART0_TX_INTERRUPT;

	txflag = 0;
	rxflag = 0;
	hdk.isr_relay = 2;

	ENABLE_UART0_RX_INTERRUPT;

	while (hdk.reset_mode == 0) {
		ppt_monitor();
	}

	if (rxflag) {
		ppt_monitor();
	}

	hdk.isr_relay = 0;

	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart0rx.fifo = &hdk.toa3kfifo;
	hdk.uart0tx.fifo = &hdk.froma3kfifo;
	
//	stop_a3k_codec( PACKET_PPT );
	packet_reset_a3k (PACKET_PPT, PACKET_PPT);
}



void
   mode_codec_uart( void )
{	
	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart0rx.fifo = &hdk.toa3kfifo;
	hdk.uart0tx.fifo = &hdk.froma3kfifo;
	hdk.uart1rx.fifo = &hdk.froma3kfifo;
	hdk.uart1tx.fifo = &hdk.toa3kfifo;

	ENABLE_UART1_RX_INTERRUPT;
	packet_reset_a3k (PACKET_PPT, PACKET_UART);

	/*
	 * configure the a3k and start up the codec.
	 */
	config_a3k_codec (PACKET_UART);
	
	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );	

	hdk.isr_relay = 1;

	while (hdk.reset_mode == 0);
	
	hdk.isr_relay = 0;

	packet_reset_a3k (PACKET_UART, PACKET_PPT);

	DISABLE_UART1_RX_INTERRUPT;
}

void
   mode_loopback_ppt( void )
{
	char mode = hdk.mode;
	char passthru = (mode == HDKMODE_LOOPBACK_VOCODER_PPT) ? 0 : 1;
	short status;

	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );
	
	status = packet_reset_a3k (PACKET_PPT, PACKET_PPT);
	if (status != 0)
		goto end;
	
	/*
	 * configure the a3k and start up the codec.
	 */
	status = config_a3k( -1, 1, PACKET_PPT );	//arg0=-1 specifies a3k rate determined by jumpers
	if (status != 0)
		goto end;
	
	status = config_a3k_codec( PACKET_PPT );
	if (status != 0)
		goto end;
	
	status = start_a3k_codec( 0, passthru, PACKET_PPT, 0 );
	if (status != 0)
		goto end;

	while (hdk.reset_mode == 0) {
		if (P1IN & TXRDY) {
			fifo_putpacketfromppt( &hdk.toa3kfifo );
			fifo_forwardpackettoppt( &hdk.toa3kfifo );
			//ppt_wrap_packet();
		}
		uart0_monitor( 1 );
	}
	
end:
	
	packet_reset_a3k (PACKET_PPT, PACKET_PPT);
}

short status;

void
   mode_loopback_uart( void )
{
	char mode = hdk.mode;
	char passthru = (mode == HDKMODE_LOOPBACK_VOCODER_UART) ? 0 : 1;
	
	
	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart1rx.fifo = &hdk.froma3kfifo;
	hdk.uart1tx.fifo = &hdk.toa3kfifo;
	ENABLE_UART1_RX_INTERRUPT;

	status = packet_reset_a3k (PACKET_PPT, PACKET_UART);
	if (status != 0) {
//		while (1);
		goto end;
	}
	
	status = config_a3k( -1, 0, PACKET_UART );	//arg0=-1 specifies a3k rate determined by jumpers
	if (status != 0) {
//		while(1);
		goto end;
	}
	
	config_a3k_codec( PACKET_UART );
	if (status != 0) {
//		while(1);
		goto end;
	}
	
	status = start_a3k_codec(0, passthru, PACKET_UART, 0 );
	if (status != 0) {
//		while(1);
		goto end;
	}
	
	hdk.uart1rx.fifo = &hdk.toa3kfifo;
	
	DISABLE_UART1_TX_INTERRUPT;

	while (hdk.reset_mode == 0) {
		if (hdk.uart1tx.fifo->nelem >= 4)
			ENABLE_UART1_TX_INTERRUPT;

		uart0_monitor( 1 );
	}

end:
	packet_reset_a3k (PACKET_UART, PACKET_PPT);

}

void
   mode_dualhdk( void )
{
	short status;
	/*
	 * switch UART1 to operate at 57600 baud
	 */
	ME2 |= UTXE1 + URXE1;                   // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                          // 8-bit character
	UTCTL1 |= SSEL0;                	// UCLK = ACLK
	UBR01 = 0x8a;                           // 8MHz 57600
	UBR11 = 0x00;                           // 8MHz 57600
	UMCTL1 = 0xef;                          // 8MHz 57600 modulation
	UCTL1 &= ~SWRST;                        // Initialize USART state machine

	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart1rx.fifo = &hdk.toa3kfifo;
	hdk.uart1tx.fifo = &hdk.froma3kfifo;

	//P1OUT &= ~0x04; //prevent standby
	
	status = config_a3k( -1, 1, PACKET_PPT );	//arg0=-1 specifies a3k rate determined by jumpers
	if (status != 0)
		goto end;
	status = config_a3k_codec (PACKET_PPT);
	if (status != 0)
		goto end;
	status = start_a3k_codec(0, 0, PACKET_PPT, 0 );	//Start Codec (skew disabled,passthru disabled)
	if (status != 0)
		goto end;
		//Set up Timer A
	TACCR0 = 0x1;

	//P1OUT |= 0x04; //allow standby

	while (hdk.reset_mode == 0 ) {
		/*
		 * if the a3k has set TXRDY then read a packet
		 * from the a3k ppt port and then add the
		 * packet to the uart1 tx fifo.
		 */
		if (P1IN & TXRDY) {

			P1OUT &= ~0x04; //prevent standby
			fifo_putpacketfromppt( hdk.uart1tx.fifo );
			ENABLE_UART1_TX_INTERRUPT;
			ENABLE_UART1_RX_INTERRUPT;
			P1OUT |= 0x04; //allow standby
			
			TX_PKT = 1;

			/*
			 * if we received a complete packet via uart1
			 * then forward it to the a3k PPT.
			 */
		} else if (fifo_checkfullpacket(hdk.uart1rx.fifo)){
			fifo_forwardpackettoppt( hdk.uart1rx.fifo );
			TX_PKT = 0;
		} else {
			/*
			 * uart0 packets that are not
			 * HDKCONTROL packets are discarded.
			 */
			uart0_monitor( 1 );
			//Debug code left for the time being     Note:  We should never trap here
			if (hdk.uart1rx.fifo->nelem > 200){
				_disable_interrupts();
				MODELEDS( 0xFF );
				while(1);
			}

		}
	}
end:	packet_reset_a3k (PACKET_PPT, PACKET_PPT);
	DISABLE_UART1_RX_INTERRUPT;

	/*
	 * switch UART1 back to the default baud rate
	 */
	ME2 |= UTXE1 + URXE1;                   // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                          // 8-bit character
	UTCTL1 |= SSEL0;                	// UCLK = ACLK
	UBR01 = ubr0x[BAUDRATESEL];
	UBR11 = 0x00;                           // 8MHz 460800
	UMCTL1 = umctlx[BAUDRATESEL];
	UCTL1 &= ~SWRST;                        // Initialize USART state machine	
}


void
   mode_dualhdkskew(void)
{
	
	/*
	 * switch UART1 to operate at 57600 baud
	 */
	ME2 |= UTXE1 + URXE1;                   // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                          // 8-bit character
	UTCTL1 |= SSEL0;                	// UCLK = ACLK
	UBR01 = 0x8a;                           // 8MHz 57600
	UBR11 = 0x00;                           // 8MHz 57600
	UMCTL1 = 0xef;                          // 8MHz 57600 modulation
	UCTL1 &= ~SWRST;                        // Initialize USART state machine

	//Set up Timer A
	TACCR0 = 0x4f;

	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );

	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	hdk.uart1rx.fifo = &hdk.toa3kfifo;
	hdk.uart1tx.fifo = &hdk.froma3kfifo;

	config_a3k( -1, 1, PACKET_PPT );	//arg0=-1 specifies a3k rate determined by jumpers
	config_a3k_codec (PACKET_PPT);
	start_a3k_codec(1, 0, PACKET_PPT, 0 );		//Start Codec (skew enabled,passthru disabled)
	TACCTL0 = CCIE;								//Turn on TimerA interrupts

	ENABLE_UART1_RX_INTERRUPT;
	while (hdk.reset_mode == 0 ) {
		P2OUT ^= 0x2;

		/*
		 * if the a3k has set TXRDY then read a packet
		 * from the a3k ppt port and then add the
		 * packet to the uart1 tx fifo.
		 */
		if (P1IN & TXRDY) {
			P1OUT &= ~0x04; //prevent standby
			fifo_putpacketfromppt( hdk.uart1tx.fifo );
			P1OUT |= 0x04; //allow standby
			ENABLE_UART1_TX_INTERRUPT;
			

		/*
		 * if we received a complete packet via uart1
		 * then forward it to the a3k PPT.
		 */
		} else if (fifo_checkfullpacket(hdk.uart1rx.fifo)){
			P5OUT |= TXRQST;								//Set TXRQST
			TACTL =  TACLR;									//Clear TimerA
			TACTL = MC0;									//Start TimerA
			fifo_forwardpackettoppt( hdk.uart1rx.fifo );
		} else {
			/*
			 * uart0 packets that are not
			 * HDKCONTROL packets are discarded.
			 */
			uart0_monitor( 1 );
			if (hdk.uart1rx.fifo->nelem > 200){
				_disable_interrupts();
				//P2OUT &= ~0xFF;							//Reset P2
				//P3OUT &= ~0xFF;
				MODELEDS(0xFF);
				while(1);
			}

		}
	}
	packet_reset_a3k (PACKET_PPT, PACKET_PPT);
	DISABLE_UART1_RX_INTERRUPT;
	/*
	 * switch UART1 back to the default baud rate
	 */
	ME2 |= UTXE1 + URXE1;                   // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                          // 8-bit character
	UTCTL1 |= SSEL0;                	// UCLK = ACLK
	UBR01 = ubr0x[BAUDRATESEL];
	UBR11 = 0x00;                           // 8MHz 460800
	UMCTL1 = umctlx[BAUDRATESEL];
	UCTL1 &= ~SWRST;                        // Initialize USART state machine	
	
}


/*
 * In DSP_UART mode the HDK doesn't do anything except wait for
 * HDKCONTROL packets to change to another mode.  This mode
 * just sets up the a3k to use the UART packet interface.  A PC
 * can be hooked directly to the DSP UART.  The PC packet mode
 * tests that I developed for the PWR3K can be used in this
 * mode.
 */
void
   mode_a3kdirect(void)
{

	fifo_sendhdkcontrol( PKT_HDKREADY, hdk.uart0tx.fifo );
	packet_reset_a3k (PACKET_PPT, PACKET_UART);
	while (hdk.reset_mode == 0) {
		/*
		 * uart0 packets that are not
		 * HDKCONTROL packets are discarded.
		 */
		uart0_monitor( 1 );
	}
	P5OUT &= ~0x40;
	delay();
	P5OUT = 0x40;							//Set P5.6 - Brings DSP out of reset	
}

msp_process()
{


	hdk.reset_mode = 0;
	
	if (hdk.mode == HDKMODE_PACKET_PPT) {
		MODELEDS( 0x02 );
		mode_packet_ppt();
	} else if (hdk.mode == HDKMODE_PACKET_UART) {
		MODELEDS( 0x03 );
		mode_packet_uart();
	} else if ( hdk.mode == HDKMODE_CODEC_PPT ) {
		MODELEDS( 0x04 );
		mode_codec_ppt();
	} else if ( hdk.mode == HDKMODE_CODEC_PASSTHRU_PPT) {
		MODELEDS( 0x05 );
		mode_codec_ppt();		
	} else if ( hdk.mode == HDKMODE_CODEC_UART ) {
		MODELEDS( 0x06 );
		mode_codec_uart();
	} else if (hdk.mode == HDKMODE_CODEC_PASSTHRU_UART) {
		MODELEDS( 0x07 );
		mode_codec_uart();		
	} else if (hdk.mode == HDKMODE_LOOPBACK_VOCODER_PPT) {
		MODELEDS( 0x08 );
		mode_loopback_ppt();
	} else if (hdk.mode == HDKMODE_LOOPBACK_PASSTHRU_PPT) {
		MODELEDS( 0x09 );
		mode_loopback_ppt();
	} else if (hdk.mode == HDKMODE_LOOPBACK_VOCODER_UART) {
		MODELEDS( 0x0A );
		mode_loopback_uart();
	} else if (hdk.mode == HDKMODE_LOOPBACK_PASSTHRU_UART) {
		MODELEDS( 0x0B );
		mode_loopback_uart();
	} else if (hdk.mode == HDKMODE_DUALHDK ) {
		MODELEDS( 0x0C );
		mode_dualhdk();
	} else if (hdk.mode == HDKMODE_DUALHDKSKEW ) {
		MODELEDS( 0x0D );
		mode_dualhdkskew();
	} else if (hdk.mode == HDKMODE_DSPUART) {
		MODELEDS( 0x0E );
		mode_a3kdirect();
	} else {
		MODELEDS( 0x01 );
		hdk.mode = HDKMODE_IDLE;
		mode_idle();
	}
}


void
   main(void)
{

	
	cpuInit();
	
	_enable_interrupts();                 			// Enable Interrupts
	
	
	/*
	 * initialize all four HDK fifos
	 */
	fifo_init( &hdk.hdkcontrolfifo, HDKCTLLEN, hdk.hdkcontrolbuf );
	fifo_init( &hdk.hdkreplyfifo,   HDKREPLEN, hdk.hdkreplybuf );
	fifo_init( &hdk.toa3kfifo,     TOA3KBLEN, hdk.toa3kbuf );
	fifo_init( &hdk.froma3kfifo,   FROMA3KBLEN, hdk.froma3kbuf );

	/*
	 * initialize the state for the uart0 rx isr.
	 */

	hdk.uart0rx.fifo = &hdk.hdkcontrolfifo;

	/*
	 * initialize the state for the uart0 tx isr.
	 */
	hdk.uart0tx.active = 0;
	hdk.uart0tx.fifo = &hdk.hdkreplyfifo;

	/*
	 * NOTE: since all modes dont use uart1, the uart1 isr states
	 * are initialized when needed.
	 */

	hdk.uart1tx.active = 0;
	
	
	ENABLE_UART0_RX_INTERRUPT;	//this remains enabled so that we can always receive hdkcontrol packets
	
 	P6OUT |= 0x06;
	P5OUT = 0x40;							//Set P5.6 - Brings DSP out of reset
	
	MODELEDS( 0xAA );

	wait_a3k_ready( PACKET_PPT );

	/*
	 * Default HDK Boot mode
	 * To get the HDK to boot in another default mode, change the assignment below.
	 */	
	/*
	 * Experimental code to choose boot mode
	 */
	 if (BOOT_MODE == 0x00){
	 	hdk.mode = HDKMODE_IDLE;
	 }else if (BOOT_MODE == 0x01){
	 	hdk.mode = HDKMODE_DSPUART;
	 }else if (BOOT_MODE == 0x80){
	 	hdk.mode = HDKMODE_DUALHDK;
	 }else if (BOOT_MODE == 0x81){
	 	hdk.mode = HDKMODE_DUALHDKSKEW;
	 }else if (BOOT_MODE == 0x40){
	 	hdk.mode = HDKMODE_LOOPBACK_VOCODER_PPT;
	 }else if (BOOT_MODE == 0x41){
	 	hdk.mode = HDKMODE_LOOPBACK_VOCODER_UART;
	 }else if (BOOT_MODE == 0xC0){
	 	hdk.mode = HDKMODE_PACKET_PPT;
	 }else{
	 	hdk.mode = HDKMODE_IDLE;
	 }

	 	
	 
//	hdk.mode = HDKMODE_IDLE;
	hdk.reset_mode = 0;
	hdk.isr_relay = 0;
//	hdk.mode = HDKMODE_DUALHDK;
//	hdk.mode = HDKMODE_DUALHDKSKEW;
//	hdk.mode = HDKMODE_CODEC_UART;
//	hdk.mode = HDKMODE_CODEC_PPT;
//	hdk.mode = HDKMODE_LOOPBACK_PASSTHRU_PPT;
//	hdk.mode = HDKMODE_LOOPBACK_VOCODER_PPT;
//	hdk.mode = HDKMODE_LOOPBACK_VOCODER_UART;
//	hdk.mode = HDKMODE_LOOPBACK_PASSTHRU_UART;
//	hdk.mode = HDKMODE_CODEC_PASSTHRU_PPT;
//	hdk.mode = HDKMODE_CODEC_PASSTHRU_UART;
//	hdk.mode = HDKMODE_DSPUART;	
	
	
	while(1) {
		msp_process();
	}
}


