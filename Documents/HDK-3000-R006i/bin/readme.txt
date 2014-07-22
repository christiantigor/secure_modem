This file desciribes the command line syntax for each of the .bat and .exe contained in the 
\bin directory.  The programs are launched using a Command Prompt from within Windows XP or
Windows Vista.

hdksetup.bat [no options]
Run this batch file first to specify the COM port and baud-rate for the HDK USB connection.
You will be prempted to enter the COM port and then the baud rate.  The batch file
sets up environment variables using the responses.  It also adds the \bin directory to
your path.

hdkcom.exe [options]
This is the hdkcom executable used by most of the batch files.  The command line syntax is 
described in the HDK Manual.  It is used to communicate with the HDK board.

hdkversion.bat [no options]
Run this batch file to display the hdkcom.exe version info, as well as to retreive the AMBE-3000
version information, and the version information from the program currently stored in the 
MSP430 flash.

hdkverify.bat [no options]
Runs a set of tests used by DVSI to determine that the board is working correctly prior to
shipping.  This batch file can be used by a customer to verify that the hardware has
been set up correctly.  Note that you need to have a serial null modem cable connect between 
P1 and P2 for some parts of this test.  You also need to have a handset connect to P3.
The test first verifies that the AMBE-3000 vocoder is functioning properly by processing
several files using packet mode, and comparing the results to the expected results.  It
excercises both the encoder and decoder at a few different rates.  It excersises the PPT and
UART interfaces to the AMBE-3000. It excercises the vocoder with DTX enabled and with DTX 
disabled.  It tests using linear, a-law and u-law PCM samples.  After the packet mode tests, 
the batch file plays one of the test vectors using codec play mode.  A file containing 
compressed speech bits is passed to the HDK board.  The bits are decoded and the resulting 
speech is sent out via the codec interface.  Next the test plays out one of the sample pcm 
output files.  This test excersise the AMBE-3000 in codec passthru mode.  PCM samples are sent
to the HDK, the MSP receives the samples, passes them to the AMBE-3000 which sends them to the
codec.  The encoder and decoder are not used for passthru mode.  As a final test, the batch 
file prompts the user to record three seconds of speech through the handset, and then plays out
the recorded speech through the handset.

hdkpacket.bat [no options]
Runs extensive packet mode tests.  It processes all the test vectors included on the CD, for
every rate (0-61).  Each vector is processed using both the UART interface and the PPT 
interface.  Each file is processed using Linear PCM samples and both u-law and A-law 
companding.  Each file is processed with DTX disabled and again with DTX enabled.

hdkerr.bat [no options]
Runs packet mode tests with bit errors for both hard-decison and soft-decision.  It decodes 
all the bit error test vectors included on the CD, every rate (0-61).  Each vector is 
processed using both the UART interface and the PPT  interface.  

hdkplaybit rate file.bit [interface]
Uses hdkcom.exe to play one of the compressed speech files via the codec interface.  If
file.bit exists in the ../tv directory it is played.  Otherwise, the path is assumed
to be relative to the current directory, or and absolute path.  Interface may be
-ppt, -uart, or blank.

hdkplaypcm rate file.pcm [interface]
Uses hdkcom.exe to play out one of the stored pcm output files in the tv directory.

hdkrecordbit.bat rate file.bit seconds [interface]
Uses hdkcom.exe to record speech. Rate is used to specify the vocoder rate index (0-61) for
the AMBE3000 vocoder. file.bit specifies the name of the file to be recorded. "seconds"
specifies how many seconds to record. Interface may be -ppt, -uart, or blank.

hdkrecordpcm.bat file.pcm seconds [nterface]
Uses hdkcom.exe to record pcm samples.  The AMBE-3000 is used with passthru mode, so that
speech samples from the codec can be recorded without encoding. file.pcm specifes the
name of the file to be recorded. "seconds" specifies how many seconds to record. 
Interface may be -ppt, -uart, or blank.

lin2a.exe infile outfile
Accepts infile containing linear 16-bit PCM samples and converts to 8-bit a-law stored in outfile.

lin2mu.exe infile outfile
Accepts infile containing linear 16-bit PCM samples and converts to 8-bit u-law stored in outfile.

a2lin.exe infile outfile
Accepts infile containing 8-bit a-law samples and converts to 16-bit linear stored in outfile.

mu2lin.exe infile outfile
Accepts infile containing 8-bit u-law samples and converts to 16-bit linear stored in outfile.

