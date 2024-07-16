@echo off
@SET PROTOID=FF
@SET DESTADDR=44
REM @SET COM_ADDR=15
call setcom.bat

@REM TC-2 : Send specific packet with priority etc and wait 5 seconds for result from target device
@ECHO Starting dump mode...
ES_SAT_MACGW_CMD v=y TS=YES COM_PORT=%COM_ADDR% DEST_MAC_ADDR=%DESTADDR% TC=1 MAC_PROTOCOL=%PROTOID% PRIORITY=5 INTF=0 MSG=000212345678AABBCC
@REM IF %errorlevel% neq 0 (ren TC_%TESTID% NOK_TC_%TESTID%) ELSE (ren TC_%TESTID% OK_TC_%TESTID%)

exit /b %errorlevel%

:TC_ERR
echo ERROR
exit /b %errorlevel%
