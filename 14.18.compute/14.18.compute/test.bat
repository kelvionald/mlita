set PROGRAM="%~1"
rem del "output.txt"

copy "test-data\input-1.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-1.txt" > nul || goto err
echo Test 1 passed

copy "test-data\input-2.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-2.txt" > nul || goto err
echo Test 2 passed

copy "test-data\input-3.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-3.txt" > nul || goto err
echo Test 3 passed

copy "test-data\input-4.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-4.txt" > nul || goto err
echo Test 4 passed

copy "test-data\input-5.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-5.txt" > nul || goto err
echo Test 5 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1