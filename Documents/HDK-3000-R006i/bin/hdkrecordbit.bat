::this encodes the handset input signal, encodes it and stores it to a file
::%1 is the vocoder rate index
::%2 is the name of the file to record
::%3 is the record duration in seconds
::%4 -uart or -ppt may optionally be specified
echo off
hdkcom -q -port %HDKPORT% %HDKBAUD% %4 -r %1 -record %3 %2

