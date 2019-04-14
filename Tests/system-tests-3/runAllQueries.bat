@echo off
title system test 3 queries

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Affects.txt out-Affects.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt AffectsStar.txt out-AffectsStar.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Calls.txt out-Calls.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt CallsStar.txt out-CallsStar.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Follows.txt out-Follows.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt FollowsStar.txt out-FollowsStar.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Modifies.txt out-Modifies.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt Uses.txt out-Uses.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Next.txt out-Next.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt NextStar.txt out-NextStar.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt NoCondition.txt out-NoCondition.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Parent.txt out-Parent.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt ParentStar.txt out-ParentStar.xml

..\..\Code\Release\AutoTester sourceAlphanumeric.txt Boolean.txt out-Boolean.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt With.txt out-With.xml


..\..\Code\Release\AutoTester sourceAlphanumeric.txt PatternWhile.txt out-PatternWhile.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt PatternIf.txt out-PatternIf.xml
..\..\Code\Release\AutoTester sourceAlphanumeric.txt PatternAssign.txt out-PatternAssign.xml



echo FINISHED
pause
exit