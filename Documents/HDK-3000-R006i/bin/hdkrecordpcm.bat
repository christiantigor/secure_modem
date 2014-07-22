::this records the handset input signal and stores it to a file using a3k passthru mode
::%1 is the name of the file to record
::%2 is the record duration in seconds
::%3 -uart or -ppt may optionally be specified
echo off

hdkcom -q -port %HDKPORT% %HDKBAUD% %3 -passthru -record %2 %1

