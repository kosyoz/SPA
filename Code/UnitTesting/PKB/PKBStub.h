#pragma once

#include "PKB.h"

/*
	procedure fruit {
1		read apple;
2		call fruit2;
3		print banana;
4		apple = cherry + 10 * banana;
5		if (apple <= 0) then {
6			while ( durian > cherry ) {
7				durian = grapes + banana;
			}
		} else {
8			figs = apple * melon / cherry;
9			call fruit3;
		}
	}

	procedure fruit2 {
10		pineapple = apple + melon;
11		while (10 > banana) {
12			call fruit3;
		}
	}

	procedure fruit3 {
13		print melon;
14		call fruit4;
	}

	procedure fruit4 {
15		pear = jackfruit + apple;
	}
*/
/*
store.addProc("fruit");
store.addProc("fruit2");
store.addProc("fruit3");
store.addProc("fruit4");

store.addStatement(1, read, "fruit");
store.addStatement(2, call, "fruit");
store.addStatement(3, print, "fruit");
store.addStatement(4, assign, "fruit");
store.addStatement(5, ifStm, "fruit");
store.addStatement(6, whileStm, "fruit");
store.addStatement(7, assign, "fruit");
store.addStatement(8, assign, "fruit");
store.addStatement(9, call, "fruit");
store.addStatement(10, assign, "fruit2");
store.addStatement(11, whileStm, "fruit2");
store.addStatement(12, call, "fruit2");
store.addStatement(13, print, "fruit3");
store.addStatement(14, call, "fruit3");
store.addStatement(15, assign, "fruit4");

store.addUsesStm(3, "banana");
store.addUsesStm(13, "melon");
store.addModifiesStm(1, "apple");

store.addAssignPattern(4, "apple", " + cherry * 10 banana ");
store.addAssignPattern(7, "durian", " + grapes banana ");
store.addAssignPattern(8, "figs", " * apple / melon cherry ");
store.addAssignPattern(10, "pineapple", " + apple melon ");
store.addAssignPattern(15, "pear", " + jackfruit apple ");

store.addVariable("apple");
store.addVariable("banana");
store.addVariable("cherry");
store.addVariable("durian");
store.addVariable("durian");
store.addVariable("grapes");
store.addVariable("figs");
store.addVariable("melon");
store.addVariable("pineapple");
store.addVariable("pear");
store.addVariable("jackfruit");

store.addConstant("10");
store.addConstant("0");

store.addIfContainerStatement(5, 6);
store.addIfContainerStatement(5, 7);

store.addElseContainerStatement(5, 8);
store.addElseContainerStatement(5, 9);

store.addWhileContainerStatement(6, 7);
store.addWhileContainerStatement(11, 12);
*/


std::unordered_set<std::string> procList = {"fruit", "fruit2", "fruit3", "fruit4"};

std::unordered_map<std::string, std::vector<int>> procStmMap =
{ {"fruit", {1, 2, 3, 4, 5, 6, 7, 8, 9}}, {"fruit2", {10, 11, 12}}, {"fruit3", {13, 14}},
{"fruit4", {15}} };

std::vector<std::string> stmProcList = {"fruit", "fruit", "fruit", "fruit", "fruit", "fruit",
"fruit", "fruit", "fruit", "fruit2", "fruit2", "fruit2", "fruit3", "fruit3", "fruit4" };

std::vector<stmType> stmTypeList = {read, call, print, assign, ifStm, whileStm, assign, assign, call,
assign, whileStm, call, print, call, assign};

std::unordered_set<std::string> varList = {"apple", "banana", "cherry", "durian", "grapes", "figs",
"melon", "pineapple", "pear", "jackfruit"};

std::unordered_set<std::string> constList = {"10", "0"};
std::unordered_set<int> readStmList = {1};
std::unordered_set<int> printStmList = {3, 13};
std::unordered_set<int> assignStmList = {4, 7, 8, 10, 15};
std::unordered_set<int> ifStmList = {5};
std::unordered_set<int> whileStmList = {6, 11};
std::unordered_set<int> callStmList = {2, 9, 12, 14};

std::unordered_set< std::pair<int, std::string>, intStringhash > readPairList =
	{ std::pair<int, std::string>(1, "apple") };
std::unordered_set< std::pair<int, std::string>, intStringhash > printPairList = 
	{ std::pair<int, std::string>(3, "banana"), std::pair<int, std::string>(13, "melon") };
std::unordered_map<int, std::vector<int>> whileBlockStmLists = { {6, {7}}, {11, {12}} };
std::unordered_map<int, std::vector<int>> ifBlockStmLists = { {5, {6, 7}} };
std::unordered_map<int, std::vector<int>> elseBlockStmLists = { {5, {8, 9}} };

std::unordered_map<int, std::pair<std::string, std::string> > patternList = 
{ {4, {"apple", " + cherry * 10 banana "}}, {7, {"durian", " + grapes banana "}},
{8, {"figs", " * apple / melon cherry "}}, {10, {"pineapple", " + apple melon "}},
{15, {"pear", " + jackfruit apple "}} };

std::unordered_set<std::pair<int, std::string>, intStringhash> patternPairs =
{ {4, "apple"}, {7, "durian"}, {8, "figs"}, {10, "pineapple"}, {15, "pear"} };
