echo off
cls
title "hdkechotest - AMBE+2 Vocoder"
call hdkversion.bat
echo "This test verifies that the AMBE3000 echo canceller works properly."
echo "The following hardware setup must be used:"
echo "1. Single HDK with JP13 installed."
echo "2. J3 looped to J2 with at least 6 dB attenuation (using resistor)"
echo "The test will play out a .bit file by decoding it and sending the"
echo "decoded samples to the codec and out on J3.  At the same time, the"
echo "encoder is running and encoding the speech signal on J2 and"
echo "storing the encoded speech into an output .bit file.  The process"
echo "is repeated first with the echo canceller off to created tmp1.bit,"
echo "and again with the echo canceller on to create tmp2.bit"
echo "Next both tmp1.bit and tmp2.bit are decoded to get speech samples,"
echo "which are stored in tmp1.dat and tmp2.dat."
echo ""
echo "For now the test requires you to look at tmp1.bit and tmp2.bit"
echo "and  determine if the echo canceller works.  TBD: write some code"
echo "to analyze tmp1.dat and tmp2.dat and make some calculations."
echo ""
pause

hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -r 0     -playrecord %HDKVEC%\r0\dam.bit tmp1.bit
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -r 0 -ec -playrecord %HDKVEC%\r0\dam.bit tmp2.bit
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -r 0     -dec tmp1.bit tmp1.dat
hdkcom -ppt -q -port %HDKPORT% %HDKBAUD% -r 0     -dec tmp2.bit tmp2.dat

echo "Test complete. Look at signals tmp1.dat and tmp2.dat"
