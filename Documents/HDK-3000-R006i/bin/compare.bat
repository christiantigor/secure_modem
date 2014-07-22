:: %1 is the first file to compare
:: %2 is the second file to compare

::the benefit of using this instead of using fc /b directly is that you
::can clean up the screen output and get rid of a "no differences encountered"
::compare is quiet unless it finds an error, in which case, it will display
::one line to stdout indicating error and all the differences go to errorlog
::I put a Control-G in to make it beep for errors.

@echo comparing %1 %2 >> errorlog
@fc /b /a %1 %2 >> errorlog
@if %ERRORLEVEL% NEQ 0 echo Files are Different 
