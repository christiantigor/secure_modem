:: %1 specify file to processs
:: %2 specify the rate 
:: %3 specify -ppt or -uart
::specify the com port and baud rate
@echo off  
echo encode %1 rate=%2 (%3)
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -enc -r %2 %HDKVEC%\%1.pcm tmp
call compare tmp %HDKVEC%\r%2\%1.bit
echo decode %1 rate=%2 (%3)		
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -dec -r %2 %HDKVEC%\r%2\%1.bit tmp
call compare tmp %HDKVEC%\r%2\%1.pcm
echo encode %1 rate=%2 with dtx enabled  (%3)
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -enc -r %2 -dtx 10000 %HDKVEC%\%1.pcm tmp
call compare tmp %HDKVEC%\r%2\%1_dtx.bit
echo decode %1 rate=%2 with dtx enabled (%3)	
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -dec -r %2 -dtx 10000 %HDKVEC%\r%2\%1_dtx.bit tmp
call compare tmp %HDKVEC%\r%2\%1_dtx.pcm
echo encode %1 rate=%2 u-law companding (%3)
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -enc -r %2 -ulaw %HDKVEC%\%1.pcmu tmp
call compare tmp %HDKVEC%\r%2\%1.bitu
echo decode %1 rate=%2 u-law companding (%3)
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -dec -r %2 -ulaw %HDKVEC%\r%2\%1.bitu tmp
call compare tmp %HDKVEC%\r%2\%1.pcmu
echo encode %1 rate=%2 A-law companding (%3)
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -enc -r %2 -alaw %HDKVEC%\%1.pcma tmp
call compare tmp %HDKVEC%\r%2\%1.bita
echo decode %1 rate=%2 A-law companding (%3)
hdkcom %3 -q -port %HDKPORT% %HDKBAUD% -dec -r %2 -alaw %HDKVEC%\r%2\%1.bita tmp
call compare tmp %HDKVEC%\r%2\%1.pcma
