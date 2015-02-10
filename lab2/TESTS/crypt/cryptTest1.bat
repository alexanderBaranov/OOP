..\..\debug\crypt.exe crypt "..\..\debug\crypt.exe" crypt.exe.crypted 123
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed