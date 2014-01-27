@echo off

rem Define Coder Format shell invocation script path.
set coderFormatPath=c:\program files\coder_format


:: ----- You should not need to edit anything below. ----- ::

if "%~1"=="" goto error
rem Check if at least one argument follows a --undo parameter.
if "%~1"=="--undo" if "%~2"=="" goto error

call php "%coderFormatPath%\coder_format.php" %*
goto :EOF

:error
echo ERROR: Wrong arguments supplied. Please see usage in coder_format.php.
goto :EOF

