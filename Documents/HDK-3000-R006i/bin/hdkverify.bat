echo off
cls
title hdkverify      ---------- AMBE+2 Vocoder ----------
call hdkversion.bat
echo VERIFYING THE VOCODER, UART/PPT PACKET INTERFACE, DTX, COMPAND...
echo encode dam rate 0 using ppt interface
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -enc -r 0 %HDKVEC%\dam.pcm tmp
call compare tmp %HDKVEC%\r0\dam.bit
echo decode clean rate 5 using ppt interface
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -dec -r 5 %HDKVEC%\r5\clean.bit tmp
call compare tmp %HDKVEC%\r5\clean.pcm
echo encode noisy rate 9, dtx enabled, using ppt interface
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -enc -r 9 -dtx 10000 %HDKVEC%\noisy.pcm tmp
call compare tmp %HDKVEC%\r9\noisy_dtx.bit
echo decode dam rate 16, dtx enabled, using ppt interface
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -dec -r 16 -dtx 10000 %HDKVEC%\r16\dam_dtx.bit tmp
call compare tmp %HDKVEC%\r16\dam_dtx.pcm
echo encode clean rate 23, ulaw companding, using uart interface
hdkcom -uart -q -port %HDKPORT% %HDKBAUD% -enc -r 23 -ulaw %HDKVEC%\clean.pcmu tmp
call compare tmp %HDKVEC%\r23\clean.bitu
echo decode noisy rate 33, ulaw companding, using uart interface
hdkcom -uart -q -port %HDKPORT% %HDKBAUD% -dec -r 33 -ulaw %HDKVEC%\r33\noisy.bitu tmp
call compare tmp %HDKVEC%\r33\noisy.pcmu
echo encode dam rate 34, alaw companding, using uart interface
hdkcom -uart -q -port %HDKPORT% %HDKBAUD% -enc -r 34 -alaw %HDKVEC%\dam.pcma tmp
call compare tmp %HDKVEC%\r34\dam.bita
echo decode dam rate 46, alaw companding, using uart interface
hdkcom -uart -q -port %HDKPORT% %HDKBAUD% -dec -r 46 -alaw %HDKVEC%\r46\clean.bita tmp
call compare tmp %HDKVEC%\r46\clean.pcma
echo decode dam rate 55, 1 percent BER, hard-decision, using ppt interface
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -dec -r 55 %HDKVEC%\r55\dam_e1_hd.bit tmp
call compare tmp %HDKVEC%\r55\dam_e1_hd.pcm
echo decode dam rate 51, 2 percent BER, soft-decision, using uart interface
hdkcom -uart -q -port %HDKPORT% %HDKBAUD% -decsd -r 51 %HDKVEC%\r51\dam_e2_sd.bit tmp
call compare tmp %HDKVEC%\r51\dam_e2_sd.pcm
echo encode dam, custom rate 2800 BPS, using uart interface 
hdkcom -uart -q -port %HDKPORT% %HDKBAUD% -enc -r 0x0038 0x0765 0x0000 0x0000 0x0000 0x0038 %HDKVEC%\dam.pcm tmp
::we dont have a vector in tv to compare to for this vector, so we play it out and listen
echo play the bits just encoded to handset and lineout using the ppt interface
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -r 0x0038 0x0765 0x0000 0x0000 0x0000 0x0038 -play tmp

echo codec mode, decode dam.bit rate 53 to handset/lineout using ppt interface
call hdkplaybit 53 dam.bit -ppt
echo codec passthru mode, play dam.pcm to handset/lineout using ppt interface
call hdkplaypcm 35 dam.pcm -ppt

echo VERIFYING THE HANDSET AND CODEC...
echo RECORD 3 SECONDS THROUGH THE HANDSET...
pause
call hdkrecordbit.bat 16 test.bit 3 
call hdkplaybit.bat 16 test.bit


if (%HDKPORT2%)==() goto skipa3kdirect
echo For A3K direct tests, please connect %HDKPORT2% to connector P1 now!
pause 
echo switching HDK into a3kdirect mode...
hdkcom -q -port %HDKPORT% %HDKBAUD% -mode a3kdirect

echo get version using a3kdirect interface...
hdkcom -q -port %HDKPORT2% %HDKBAUD% -version -a3kdirect

echo VERIFYING THE HANDSET AND CODEC...
echo RECORD THEN PLAY 3 SECONDS THROUGH THE HANDSET USING PASSTHRU AND A3KDIRECT...
pause
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD%  -passthru -record 3 test.pcm
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD%  -passthru -play test.pcm

echo PACKET MODE TESTS USING A3KDIRECT
echo encode dam rate 1 using a3kdirect mode
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -enc -r 1 %HDKVEC%\dam.pcm tmp
call compare tmp %HDKVEC%\r1\dam.bit
echo decode clean rate 6 using a3kdirect mode
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -dec -r 6 %HDKVEC%\r6\clean.bit tmp
call compare tmp %HDKVEC%\r6\clean.pcm
echo encode noisy rate 10, dtx enabled, using a3kdirect mode
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -enc -r 10 -dtx 10000 %HDKVEC%\noisy.pcm tmp
call compare tmp %HDKVEC%\r10\noisy_dtx.bit
echo encode clean rate 24, ulaw companding, using a3kdirect mode
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -enc -r 24 -ulaw %HDKVEC%\clean.pcmu tmp
call compare tmp %HDKVEC%\r24\clean.bitu
echo decode dam rate 47, alaw companding, using a3kdirect mode
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -dec -r 47 -alaw %HDKVEC%\r47\dam.bita tmp
call compare tmp %HDKVEC%\r47\dam.pcma
echo decode dam rate 25, 2 percent BER, hard-decision, using a3kdirect interface
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -dec -r 25 %HDKVEC%\r25\dam_e2_hd.bit tmp
call compare tmp %HDKVEC%\r25\dam_e2_hd.pcm
echo decode dam rate 61, 5 percent BER, soft-decision, using a3kdirect interface
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -decsd -r 61 %HDKVEC%\r61\dam_e5_sd.bit tmp
call compare tmp %HDKVEC%\r61\dam_e5_sd.pcm
echo CODEC MODE TESTS USING A3KDIRECT
echo codec mode, decode dam.bit rate 54 to handset/lineout using a3kdirect interface
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -r 54 -play %HDKVEC%\r54\dam.bit 
echo codec passthru mode, play dam.pcm to handset/lineout using a3kdirect interface
hdkcom -a3kdirect -q -port %HDKPORT2% %HDKBAUD% -passthru -play %HDKVEC%\dam.pcm

echo switching HDK into idle mode...
hdkcom -q -port %HDKPORT% %HDKBAUD% -mode idle

:skipa3kdirect

