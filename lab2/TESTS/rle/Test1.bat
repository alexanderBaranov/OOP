..\..\debug\rle.exe pack "..\..\debug\rle.exe" rle.exe.compressed
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed