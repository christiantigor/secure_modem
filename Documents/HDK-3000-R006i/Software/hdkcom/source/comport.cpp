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

#include <stdio.h>

#include "comport.h"

static void WINAPI
   ThreadFunc(void* hCommPorts)
{

	DWORD  dwError;
	BOOL   bResult;
	int	 nTotRead = 0;
	DWORD  dwCommModemStatus;
	CommPortClass*  CommPorts;
	ERR_CODE ecStatus = OK;
	unsigned long lNumRcvd;

	CommPorts = (CommPortClass* )hCommPorts;

	  // Specify a set of events to be monitored for the port.
	SetCommMask(CommPorts->handlePort, EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_RING);

	  // Wait for an event to occur for the port.
	WaitCommEvent(CommPorts->handlePort, &dwCommModemStatus, 0);		

	  // Re-specify the set of events to be monitored for the port.
	SetCommMask(CommPorts->handlePort, EV_RXCHAR | EV_CTS | EV_DSR |EV_RLSD| EV_RING);

	if (dwCommModemStatus & EV_RXCHAR||dwCommModemStatus & EV_RLSD)	// received the char_event
	{

			// Read the data from the serial port.
		bResult = ReadFile(CommPorts->handlePort, CommPorts->pcBuffer, CommPorts->iMaxChars, &lNumRcvd, 0);
		CommPorts->piNumRcvd = (int) lNumRcvd;

		if (!bResult)
		{
			printf("Unable to read the port\n");
			switch (dwError = GetLastError()) 
			{ 
				case ERROR_HANDLE_EOF: 
					printf("Serial Receive Failed\n");
					break;
			}
		}
	}		

	return;
}

static void
   PrefixComName( char *nstring,
		  char *ostring,
		  int     maxlen )
{
	char *prefix = "\\\\.\\";
	int len = 0;

	while ((*prefix != 0) && (len < (maxlen-1))) {
		*nstring++ = *prefix++;
		len++;
	}
	while ((*ostring != 0) && (len < (maxlen-1))) {
		*nstring++ = *ostring++;
		len++;
	}
	*nstring++ = 0;

}

static ERR_CODE
   PortInitialize(LPTSTR lpszPortName,
		  pSerialCreate pCreate)
{
	HANDLE		   hPort;
	DWORD		   dwError;
	DCB			   PortDCB;  
	ERR_CODE       ecStatus = OK;
	COMMTIMEOUTS   CommTimeouts;
	unsigned char  dBit;
	char comportname[20];

	/*
	 * CreateFile does not work for COM ports 10 and higher unless
	 * you prepend "\\\\.\\"
	 */
	PrefixComName( comportname, lpszPortName, 20 );

	// Open the serial port.
	hPort = CreateFile(comportname,  // Pointer to the name of the port
			   GENERIC_READ | GENERIC_WRITE, // Access (read/write) mode
			   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE/*0*/,             // Share mode
			   NULL,          // Pointer to the security attribute
			   OPEN_EXISTING, // How to open the serial port
			   0,             // Port attributes
			   NULL);         // Handle to port with attribute to copy										

	// If it fails to open the port, return error.
	if ( hPort == INVALID_HANDLE_VALUE ) 
	{
		// Could not open the port.
		dwError = GetLastError();
//		msg("Unable to open the port");
		CloseHandle(hPort);
		return EC_FOPEN;
	} else 
		PortDCB.DCBlength = sizeof(DCB);     

	// Get the default port setting information.
	GetCommState(hPort, &PortDCB);

	// Change the DCB structure settings.
	PortDCB.BaudRate = pCreate->lBaudRate;		// Current baud 
	PortDCB.fBinary  = TRUE;			// Binary mode; no EOF check 
	PortDCB.fParity  = TRUE;			// Enable parity checking. 
	PortDCB.fOutxCtsFlow = FALSE;			// No CTS output flow control 
	PortDCB.fOutxDsrFlow = FALSE;			// No DSR output flow control 
	PortDCB.fDtrControl = DTR_CONTROL_ENABLE;	// DTR_CONTROL
												// DTR flow control type 
	PortDCB.fDsrSensitivity = FALSE;		// DSR sensitivity 
	PortDCB.fTXContinueOnXoff = TRUE;		// XOFF continues Tx 
	PortDCB.fOutX = FALSE;				// No XON/XOFF out flow control 
	PortDCB.fInX  = FALSE;				// No XON/XOFF in flow control 
	PortDCB.fErrorChar = FALSE;			// Disable error replacement. 
	PortDCB.fNull = FALSE;				// Disable null stripping. 
	PortDCB.fRtsControl = RTS_CONTROL_ENABLE;	// RTS_CONTROL
												// RTS flow control 
	PortDCB.fAbortOnError = FALSE;			// Do not abort reads/writes on error.
	dBit = (unsigned char)pCreate->lDataBits;	
	PortDCB.ByteSize = dBit;			// Number of bits/bytes, 4-8 
	PortDCB.Parity = NOPARITY;			// 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = ONESTOPBIT;			// 0,1,2 = 1, 1.5, 2 

	// Configure the port according to the specifications of the DCB structure.
	if (!SetCommState (hPort, &PortDCB))
	{
		// Could not create the read thread.
		dwError = GetLastError();
//		msg("Unable to configure the serial port");
		return EC_INVAL_CONFIG;
	} 

	// Retrieve the time-out parameters for all read and write operations on the port. 
	GetCommTimeouts(hPort, &CommTimeouts);

	// Change the COMMTIMEOUTS structure settings.
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeouts.ReadTotalTimeoutConstant = 0;    
	CommTimeouts.WriteTotalTimeoutMultiplier = 10;  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;    

	// Set the time-out parameters for all read and write operations on the port. 
	if (!SetCommTimeouts (hPort, &CommTimeouts))
	{
		// Could not create the read thread.
		dwError = GetLastError();
//		msg("Unable to set the time-out parameters");
		return EC_TIMEOUT_SET;
	} 


	EscapeCommFunction(hPort, SETDTR);
	EscapeCommFunction(hPort, SETRTS);
	pCreate->h_Port = hPort;

	return ecStatus;
}

static ERR_CODE
   PortWrite(HANDLE handPort, char *pbByte, int NumByte)
{
	DWORD dwError;
	DWORD dwNumBytesWritten;
	ERR_CODE ecStatus = OK;

	if (!WriteFile (handPort,				// Port handle
			pbByte,				// Pointer to the data to write 
			NumByte,				// Number of bytes to write
			&dwNumBytesWritten,	// Pointer to the number of bytes written
			NULL))				// Must be NULL for Windows CE
	{
		// WriteFile failed. Report error.
		dwError = GetLastError ();
//		msg("ERROR in PortWrite ..");
		return EC_WRITE_FAIL;
	}

	return ecStatus;
}

static ERR_CODE
   PortRead(CommPortClass *hCommPort, short timeout )
{  
	HANDLE hThread;			// handler for port read thread
	DWORD  IDThread;
	DWORD  Ret, ExitCode;
	DWORD	 dTimeout = 5000;	// define time out value: 5 sec.

	/* allows a non-default timeout to be specified */
	if (timeout != 0)
		dTimeout = timeout;
	
	if (!(hThread = CreateThread(NULL,			// no security attributes
				     0,					            // use default stack size
				     (LPTHREAD_START_ROUTINE) ThreadFunc,
				     (LPVOID)hCommPort,              // parameter to thread funciton
				     CREATE_SUSPENDED,	            // creation flag - suspended
				     &IDThread) ) ) {					// returns thread ID
//		msg("Create Read Thread failed");
		printf("PortRead: error creating thread\n");
		return EC_CREATE_THREAD;
	}

	ResumeThread(hThread);		// start thread now

	Ret = WaitForSingleObject(hThread, dTimeout);
	if (Ret == WAIT_OBJECT_0) {
		  // data received & process it...
		  // Need to do nothing because the data has been stored in the hCommPort in Thread Func.
		  // close thread handle
		//  printf("wait_object_0\n");
		//this is what happens normally
		CloseHandle(hThread);
		return OK;
		
	} else if (Ret == WAIT_TIMEOUT) {
		  // time out happened, warning & kill thread
		Ret = GetExitCodeThread(hThread, &ExitCode);
//		printf("PortRead: Timeout\n");
//		msg("Time out happened in PortRead() ");
		if (ExitCode == STILL_ACTIVE) {
			TerminateThread(hThread, ExitCode);
			CloseHandle(hThread);
			return EC_RECV_TIMEOUT;
		} else {
			CloseHandle(hThread);
//			msg("ERROR in GetExitCodeThread: != STILL_ACTIVE ");
			return EC_EXIT_CODE;
		}
	} else {
//		msg("ERROR in WaitFor SingleObject ");
		printf("Port Read: Unknown error\n");
		return EC_WAIT_SINGLEOBJ;
	}

}









