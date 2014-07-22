:: %1 specify file to processs
:: %2 specify the rate 
@echo off
@FOR %%E IN ( e1 e2 e5 e10 ) do @(
	@echo decode r%2\%1_%%E_hd.bit
	@hdkcom -q -port %HDKPORT% %HDKBAUD% -dec -r %2 %HDKVEC%\r%2\%1_%%E_hd.bit tmp
	@call compare tmp %HDKVEC%\r%2\%1_%%E_hd.pcm
	@echo decode r%2\%1_%%E_sd.bit
	@hdkcom -q -port %HDKPORT% %HDKBAUD% -decsd -r %2 %HDKVEC%\r%2\%1_%%E_sd.bit tmp
	@call compare tmp %HDKVEC%\r%2\%1_%%E_sd.pcm
)
