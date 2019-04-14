#pragma once

#include "ModifyStorage.h"

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
Modify
store.addModifiesStm(1, "apple"); *
store.addModifiesStm(2, "pineapple");
store.addModifiesStm(2, "pear");
store.addModifiesStm(4, "apple"); *
store.addModifiesStm(5, "durian");
store.addModifiesStm(5, "figs");
store.addModifiesStm(5, "pear");
store.addModifiesStm(6, "durian");
store.addModifiesStm(7, "durian"); *
store.addModifiesStm(8, "figs"); *
store.addModifiesStm(9, "pear");
store.addModifiesStm(10, "pineapple"); *
store.addModifiesStm(11, "pear");
store.addModifiesStm(12, "pear");
store.addModifiesStm(14, "pear");
store.addModifiesStm(15, "pear"); *
store.addModifiesProc("fruit", "apple"); *
store.addModifiesProc("fruit", "pineapple");
store.addModifiesProc("fruit", "durian"); *
store.addModifiesProc("fruit", "figs"); *
store.addModifiesProc("fruit", "pear");
store.addModifiesProc("fruit2", "pineapple"); *
store.addModifiesProc("fruit2", "pear");
store.addModifiesProc("fruit3", "pear");
store.addModifiesProc("fruit4", "pear"); *
*/
std::unordered_map<int, std::unordered_set<std::string>> stmToVarMapModifies = 
{ {1, {"apple"}}, {2, {"pineapple", "pear"}}, {4, {"apple"}}, {5, {"durian", "figs", "pear"}},
{6, {"durian"}}, {7, {"durian"}}, {8, {"figs"}}, {9, {"pear"}}, {10, {"pineapple"}},
{11, {"pear"}}, {12, {"pear"}}, {14, {"pear"}}, {15, {"pear"}} };

std::unordered_map<std::string, std::unordered_set<std::string>> procToVarMapModifies = 
{ {"fruit", {"apple", "pineapple", "durian", "figs", "pear"}}, {"fruit2", {"pineapple", "pear"}},
{"fruit3", {"pear"}}, {"fruit4", {"pear"}} };

std::unordered_map<std::string, std::unordered_set<int> > varToStmMapModifies = 
{ {"apple", {1, 4}}, {"pineapple", {2, 10}}, {"pear", {2, 5, 9, 11, 12, 14, 15}},
{"durian", {5, 6, 7}}, {"figs", {5, 8}}, {"", {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15}} };

std::unordered_map<std::string, std::unordered_set<std::string> > varToProcMapModifies =
{ {"apple", {"fruit"}}, {"pineapple", {"fruit", "fruit2"}},
{"durian", {"fruit"}}, {"figs", {"fruit"}}, {"pear", {"fruit", "fruit2", "fruit3", "fruit4"}},
{"", {"fruit", "fruit2", "fruit3", "fruit4"}} };

std::unordered_set<std::pair<int, std::string>, intStringhash> ModifyStmVarPairs =
{ std::pair<int, std::string>(1, "apple"), std::pair<int, std::string>(2, "pineapple"),
std::pair<int, std::string>(2, "pear"), std::pair<int, std::string>(4, "apple"),
std::pair<int, std::string>(5, "durian"), std::pair<int, std::string>(5, "figs"),
std::pair<int, std::string>(5, "pear"), std::pair<int, std::string>(6, "durian"),
std::pair<int, std::string>(7, "durian"), std::pair<int, std::string>(8, "figs"),
std::pair<int, std::string>(9, "pear"), std::pair<int, std::string>(10, "pineapple"),
std::pair<int, std::string>(11, "pear"), std::pair<int, std::string>(12, "pear"),
std::pair<int, std::string>(14, "pear"), std::pair<int, std::string>(15, "pear") };

std::unordered_set<std::pair<std::string, std::string>, strPairhash> ModifyProcVarPairs =
{ std::pair<std::string, std::string>("fruit", "apple"),
std::pair<std::string, std::string>("fruit", "pineapple"),
std::pair<std::string, std::string>("fruit", "durian"), 
std::pair<std::string, std::string>("fruit", "figs"),
std::pair<std::string, std::string>("fruit", "pear"),
std::pair<std::string, std::string>("fruit2", "pineapple"),
std::pair<std::string, std::string>("fruit2", "pear"),
std::pair<std::string, std::string>("fruit3", "pear"),
std::pair<std::string, std::string>("fruit4", "pear") };