/*
 * opens a port
 *
 * port is a string such as "COM4"
 * buffer is a buffer for storing read data
 * buffer_max_size is the size of the buffer
 */
ERR_CODE
   OpenPort( char              *port,		//port string ("COM4" for example)
	     char            *buffer,		//start of the buffer that you are providing for I/O
	     int     buffer_max_size,		//lenth of the buffer
	     long           baudrate,		//baud rate for the com port 115200 or 230400 for example
	     long           databits,		//data bits for the com port (8 for example)
	     long            timeout,		//timeout for the com port in milliseconds (3000=>3 seconds timeout)
	     CommPortClass **comPort )
{
	ERR_CODE       ecRet;
	pSerialCreate pParam;
	HANDLE hProcess;
	int stat;

	/*
	 * set the  priority of this process
	 */
	hProcess = GetCurrentProcess();
	stat = SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);


	*comPort = new CommPortClass;
	pParam = new SerialCreate;

	pParam->lBaudRate = baudrate;
	pParam->lDataBits = databits;
	pParam->lTimeout  = timeout;

	ecRet = PortInitialize(port, pParam);

	if (ecRet == OK) {
		(*comPort)->handlePort = pParam->h_Port;
		(*comPort)->iMaxChars  = buffer_max_size;		//maximum size of buffer
		(*comPort)->pcBuffer = buffer;				
	} else {
		delete (*comPort);
	}

	delete pParam;

	return ecRet;
}

/*
 * Note that the rxbuffer is used to hold the received data.  After we
 * have received a full packet, the data is copied from the rxbuffer to
 * the destination packet.  The data in the rxbuffer is then shifted.
 * rxbuffer_length keeps track of how many bytes are in the rxbuffer.
 * The destination (packet) must be large enough to hold the packet.
 */
