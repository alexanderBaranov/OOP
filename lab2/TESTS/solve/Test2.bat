..\..\debug\Solve.exe 1 1 1 > outFileResultOfSolveTest.txt
FC /B outFileResultOfSolveTest.txt ResultFileOfSolveTest2.txt
IF ERRORLEVEL 1 GOTO err
ECHO Program testing succeeded

EXIT

:err
ECHO Program testing failed