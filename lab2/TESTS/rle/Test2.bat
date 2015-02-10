..\..\debug\rle.exe unpack rle.exe.compressed rle.exe.decompressed
IF ERRORLEVEL 1 GOTO err
FC /B "..\..\debug\rle.exe" rle.exe.decompressed
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed