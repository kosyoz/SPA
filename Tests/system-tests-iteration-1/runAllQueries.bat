@echo off
title system test 1 queries

..\Debug\AutoTester source1.txt queries1.txt out-1.xml
..\Debug\AutoTester source1.txt irregular-queries1.txt out-irregular.xml
..\Debug\AutoTester source2.txt queries2.txt out-2.xml
..\Debug\AutoTester source3.txt queries3.txt out-3.xml
..\Debug\AutoTester source4.txt queries4.txt out-4.xml

echo FINISHED
pause
exit