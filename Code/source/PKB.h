#pragma once

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#include "FollowStorage.h"
#include "ParentStorage.h"
#include "UseStorage.h"
#include "ModifyStorage.h"
#include "CallStorage.h"
#include "Hasher.h"

enum stmType { read, print, assign, whileStm, ifStm, call};

/*
	Accepts relationship, pattern and other general data from Parser and DesignExtractor and
	stores them here or into their respective Storage classes.
	Reply to queries made by the QueryEvaluator.
*/
class PKB {
public:
	PKB();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//General adder Methods			/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// add a procedure to procList
	void addProc(string procName);

	//add statement to its respective StmList and set stmTypeList[stmNo] to type 
	void addStatement(int stmNo, stmType type);

	// add variable to varList
	void addVariable(string name);

	// add constant to constList
	void addConstant(string value);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Follows adder & setter Methods	/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		add the follows relation in FollowStorage
		Returns false if
			1) the pair is already stored
			2) the followed statement has another follower stored
			3) the follower is following another statement
			4) stm2 <= stm1 or stm1, stm2 <= 0
	*/
	bool addFollow(int stm1, int stm2);

	/*
		Sets the list of followers of 'stm' to be 'stmList' in FollowStorage
		Every FollowStar pair is stored as well
		If stm already has a list of followers, it is not replaced and it return false
	*/
	bool setAllFollowing(int stm, unordered_set<int> stmList);

	/*
		Sets the list of followed of 'stm' to be 'stmList' in FollowStorage
		Every FollowStar pair is stored as well
		If stm already has a list of followed, it is not replaced and it return false
	*/
	bool setAllFollowedBy(int stm, unordered_set<int> stmList);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Parent adder & setter Methods		/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Adds the parent relation into the various lists in the storage
		Returns false if	
			1) the pair is already stored
			2) the child already has another parent
			3) stm2 <= stm1 or stm1, stm2 <= 0
	*/
	bool addParent(int stm1, int stm2);

	/*
		Sets the list of ancestors of 'stm' in ParentStorage
		Each Parent* pair is stored as well
		If stm already has a list of ancestors, it is not replaced and it return false
	*/
	bool setAncestors(int stm, unordered_set<int> stmList);

	/*
		Sets the list of descendants of 'stm' in ParentStorage
		Each Parent* pair is stored as well
		If stm already has a list of descendants, it is not replaced and it return false
	*/
	bool setDescendants(int stm, unordered_set<int> stmList);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Uses adder Methods			/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		add the Uses relation for a Statement in UseStorage
		Returns false if
			1) the pair is already stored
			2) stm <= 0 and variable is an empty string
	*/
	bool addUsesStm(int stm, string variable);

	/*
		add the Uses relation for a Procedure in UseStorage
		Returns false if
			1) the pair is already stored
			2) procedure or variable is an empty string
	*/
	bool addUsesProc(string procedure, string variable);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Modifies adder Methods			/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		add the Modifies relation for a Statement in UseStorage
		Returns false if
			1) the pair is already stored
			2) stm <= 0 and variable is an empty string
	*/
	bool addModifiesStm(int stm, string variable);

	/*
		add the Modifies relation for a Procedure in UseStorage
		Returns false if
			1) the pair is already stored
			2) procedure or variable is an empty string
	*/
	bool addModifiesProc(string procedure, string variable);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pattern adder Methods			/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		add a pattern for an assign statement to patternList
		returns false if 'stm' already exist in the list with another pattern
	*/
	bool addAssignPattern(int stm, string variable, string expr);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Calls adder & setter Methods	/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//adding Calls relationships
	bool addCall(string proc1, string proc2);
	bool setCallAnc(string proc, unordered_set<string> procList);
	bool setCallDesc(string proc, unordered_set<string> procList);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//General Getter Methods	/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// returns the stored list of procedures
	unordered_set<string> getProcList();

	// returns the total number of statements in the entire program
	int getTotalStmNo();

	// return the statement type of stm
	stmType getStmType(int stm);

	// returns the stored list of read statements
	unordered_set<int> getReadStms();

	// returns the stored list of print statements
	unordered_set<int> getPrintStms();

	// returns the stored list of assign statements
	unordered_set<int> getAssignStms();

	// returns the stored list of if statements
	unordered_set<int> getIfStms();

	// returns the stored list of while statements
	unordered_set<int> getWhileStms();

	// returns the stored list of variables
	unordered_set<string> getVariables();

	// returns the stored list of constants
	unordered_set<string> getConstants();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Follows Getter Methods	/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// checks if there is at least one follows relation
	bool hasFollowRelation();

	// checks if the relation Follows*(stm1, stm2) exist
	bool hasFollowStarPair(int stm1, int stm2);

	/*
		return the statement followed by 'stm'
		return 0 if 'stm' is not found
	*/
	int getStmFollowedBy(int stm);

	/*
		return the statement following 'stm'
		return 0 if 'stm' is not found
	*/
	int getFollower(int stm);

	/*
		return a list of statements that is directly/indirectly following 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<int> getAllFollowing(int stm);

	/*
		return a list of statements that is directly/indirectly followed by 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<int> getAllFollowedBy(int stm);

	// returns a list of all statements that follows another
	unordered_set<int> getAllFollowers();

	// returns a list of all statements that is followed by another
	unordered_set<int> getAllFollowed();

	// returns a list of all follows pairs
	unordered_set< pair<int, int>, intPairhash> getFollowPairs();

	// returns a list of all follows* pairs
	unordered_set< pair<int, int>, intPairhash> getFollowStarPairs();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Parent Getter Methods		/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// checks if there is at least one Parent relationship
	bool hasParentRelation();

	// checks if stm is a parent of another
	bool isParent(int stm);

	// checks if stm is a child of another
	bool isChild(int stm);

	// checks if the relation Parent*(stm1, stm2) exist
	bool hasAncDescPair(int stm1, int stm2);

	/*
		return the statement that is the parent of 'stm'
		return 0 if 'stm' is not found
	*/
	int getParent(int stm);

	/*
		return the list of statements that is the children of 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<int> getChildren(int stm);

	/*
		return the list of statements that is the ancestors of 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<int> getAncestors(int stm);

	/*
		return the list of statements that is the descendants of 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<int> getDescendants(int stm);

	// returns a list of all statements that is the parent of another
	unordered_set<int> getAllParents();

	// returns a list of all statements that is the child of another
	unordered_set<int> getAllChildren();

	// returns a list of all parent pairs
	unordered_set< pair<int, int>, intPairhash> getParentChildPairs();

	// returns a list of all parent* pairs
	unordered_set< pair<int, int>, intPairhash> getAncDescPairs();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Uses Getter Methods		/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// checks if the relation Uses(stm, variable) exist
	bool isStmUsing(int stm, string variable);

	// checks if the relation Uses(procedure, variable) exist
	bool isProcUsing(string procedure, string variable);

	/*
		return the list of variables that is used by 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<string> getVarUsedByStm(int stm);

	/*
		return the list of variables that is used by 'procedure'
		return an empty set if 'procedure' is not found
	*/
	unordered_set<string> getVarUsedByProc(string procedure);

	/*
		return the list of statements that is using 'variable'
		return an empty set if 'variable' is not found
	*/
	unordered_set<int> getStmUsing(string variable);

	/*
		return the list of procedure that is using 'variable'
		return an empty set if 'variable' is not found
	*/
	unordered_set<string> getProcUsing(string variable);

	// returns a list of all Uses pairs for statements
	unordered_set< pair<int, string>, intStringhash> getStmVarUsePairs();

	// returns a list of all Uses pairs for procedures
	unordered_set< pair<string, string>, strPairhash> getProcVarUsePairs();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Modifies Getter Methods	/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// checks if the relation Modifies(stm, variable) exist
	bool isStmModifying(int stm, string variable);

	// checks if the relation Modifies(procedure, variable) exist
	bool isProcModifying(string procedure, string variable);

	/*
		return the list of variables that is modified by 'stm'
		return an empty set if 'stm' is not found
	*/
	unordered_set<string> getVarModifiedByStm(int stm);

	/*
		return the list of variables that is modified by 'procedure'
		return an empty set if 'procedure' is not found
	*/
	unordered_set<string> getVarModifiedByProc(string procedure);

	/*
		return the list of statements that is modifying 'variable'
		return an empty set if 'variable' is not found
	*/
	unordered_set<int> getStmModifying(string variable);

	/*
		return the list of procedures that is modifying 'variable'
		return an empty set if 'variable' is not found
	*/
	unordered_set<string> getProcModifying(string variable);

	// returns a list of all Modifies pairs for statements
	unordered_set< pair<int, string>, intStringhash> getStmVarModifyPairs();

	// returns a list of all Modifies pairs for procedures
	unordered_set< pair<string, string>, strPairhash> getProcVarModifyPairs();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pattern Getter Methods	/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
		Search for assign statements with pattern matching
			- the specified variable ont the left side and
			- the specified expression on the right side
		If isExclusive is true, the function finds for an exact match to the specfied expression.
		If false, it finds for a matching substring instead.
	*/
	unordered_set<int> findPattern(string variable, string expr, bool isExclusive);

	/*
		Search for assign statements with pattern matching
			- the specified expression on the right side
		If isExclusive is true, the function finds for an exact match to the specfied expression.
		If false, it finds for a matching substring instead.
	*/
	unordered_set<int> findPattern(string expr, bool isExclusive);

	/*
		Search for pairs of an assign statement and left-hand side variable with
			the right side expression matching the specified expression
		If isExclusive is true, the function finds for an exact match to the specfied expression.
		If false, it finds for a matching substring instead.
	*/
	unordered_set<pair<int, string>, intStringhash> findPatternPairs(string expr, bool isExclusive);

private:
	static unordered_set<string> procList;
	static vector<stmType> stmTypeList;
	static unordered_set<string> varList;
	static unordered_set<string> constList;
	static unordered_set<int> readStmList;
	static unordered_set<int> printStmList;
	static unordered_set<int> assignStmList;
	static unordered_set<int> ifStmList;
	static unordered_set<int> whileStmList;

	static FollowStorage fStore;
	static ParentStorage pStore;
	static UseStorage uStore;
	static ModifyStorage mStore;
	static CallStorage cStore;
	static unordered_map<int, pair<string, string> > patternList;
};