ERR_CODE
   ReadPacketPort( char           *packet,
		   int     *packet_length,
		   short          timeout,
		   CommPortClass *comPort )
{
	static char rxbuffer[2048];
	static int rxbuffer_length = 0;
start:	
	*packet_length = rxbuffer_length;
//	printf("*packet_lengtha=%d\n", *packet_length );
	if ((rxbuffer_length > 2048) || (rxbuffer_length < 0)) {
		printf("ReadPacketPort error: rxbuffer_length is invalid\n");
		printf("rxbuffer_length=%d\n", rxbuffer_length );
		return (ERR_CODE)EC_UNKNOWNERROR;
	}
	
	while (1) {
		int i;

		/*
		 * once we have received the first 4 bytes we can check
		 * the header byte and we can determine the packet
		 * length.  If we haven't received at least 4 bytes
		 * then wait until we have.
		 */
		if (*packet_length >= 4) {
			if (rxbuffer[0] != HEADER_BYTE) {
				printf("ReadPacketPort error: invalid header\n");
				printf("length=%d", *packet_length );
				for(i=0;i<*packet_length;i++) {
					printf("%02x ", rxbuffer[i] & 0x00ff );
				}
#if 0
				return (ERR_CODE)EC_INVALID_HEADER;
#else
				{
					short len;
					
					len = 0;
					while (len < *packet_length) {
						if (rxbuffer[len] != HEADER_BYTE) {
							len++;
						} else
							break;
					}
					/*
					 * now discard len bytes and
					 * shift over rxbuffer.
					 */
					rxbuffer_length = *packet_length - len;
				//	printf("rxbuffer_length=%d\n", rxbuffer_length );
				//	printf("len=%d\n", len );
					for ( i = 0; i < rxbuffer_length; i++ ) {
						rxbuffer[i] = rxbuffer[len+i];
					}
					/*
					 * now start over
					 */
					goto start;
				}
#endif
			} else {
				int len = (rxbuffer[1] << 8) | (((short)rxbuffer[2]) & 0x00ff);

		//		printf("len=%d ****\n", len );
				/*
				 * if we received a packet length that
				 * is out of range then return an
				 * error.
				 */
				if (len <= 0) {
					printf("ReadPacketPort error: length field <= 0 (len=%d)\n", len );
					for (i=0;i<*packet_length;i++) {
						printf("%02x ", rxbuffer[i] & 0x00ff );
					}
					return (ERR_CODE)EC_UNKNOWNERROR;

				} else if (len + 4 > 512) {
					printf("ReadPacketPort error: length field indicates receive packet too big\n");
					printf("len=%d\n", len );
					printf("received bytes=%d\n", *packet_length );
					for ( i = 0 ; i < *packet_length; i++ ) {
						printf("rxbuffer[%d]=0x%02x\n", i, rxbuffer[i] & 0x00ff );
					}
					return (ERR_CODE)EC_UNKNOWNERROR;
				}
				
				/*
				 * when we have collected at least a
				 * full packet, copy the data to the
				 * destination, shift the rxbuffer,
				 * and return without error.
				 */
				if (*packet_length >= (len + 4)) {
					rxbuffer_length=*packet_length-(len+4);
					for ( i = 0; i < len + 4; i++ ) {
						*packet++ = rxbuffer[i];
					}
					*packet_length = len+4;
					for (i=0;i<rxbuffer_length;i++) {
						rxbuffer[i] = rxbuffer[len+4+i];
					}
					return (ERR_CODE)0;
				}
			}
		}

		{
			ERR_CODE ecRet = PortRead(comPort,timeout);
			if (ecRet) {
				printf("PortRead error = %d\n", ecRet );
				return ecRet;
			}
		}

		/*
		 * copy whatever bytes were received into the packet
		 * and increment the packet length.
		 */
		if (comPort->piNumRcvd > 0) {
			int start = *packet_length;
			if (*packet_length + comPort->piNumRcvd > 2048) {
				/*
				 * we have read more data than will fit
				 * in the buffer.
				 */
				printf("ReadPacketPort error: receive overflow\n");
				return (ERR_CODE)EC_RECEIVE_OVERFLOW;
			}
			for ( i = 0;i < comPort->piNumRcvd; i++ )
				rxbuffer[start+i] = comPort->pcBuffer[i];
			*packet_length += comPort->piNumRcvd;
	//		printf("*packet_lengthb=%d\n", *packet_length );
	//		printf("*packet_length=%d\n", *packet_length );
		}
		
	}
}

ERR_CODE
   WritePacketPort( char           *packet,
		    int      packet_length,
		    CommPortClass *comPort )
{

	return PortWrite(comPort->handlePort, packet, packet_length );
}

void
   ClosePort( CommPortClass *comPort )
{
	CloseHandle( comPort->handlePort );
	delete comPort;
}




#if 0
//this shows how to use the functions as intended

#include "comport.h"

#define COM4_RXBUFFER_LEN	1024
#define COM4_BAUD_RATE		230400L
#define COM4_DATA_BITS		8L
#define COM4_TIMEOUT		3000L

mymain()
{

	CommPortClass* comPort;
	char com4_rxbuffer[COM4_RXBUFFER_LEN];
	char txpacket[MAX_TXPACKET_LEN];
	char rxpacket[MAX_RXPACKET_LEN];	
	ERR_CODE error;

	error = OpenPort( "COM4", com4_rxbuffer, COM4_RXBUFFER_LEN, COM4_BAUD_RATE, COM4_DATA_BITS, COM4_TIMEOUT, comPort );
	if (!error) {
		while (1) {

			/*
			 * get a txpacket from somewhere and set
			 * txpacket_length to the number of bytes in
			 * the packet.
			 */

			/*
			 * now send the packet to the COM port
			 */
			error = WritePacketPort( txpacket, txpacket_length, comPort );
			if (error) {
				ClosePort( comPort );
			}

			/*
			 * now receive the response packet
			 */
			error = ReadPacketPort( rxpacket, &rxpacket_length, comPort );
			if (error) {
				
				ClosePort( comPort );
			}

			/*
			 * now rxpacket_length has the length of the
			 * received packet.  Do something with the
			 * received packet
			 */

		}

		//if we finish without error, close the port
		ClosePort( comPort );
	}


}
#endif