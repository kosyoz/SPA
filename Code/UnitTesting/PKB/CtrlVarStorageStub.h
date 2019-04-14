#pragma once

#include "CtrlVarStorage.h"

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
if / while pattern
store.addIfControlVariable(5, "apple");
store.addWhileControlVariable(6, "durian");
store.addWhileControlVariable(6, "cherry");
store.addWhileControlVariable(11, "banana");
*/

std::unordered_map<std::string, std::unordered_set<int>> ifVariableToStm = { {"apple", {5}} };

std::unordered_map<std::string, std::unordered_set<int>> whileVariableToStm = { {"cherry", {6}},
{"durian", {6}}, {"banana", {11}} };

std::unordered_set<std::pair<int, std::string>, intStringhash> ifPatternPair =
{ std::pair<int, std::string>(5, "apple") };

std::unordered_set<std::pair<int, std::string>, intStringhash> whilePatternPair =
{ std::pair<int, std::string>(6, "durian"), std::pair<int, std::string>(6, "cherry"),
std::pair<int, std::string>(11, "banana") };