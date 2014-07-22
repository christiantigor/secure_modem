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

#ifndef COMPORT_H_
#define COMPORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

//#define MAX_MENU		9
//#define MAX_STRING		256

#define NOPARITY		0
#define ONESTOPBIT		0
#define RTS_CONTROL_DISABLE     0x00
#define RTS_CONTROL_ENABLE      0x01
#define DTR_CONTROL_DISABLE     0x00
#define DTR_CONTROL_ENABLE      0x01

#define msg(info)	MessageBox(NULL, info, "", MB_OK)


#define HEADER_BYTE	'a'

typedef struct
{
	unsigned long   ulCtrlerID;
	char            cEcho;
	char            cEORChar;
	long            lTimeout;
	long            lBaudRate;
	long            lDataBits;
	HANDLE          h_Port;
}SerialCreate, *pSerialCreate;

typedef struct
{
	char   *pcBuffer;     //not used in read function
	BYTE   bByte;
	int    iMaxChars;         
	int    piNumRcvd;     //never initialized       
	char   cTermChar;	
	HANDLE handlePort;
}CommPortClass;

typedef enum
{
	OK					= 0,		 /* no error */
	EC_TIMEOUT,
	EC_FOPEN,
	EC_INVAL_CONFIG,
	EC_TIMEOUT_SET,
	EC_RECV_TIMEOUT,
	EC_EXIT_CODE,
	EC_WAIT_SINGLEOBJ,
	EC_INVALIDPORT,
	EC_WRITE_FAIL,
	EC_READ_FAIL,
	EC_TEST_FAIL,
	EC_CREATE_THREAD,
	EC_PORT_INITDONE,	
	EC_INVALID_HEADER,
	EC_RECEIVE_OVERFLOW,
	EC_UNKNOWNERROR
}ERR_CODE;

/*
 * comport.cpp defines the following external functions:
 *
 * To use the functions you must declare a pointer to a
 * comPort, i.e.
 *
 * CommPortClass *comPort;
 *
 * You can then open a COM port using
 * OpenPort()
 *
 * You can read/write packets from the COM port using
 * ReadPacketPort()
 * and
 * WritePacketPort()
 *
 * When you are done you should close the COM port using
 * ClosePort()
 *
 * All functions use comPort as the last argument.
 *
 */
#ifdef __cplusplus
extern "C"
#endif
ERR_CODE
   OpenPort( char             *port,
	     char           *buffer,
	     int    max_buffer_size,
	     long         baud_rate,
	     long          databits,
	     long           timeout,
	     CommPortClass **comPort );

#ifdef __cplusplus
extern "C"
#endif
ERR_CODE
   ReadPacketPort( char           *packet,
		   int     *packet_length,
		   short          timeout,
		   CommPortClass *comPort );

#ifdef __cplusplus
extern "C"
#endif
ERR_CODE
   WritePacketPort( char           *packet,
		    int      packet_length,
		    CommPortClass *comPort );

#ifdef __cplusplus
extern "C"
#endif
void
   ClosePort( CommPortClass *comPort );

#endif
