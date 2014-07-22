echo off
set /p HDKPORT="Enter COM Port:"
set /p HDKBAUD="Enter Baud Rate:"
set /p HDKPORT2="Enter A3kdirect COM Port (or just ENTER to skip):"
PATH %CD%;%PATH%
set HDKVEC=%CD%\..\tv
