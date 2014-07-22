@echo off
@cls
@title hdkerr      ---------- AMBE+2 Vocoder ----------
@call hdkversion.bat
::hdkrates.bat sets an environment variable named RATES that lists all the rates to be processed
@call hdkrates.bat
@if exist errorlog del /q errorlog
@echo RATES=%RATES%
@FOR %%R IN (%RATES%) do @for %%V in ( dam ) do @( call hdkerrsub.bat %%V %%R ) 

