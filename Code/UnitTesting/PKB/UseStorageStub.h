#pragma once

#include "UseStorage.h"

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
Uses
store.addUsesStm(2, "apple");
store.addUsesStm(2, "melon");
store.addUsesStm(2, "banana");
store.addUsesStm(2, "jackfruit");
store.addUsesStm(3, "banana"); *
store.addUsesStm(4, "banana"); *
store.addUsesStm(4, "cherry"); *
store.addUsesStm(5, "apple"); *
store.addUsesStm(5, "durian");
store.addUsesStm(5, "cherry");
store.addUsesStm(5, "grapes");
store.addUsesStm(5, "banana");
store.addUsesStm(5, "melon");
store.addUsesStm(5, "jackfruit");
store.addUsesStm(6, "durian"); *
store.addUsesStm(6, "cherry"); *
store.addUsesStm(6, "grapes");
store.addUsesStm(6, "banana");
store.addUsesStm(7, "grapes"); *
store.addUsesStm(7, "banana"); *
store.addUsesStm(8, "apple"); *
store.addUsesStm(8, "melon"); *
store.addUsesStm(8, "cherry"); *
store.addUsesStm(9, "apple");
store.addUsesStm(9, "melon");
store.addUsesStm(9, "jackfruit");
store.addUsesStm(10, "apple"); *
store.addUsesStm(10, "melon"); *
store.addUsesStm(11, "banana"); *
store.addUsesStm(11, "melon");
store.addUsesStm(11, "apple");
store.addUsesStm(11, "jackfruit");
store.addUsesStm(12, "melon");
store.addUsesStm(12, "apple");
store.addUsesStm(12, "jackfruit");
store.addUsesStm(13, "melon"); *
store.addUsesStm(14, "jackfruit");
store.addUsesStm(14, "apple");
store.addUsesStm(15, "jackfruit"); *
store.addUsesStm(15, "apple"); *

store.addUsesProc("fruit", "apple"); *
store.addUsesProc("fruit", "banana"); *
store.addUsesProc("fruit", "cherry"); *
store.addUsesProc("fruit", "durian"); *
store.addUsesProc("fruit", "grapes"); *
store.addUsesProc("fruit", "melon"); *
store.addUsesProc("fruit", "jackfruit");
store.addUsesProc("fruit2", "apple"); *
store.addUsesProc("fruit2", "melon"); *
store.addUsesProc("fruit2", "banana"); *
store.addUsesProc("fruit2", "jackfruit");
store.addUsesProc("fruit3", "melon"); *
store.addUsesProc("fruit3", "jackfruit");
store.addUsesProc("fruit3", "apple");
store.addUsesProc("fruit4", "jackfruit"); *
store.addUsesProc("fruit4", "apple"); *
*/

std::unordered_map<int, std::unordered_set<std::string> > stmToVarMapUses =
{ {2, {"apple", "melon", "banana", "jackfruit"}}, {3, {"banana"}}, {4, {"banana", "cherry"}},
{5, {"apple", "durian", "cherry", "grapes", "banana", "melon", "jackfruit"}},
{6, {"durian", "cherry", "grapes", "banana"}}, {7, {"grapes", "banana"}},
{8, {"apple", "melon", "cherry"}}, {9, {"apple", "melon", "jackfruit"}}, {10, {"apple", "melon"}},
{11, {"banana", "melon", "apple", "jackfruit"}}, {12, {"apple", "melon", "jackfruit"}}, {13, {"melon"}},
{14, {"jackfruit", "apple"}}, {15, {"jackfruit", "apple"}} };

std::unordered_map<std::string, std::unordered_set<std::string> > procToVarMapUses = 
{ {"fruit", {"apple", "durian", "cherry", "grapes", "banana", "melon", "jackfruit"}},
{"fruit2", {"banana", "melon", "apple", "jackfruit"}}, {"fruit3", {"apple", "melon", "jackfruit"}},
{"fruit4", {"jackfruit", "apple"}} };

std::unordered_map<std::string, std::unordered_set<int> > varToStmMapUses = 
{ {"apple", {2, 5, 8, 9, 10, 11, 12, 14, 15}}, {"banana", {2, 3, 4, 5, 6, 7, 11}},
{"cherry", {4, 5, 6, 8, }}, {"durian", {5, 6}}, {"grapes", {5, 6, 7}},
{"melon", {2, 5, 8, 9, 10, 11, 12, 13}}, {"jackfruit", {2, 5, 9, 11, 12, 14, 15}},
{"", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}} };

std::unordered_map<std::string, std::unordered_set<std::string> > varToProcMapUses = 
{ {"apple", {"fruit", "fruit2", "fruit3", "fruit4"}}, {"banana", {"fruit", "fruit2"}},
{"cherry", {"fruit"}}, {"durian", {"fruit"}}, {"grapes", {"fruit"}},
{"melon", {"fruit", "fruit2", "fruit3"}}, {"jackfruit", {"fruit", "fruit2", "fruit3", "fruit4"}},
{"", {"fruit", "fruit2", "fruit3", "fruit4"}} };

std::unordered_set<std::pair<int, std::string>, intStringhash> stmVarPairs =
	{ std::pair<int, std::string>(2, "apple"), std::pair<int, std::string>(2, "melon"),
	std::pair<int, std::string>(2, "banana"), std::pair<int, std::string>(2, "jackfruit"),
	std::pair<int, std::string>(3, "banana"), std::pair<int, std::string>(4, "banana"),
	std::pair<int, std::string>(4, "cherry"), std::pair<int, std::string>(5, "apple"),
	std::pair<int, std::string>(5, "durian"), std::pair<int, std::string>(5, "cherry"),
	std::pair<int, std::string>(5, "grapes"), std::pair<int, std::string>(5, "banana"),
	std::pair<int, std::string>(5, "melon"), std::pair<int, std::string>(5, "jackfruit"),
	std::pair<int, std::string>(6, "durian"), std::pair<int, std::string>(6, "cherry"),
	std::pair<int, std::string>(6, "grapes"), std::pair<int, std::string>(6, "banana"),
	std::pair<int, std::string>(7, "grapes"), std::pair<int, std::string>(7, "banana"),
	std::pair<int, std::string>(8, "apple"), std::pair<int, std::string>(8, "melon"),
	std::pair<int, std::string>(8, "cherry"), std::pair<int, std::string>(9, "apple"),
	std::pair<int, std::string>(9, "melon"), std::pair<int, std::string>(9, "jackfruit"),
	std::pair<int, std::string>(10, "apple"), std::pair<int, std::string>(10, "melon"),
	std::pair<int, std::string>(11, "banana"), std::pair<int, std::string>(11, "melon"),
	std::pair<int, std::string>(11, "apple"), std::pair<int, std::string>(11, "jackfruit"),
	std::pair<int, std::string>(12, "melon"), std::pair<int, std::string>(12, "apple"),
	std::pair<int, std::string>(12, "jackfruit"), std::pair<int, std::string>(13, "melon"),
	std::pair<int, std::string>(14, "jackfruit"), std::pair<int, std::string>(14, "apple"),
	std::pair<int, std::string>(15, "jackfruit"), std::pair<int, std::string>(15, "apple") };

std::unordered_set<std::pair<std::string, std::string>, strPairhash> procVarPairs =
{ std::pair<std::string, std::string>("fruit", "apple"),
std::pair<std::string, std::string>("fruit", "banana"),
std::pair<std::string, std::string>("fruit", "cherry"),
std::pair<std::string, std::string>("fruit", "durian"),
std::pair<std::string, std::string>("fruit", "grapes"),
std::pair<std::string, std::string>("fruit", "melon"),
std::pair<std::string, std::string>("fruit", "jackfruit"),
std::pair<std::string, std::string>("fruit2", "apple"),
std::pair<std::string, std::string>("fruit2", "melon"),
std::pair<std::string, std::string>("fruit2", "banana"),
std::pair<std::string, std::string>("fruit2", "jackfruit"),
std::pair<std::string, std::string>("fruit3", "melon"),
std::pair<std::string, std::string>("fruit3", "jackfruit"),
std::pair<std::string, std::string>("fruit3", "apple"),
std::pair<std::string, std::string>("fruit4", "jackfruit"),
std::pair<std::string, std::string>("fruit4", "apple") };