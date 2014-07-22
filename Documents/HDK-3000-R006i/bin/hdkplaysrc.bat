::this plays the specified PCM file through the handset, using a3k passthru mode 
::%1 is the name of the file to play
::looks for the file in the directory specified by HDKVEC
echo off
if exist %HDKVEC%\%1 (
	hdkcom -q -port %HDKPORT% %HDKBAUD% -passthru -play %HDKVEC%\%1 
) else (
	echo "the file %HDKVEC%\%1 does not exist"
)
