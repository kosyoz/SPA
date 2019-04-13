@echo off
title system test 3 queries

..\..\Code\Debug\AutoTester SourceAffectsProcedure.txt Affects.txt out-Affects.xml
..\..\Code\Debug\AutoTester SourceAffectsProcedure.txt AffectsStar.txt out-AffectsStar.xml

echo FINISHED
pause
exit