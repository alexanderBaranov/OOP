..\..\debug\rle.exe pack rle123.exe crypt.exe.decompressed > outFileResultOfRleTest3.txt
FC /B outFileResultOfRleTest3.txt ResultFileOfRleTest3.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed