@echo off
title system test 1 queries

..\..\Code\Release\AutoTester sourceDemo.txt Calls.txt out-Calls.xml
..\..\Code\Release\AutoTester sourceDemo.txt CallsStar.txt out-CallsStar.xml

..\..\Code\Release\AutoTester sourceDemo.txt Parent.txt out-Parent.xml
..\..\Code\Release\AutoTester sourceDemo.txt ParentStar.txt out-ParentStar.xml

..\..\Code\Release\AutoTester sourceDemo.txt Follows.txt out-Follows.xml
..\..\Code\Release\AutoTester sourceDemo.txt FollowsStar.txt out-FollowsStar.xml

..\..\Code\Release\AutoTester sourceDemo.txt Modifies.txt out-Modifies.xml
..\..\Code\Release\AutoTester sourceDemo.txt Uses.txt out-Uses.xml


..\..\Code\Release\AutoTester sourceDemo.txt Multiple-easy.txt out-Multiple-easy.xml
..\..\Code\Release\AutoTester sourceDemo.txt Multiple.txt out-Multiple.xml

..\..\Code\Release\AutoTester sourceDemo.txt Next.txt out-Next.xml
..\..\Code\Release\AutoTester sourceDemo.txt NextStar.txt out-NextStar.xml

..\..\Code\Release\AutoTester sourceDemo.txt NoClause.txt out-NoClause.xml

..\..\Code\Release\AutoTester sourceDemo.txt Boolean.txt out-Boolean.xml

..\..\Code\Release\AutoTester sourceDemo.txt Pattern.txt out-Pattern.xml

..\..\Code\Release\AutoTester sourceDemo.txt WithClause.txt out-WithClause.xml

..\..\Code\Release\AutoTester sourceDemo.txt Tuples.txt out-Tuples.xml


echo FINISHED
pause
exit