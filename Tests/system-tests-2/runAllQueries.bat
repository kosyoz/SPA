@echo off
title system test 2 queries

..\..\Code\Release\AutoTester source-nesting.txt Affects.txt out-Affects.xml
..\..\Code\Release\AutoTester source-nesting.txt AffectsStar.txt out-AffectsStar.xml

..\..\Code\Release\AutoTester source-nesting.txt Calls.txt out-Calls.xml
..\..\Code\Release\AutoTester source-nesting.txt CallsStar.txt out-CallsStar.xml

..\..\Code\Release\AutoTester source-nesting.txt Follows.txt out-Follows.xml
..\..\Code\Release\AutoTester source-nesting.txt FollowsStar.txt out-FollowsStar.xml

..\..\Code\Release\AutoTester source-nesting.txt Modifies.txt out-Modifies.xml
..\..\Code\Release\AutoTester source-nesting.txt Uses.txt out-Uses.xml

..\..\Code\Release\AutoTester source-nesting.txt Next.txt out-Next.xml
..\..\Code\Release\AutoTester source-nesting.txt NextStar.txt out-NextStar.xml

..\..\Code\Release\AutoTester source-nesting.txt Parent.txt out-Parent.xml
..\..\Code\Release\AutoTester source-nesting.txt ParentStar.txt out-ParentStar.xml

..\..\Code\Release\AutoTester source-nesting.txt PatternAssign.txt out-PatternAssign.xml
..\..\Code\Release\AutoTester source-nesting.txt PatternIf.txt out-PatternIf.xml
..\..\Code\Release\AutoTester source-nesting.txt PatternWhile.txt out-PatternWhile.xml

..\..\Code\Release\AutoTester source-nesting.txt With.txt out-With.xml

echo FINISHED
pause
exit