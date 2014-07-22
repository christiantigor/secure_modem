::this decodes the specified bit file and plays the result through the handset
::%1 is the vocoder rate index
::%2 is the name of the file to play
::%3 -uart or -ppt may optionally be specified
::if the specified file does not exist, then look in the directory specified by HDKVEC
echo off
if exist %2 (
	hdkcom -q -port %HDKPORT% %HDKBAUD% %3 -r %1 -play %2
) else if exist %HDKVEC%\r%1\%2 (
	hdkcom -q -port %HDKPORT% %HDKBAUD% %3 -r %1 -play %HDKVEC%\r%1\%2 
) else (
	echo "the file %2 or %HDKVEC%\r%1\%2 does not exist"
)
