@echo off
@cls
@title hdkpacket      ---------- AMBE+2 Vocoder ----------
@call hdkversion.bat
::hdkvectors.bat sets an environment variable named VECTORS that lists all the test vectors to be processed
@call hdkvectors.bat
::hdkrates.bat sets an environment variable named RATES that lists all the rates to be processed
@call hdkrates.bat
@if exist errorlog del /q errorlog
@echo VECTORS=%VECTORS%
@echo RATES=%RATES%
@for %%R IN (%RATES%) do @for %%V in (%VECTORS%) do @for %%I in (-uart,-ppt) do @( call hdkpacketsub.bat %%V %%R %%I ) 

