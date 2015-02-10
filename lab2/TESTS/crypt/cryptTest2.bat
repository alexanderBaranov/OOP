..\..\debug\crypt.exe decrypt crypt.exe.crypted crypt.exe.decrypted 123
IF ERRORLEVEL 1 GOTO err
FC /B "..\..\debug\crypt.exe" crypt.exe.decrypted
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed