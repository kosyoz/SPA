#pragma once

#include "AffectsEvaluator.h"	

/*
Evaluate trivial Affects clause 
*/
std::string AffectsEvaluator::isTrivial(std::string firstArgument, std::string secondArgument) {
	bool result;
	if (firstArgument == "_") {
		if (secondArgument == "_") {
			result = PKB().hasAffectsRelation();
		}
		else if (QueryUtility::isInteger(secondArgument)) {
			result = PKB().isAffected(stoi(secondArgument));
		}
	}
	else if (QueryUtility::isInteger(firstArgument)) {
		if (secondArgument == "_") {
			result = PKB().isAffector(stoi(firstArgument));
		}
		else if (QueryUtility::isInteger(secondArgument)) {
			result = PKB().hasAffectPair(stoi(firstArgument), stoi(secondArgument));
		}
	}
	return QueryUtility::truthValue(result);
}

/*
Evaluate non trivial Affects clause
*/
std::unordered_map<std::string, std::vector<std::string>> AffectsEvaluator::evaluate(
	std::unordered_map<std::string, std::string> declarations,
	std::string firstArgument, std::string secondArgument) {
	std::unordered_map<std::string, std::vector<std::string>> tableResult;
	std::vector<std::string> emptyVec;
	if (QueryUtility::isSynonym(firstArgument)) {
		if (secondArgument == "_") {
			tableResult = QueryUtility::to_mapvec(firstArgument, PKB().getAllAffectors());
		}
		else if (QueryUtility::isInteger(secondArgument)) {
			tableResult = QueryUtility::to_mapvec(firstArgument, PKB().getAffector(
				stoi(secondArgument)));
		}
		else if (firstArgument == secondArgument) {
			tableResult = QueryUtility::to_mapvec(firstArgument, QueryUtility::getTwin(
				PKB().getAffectPairs()));
		}
		else {
			tableResult = QueryUtility::to_mapvec(firstArgument, secondArgument,
				PKB().getAffectPairs());
		}
	}
	if (QueryUtility::isSynonym(secondArgument)) {
		if (firstArgument == "_") {
			tableResult = QueryUtility::to_mapvec(secondArgument, PKB().getAllAffected());
		}
		else if (QueryUtility::isInteger(firstArgument)) {
			tableResult = QueryUtility::to_mapvec(secondArgument, PKB().getAffected(
				stoi(firstArgument)));
		}
	}
	return tableResult;
}