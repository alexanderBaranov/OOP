..\..\debug\crypt.exe crypt crypt123.exe crypt.exe.decrypted 123 > outFileResultOfCryptTest3.txt
FC /B outFileResultOfCryptTest3.txt ResultFileOfCryptTest3.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed