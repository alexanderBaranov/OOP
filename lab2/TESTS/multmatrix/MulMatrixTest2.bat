..\..\debug\multmatrix.exe matrix1_3x3.txt matrix2_3x3.txt > outFileResultOfMultMatrix2.txt
FC /B outFileResultOfMultMatrix2.txt ResultMultMatrixTest2.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed