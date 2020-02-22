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

copy "test-data\input-6.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-6.txt" > nul || goto err
echo Test 6 passed

copy "test-data\input-7.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-7.txt" > nul || goto err
echo Test 7 passed

copy "test-data\input-8.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-8.txt" > nul || goto err
echo Test 8 passed

copy "test-data\input-9.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-9.txt" > nul || goto err
echo Test 9 passed

copy "test-data\input-10.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-10.txt" > nul || goto err
echo Test 10 passed

copy "test-data\input-11.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-11.txt" > nul || goto err
echo Test 11 passed

copy "test-data\input-12.txt" "input.txt" > nul
%PROGRAM%
fc.exe "output.txt" "test-data/output-12.txt" > nul || goto err
echo Test 12 passed

echo OK
exit 0

:err
echo Program testing failed
exit 1