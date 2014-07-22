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

#ifndef HARDWARE_H_
#define HARDWARE_H_

//Hardware Pin Definitions
#define PPT_ACK		(0x08)
#define PPT_WR		(0x04)
#define PPT_RD		(0x02)
#define TXRDY		(0x02)
#define RXRDY		(0x04)
#define RXRQST		(0x20)
#define TXRQST		(0x04)
#define MSP_RESET	(0x40)
#define WAKE		(0x04)


//Status LED definitions
#define LED0		(0x01)
#define LED1		(0x80)
#define LED2		(0x40)
#define LED3		(0x20)
#define LED4		(0x10)
#define LED5		(0x08)
#define LED6		(0x04)
#define LED7		(0x02)

//Port Output Register
#define P1OUT_INIT      (WAKE | BIT1)              // Init Output data of port1
#define P2OUT_INIT      0                          // Init Output data of port2
#define P3OUT_INIT      (PPT_WR | PPT_RD)          // Init Output data of port3
#define P4OUT_INIT      0                          // Init Output data of port4
#define P5OUT_INIT      0                          // Init Output data of port5
#define P6OUT_INIT      0                          // Init Output data of port6

//Port Direction Register
#define P1DIR_INIT      (WAKE)                     // Init of Port1 Data-Direction Reg (Out=1 / Inp=0)
#define P2DIR_INIT      0x3E                       // Init of Port2 Data-Direction Reg (Out=1 / Inp=0)
#define P3DIR_INIT      (PPT_RD | PPT_WR)   // Init of Port3 Data-Direction Reg (Out=1 / Inp=0)
#define P4DIR_INIT      0                          // Init of Port4 Data-Direction Reg (Out=1 / Inp=0)
#define P5DIR_INIT      (MSP_RESET | TXRQST)       // Init of Port5 Data-Direction Reg (Out=1 / Inp=0)
#define P6DIR_INIT      0xFF                       // Init of Port6 Data-Direction Reg (Out=1 / Inp=0)

//Selection of I/O Port or Module
#define P1SEL_INIT      (BIT0)                     // P1-Modules
#define P2SEL_INIT      0                          // P2-Modules
#define P3SEL_INIT      (BIT7 | BIT6 | BIT5 | BIT4)// P3.4,5,6,7 = USART0/1 TXD/RXD
#define P4SEL_INIT      0                          // P4-Modules
#define P5SEL_INIT      0                          // P5-Modules
#define P6SEL_INIT      0                          // P6-Modules

//Interrupt capabilities of P1 and P2
#define P1IE_INIT       0                          // Interrupt Enable (0=dis 1=enabled)
#define P2IE_INIT       0                          // Interrupt Enable (0=dis 1=enabled)
#define P1IES_INIT      0                          // Interrupt Edge Select (0=pos 1=neg)
#define P2IES_INIT      0	                       // Interrupt Edge Select (0=pos 1=neg)

#endif /*HARDWARE_H_*/
