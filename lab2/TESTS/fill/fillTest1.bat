..\..\debug\fill.exe fillInputFile.txt fillOutputFile.txt
IF ERRORLEVEL 1 GOTO err
FC /B fillOutputFile.txt fillOutputTest1.txt
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed