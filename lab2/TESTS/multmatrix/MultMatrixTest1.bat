..\..\debug\multmatrix.exe matrix1.txt matrix2.txt > outFileResultOfMultMatrix.txt
FC /B outFileResultOfMultMatrix.txt ResultMultMatrixTest1.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed