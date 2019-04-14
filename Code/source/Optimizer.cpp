#include "Optimizer.h"

/*
* Constructor function
*/
Optimizer::Optimizer(
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> st,
	std::vector<std::pair<std::string, std::string>> w,
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> p,
	std::vector<std::string> s, std::unordered_map<std::string, std::string> d) {
	suchThatClauses = st;
	withClauses = w;
	patternClauses = p;
	selectClause = s;
	declarations = d;
	//internal reference of clauses will follow: p, w, st
	psize = patternClauses.size();
	wsize = withClauses.size();
}

/*
* Main processing function
*/
void Optimizer::groupClause() {
	//extract synonyms and create the syn-cl and cl-syn map
	int clauseSize = psize + wsize + suchThatClauses.size();
	for (int i = 0; i < clauseSize; i++) {
		groupByClauseType(i);
	}
	//while loop to order non-synonym clauses
	std::pair<int, int> cl;
	while (!pq.empty()) { //
		cl = pq.top();
		nonsynonym.push_back(getClause(cl.second));
		pq.pop();
	}
	processSelect();
	bool isTrivial;
	//while loop to chain clauses (Dijkstra)
	while (!clSet.empty()) {
		pq.push(*clSet.begin()); //use the first in set (ordered by priority)
		clSet.erase(clSet.begin()); //clause removed from bookkeeping sets
		isTrivial = mapGraph();
		if (isTrivial) {
			trivial.push_back(graph);
		} else {
			nontrivial.push_back(graph);
		}
		graph.clear();
	}
}

/* Preprocesses select clause for O(1) time for comparison */
void Optimizer::processSelect() {
	for (std::vector<std::string>::iterator it = selectClause.begin(); it != selectClause.end(); ++it) {
		if ((*it).find(".") != std::string::npos) { //is attribute
			selectSet.insert((*it).substr(0, (*it).find(".")));
		} else {
			selectSet.insert(*it);
		}

	}
}

/*
* Creates a hashmap of syn-clause and clause-syn, which will be used for graph traversal
*/
void Optimizer::groupByClauseType(int i) {
	std::pair<int, std::vector<std::string>> prioritySyn;
	//clauses are represented internally by int, in the order pattern, with, st
	if (i >= (wsize + psize)) {
		prioritySyn = extractSuchThatSyn(i - wsize - psize);
		if (prioritySyn.first != 0) {
			createMaps(prioritySyn.second, std::make_pair(prioritySyn.first, i));
		}
	} else if (i >= psize) {
		prioritySyn = extractWithSyn(i - psize);
		if (prioritySyn.first != 0) {
			createMaps(prioritySyn.second, std::make_pair(prioritySyn.first, i));
		}
	} else {
		prioritySyn = extractPatternSyn(i);
		if (prioritySyn.first != 0) {
			createMaps(prioritySyn.second, std::make_pair(prioritySyn.first, i));
		}
	}
}

/*
* Creates syn-cl and cl-syn maps
*/
void Optimizer::createMaps(std::vector<std::string> synLst, std::pair<int, int> cl) {
	clMap[cl.second] = synLst;
	clSet.insert(cl);
	for (std::vector<std::string>::iterator it = synLst.begin(); it != synLst.end(); ++it) {
		if (synMap.find(*it) == synMap.end()) {
			synMap[*it] = std::priority_queue<std::pair<int, int>>();
			synSet.insert(*it);
		}
		synMap[*it].push(cl);
	}
}

/*
* Chains synonyms and clauses together
* Input: NIL
* Output: isTrivial
* Bookeeping: as this is Dijkstra, a synSet and clSet is used for bookkeeping
  i.e. once a clause/synonym is accessed, no other synonym/clause can access it
  As the for loop is implemented, the algorithm is guaranteed to access all synonyms of the clause and vice versa
* Note: The actual clause, rather than the internal reference, is added to the results graph
*/
bool Optimizer::mapGraph() {
	std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> clause;
	bool isTrivial = true;
	std::pair<int, int> cl;
	while (!pq.empty()) {
		cl = pq.top();
		clause = getClause(cl.second);
		pq.pop();
		graph.push_back(clause);
		isTrivial = mapClauses(cl, isTrivial);
	}
	return isTrivial;
}

/*
* Chains synonyms and clauses together
* Input: clause, isTrivial
* Output: isTrivial
* Bookeeping: as this is Dijkstra, a synSet and clSet is used for bookkeeping
  i.e. once a clause/synonym is accessed, no other synonym/clause can access it
  As the for loop is implemented, the algorithm is guaranteed to access all synonyms of the clause and vice versa
* Note: function meant to loop through synonyms of clause to find connected clauses
*/
bool Optimizer::mapClauses(std::pair<int,int> cl, bool isTrivial) {
	for (std::vector<std::string>::iterator it = clMap[cl.second].begin(); it != clMap[cl.second].end(); ++it) {
		if (synSet.find(*it) != synSet.end()) { //check if synonym is already (partially) processed
			isTrivial = mapSynonym(*it, isTrivial);
		}
	}
	return isTrivial;
}

/*
* Chains synonyms and clauses together
* Input: synonym, isTrivial
* Output: isTrivial
* Bookeeping: as this is Dijkstra, a synSet and clSet is used for bookkeeping
  i.e. once a clause/synonym is accessed, no other synonym/clause can access it
  As the for loop is implemented, the algorithm is guaranteed to access all synonyms of the clause and vice versa
* Note: Group is assumed to be trivial until a select synonym matches
  function meant to loop through clauses of the particular synonym to get connected clauses
*/
bool Optimizer::mapSynonym(std::string syn, bool isTrivial) {
	//check if syn is part of select if group is trivial
	if (isTrivial) {
		isTrivial = selectSet.find(syn) == selectSet.end();
	}
	synSet.erase(syn); //synonym removed from bookkeeping sets
	while (!synMap[syn].empty()) {
		std::pair<int, int> cl = synMap[syn].top();
		synMap[syn].pop();
		if (clSet.find(cl) != clSet.end()) { //check if clause is already processed
			pq.push(cl);
			clSet.erase(cl); //clause removed from bookkeeping sets
		}
	}
	return isTrivial;
}

/*
* To extract synonym from the such that clauses
* Input: index of such that clause to be examined
* Output: int (priority of clause), and vector<string> (vector of synonyms)
* If clause has no synonyms --> add to nonsynonym
* Else give priority and synLst for chaining
*/
std::pair<int, std::vector<std::string>> Optimizer::extractSuchThatSyn(int index) {
	std::vector<std::string> synLst;
	std::string r = suchThatClauses.at(index).first;
	std::string f = suchThatClauses.at(index).second.first;
	std::string s = suchThatClauses.at(index).second.second;
	int tmp1 = OptimizerUtility::getSuchThatEntityType(f);
	int tmp2 = OptimizerUtility::getSuchThatEntityType(s);
	if (tmp1 != 1 && tmp2 != 1) { //if nonsyn
		pq.push(std::make_pair(OptimizerUtility::getNoSynSuchThatPriority(r, tmp1 + tmp2), 
			index + wsize + psize));
		tmp1 = 0;
	} else {
		int synNum = 0;
		if (tmp1 > 0) synNum++;
		if (tmp2 > 0) synNum++;
		if (tmp1 == 1) synLst.push_back(f);
		if (tmp2 == 1) synLst.push_back(s);
		tmp1 = OptimizerUtility::getSuchThatPriority(r, synNum);
	}
	return std::make_pair(tmp1, synLst);
}

/*
* To extract synonym from the pattern clauses
* Input: index of pattern clause to be examined
* Output: int (priority of clause), and vector<string> (vector of synonyms)
* Gives priority and synLst for chaining
*/
std::pair<int, std::vector<std::string>> Optimizer::extractPatternSyn(int index) {
	std::vector<std::string> synLst;
	std::string syn = patternClauses.at(index).first;
	std::string f = patternClauses.at(index).second.first;
	std::string s = patternClauses.at(index).second.second;
	int tmp1 = OptimizerUtility::getPatternEntityType1(f);
	//get from declaration --> syn type of syn
	std::string type = declarations[syn];
	synLst.push_back(syn);
	int tmp2 = 0;
	if (type.compare("assign") == 0) {
		tmp2 = OptimizerUtility::getPatternEntityType2(s);
	} 
	if (tmp1 == 1) {
		synLst.push_back(f);	
	}
	int p = OptimizerUtility::getPatternPriority(type, tmp1, tmp2);
	return std::make_pair(p, synLst);
}

/*
* To extract synonym from the with clauses
* Input: index of with clause to be examined
* Output: int (priority of clause), and vector<string> (vector of synonyms)
* If clause has no synonyms --> add to nonsynonym
* Else give priority and synLst for chaining
*/
std::pair<int, std::vector<std::string>> Optimizer::extractWithSyn(int index) {
	std::vector<std::string> synLst;
	std::string f = withClauses.at(index).first;
	std::string s = withClauses.at(index).second;
	int synNum = 0;
	int tmp = 0;
	if (OptimizerUtility::isWithSynonym(f)) {
		synLst.push_back(f.substr(0, f.find(".")));
		synNum++;
	} else if (isProg_line(f)) {
		synLst.push_back(f);
		synNum++;
	}
	if (OptimizerUtility::isWithSynonym(s)) {
		synLst.push_back(s.substr(0, s.find(".")));
		synNum++;
	} else if (isProg_line(s)) {
		synLst.push_back(s);
		synNum++;
	}
	if (synNum == 0) {
		pq.push(std::make_pair(19, index + psize));
	} else {
		tmp = OptimizerUtility::getWithPriority(synNum);
	}
	return std::make_pair(tmp, synLst);
}

/*
* Checks whether synonym is prog_line for processing of with clause
*/
bool Optimizer::isProg_line(std::string str) {
	bool res = false;
	if (declarations.find(str) != declarations.end()) {
		res = declarations[str].compare("prog_line") == 0;
	}
	return res;
}

/* Getter functions for retrieving clauses */
std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>>> Optimizer::getTrivial() {
	return trivial;
}
std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>>> Optimizer::getNonTrivial() {
	return nontrivial;
}
std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>> Optimizer::getNonSynonym() {
	return nonsynonym;
}

std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> Optimizer::getClause(int cl) {
	std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> clause;
	if (cl >= psize + wsize) {
		int index = cl - psize - wsize;
		clause = std::make_pair(std::make_pair("st", suchThatClauses.at(index).first), suchThatClauses.at(index).second);
	} else if (cl >= psize) {
		clause = std::make_pair(std::make_pair("with", "with"), withClauses.at(cl - psize));
	} else {
		clause = std::make_pair(std::make_pair("pattern", patternClauses.at(cl).first), patternClauses.at(cl).second);
	}
	return clause;
}