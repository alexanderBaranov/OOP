..\..\debug\Solve.exe 16 17 1 > outFileResultOfSolveTest.txt
FC /B outFileResultOfSolveTest.txt ResultFileOfSolveTest1.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed