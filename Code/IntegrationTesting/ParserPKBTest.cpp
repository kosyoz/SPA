#include "stdafx.h"
#include "CppUnitTest.h"
#include "Preprocessor.h"
#include "PKB.h"
#include "Parser.h"
#include "Statement.h"
#include "DesignExtractor.h"

#include "../UnitTesting/PKB/PKBStub.h"
#include "../UnitTesting/PKB/FollowStorageStub.h"
#include "../UnitTesting/PKB/ParentStorageStub.h"
#include "../UnitTesting/PKB/ModifyStorageStub.h"
#include "../UnitTesting/PKB/UseStorageStub.h"
#include "../UnitTesting/PKB/CallStorageStub.h"
#include "../UnitTesting/PKB/NextStorageStub.h"
#include "../UnitTesting/PKB/CtrlVarStorageStub.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
	TEST_CLASS(FrontEndPKBTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize) {
			PKB().clear();
			Parser parser = Parser();

			std::vector<Statement> procList;
			std::vector<Statement> procStmList;
			std::vector<Statement> ifStmList;
			std::vector<Statement> elseStmList;
			std::vector<Statement> whileStmList;

			procStmList.push_back(Statement("read apple", 3, 1));
			procStmList.push_back(Statement("call fruit2", 2, 2));
			procStmList.push_back(Statement("print banana", 4, 3));
			procStmList.push_back(Statement("apple = cherry + 10 * banana", 1, 4));
			whileStmList.push_back(Statement("durian = grapes + banana", 1, 7));
			ifStmList.push_back(Statement("while ( durian > cherry )", whileStmList, 5, 6));
			procStmList.push_back(Statement("if (apple <= 0)", ifStmList, 6, 5));
			elseStmList.push_back(Statement("figs = apple * melon / cherry", 1, 8));
			elseStmList.push_back(Statement("call fruit3", 2, 9));
			procStmList.push_back(Statement("else", elseStmList, 7, 5));
			procList.push_back(Statement("procedure fruit", procStmList, 8, 0));
			procStmList.clear();
			whileStmList.clear();

			procStmList.push_back(Statement("pineapple = apple + melon", 1, 10));
			whileStmList.push_back(Statement("call fruit3", 2, 12));
			procStmList.push_back(Statement("while (10 > banana)", whileStmList, 5, 11));
			procList.push_back(Statement("procedure fruit2", procStmList, 8, 0));
			procStmList.clear();

			procStmList.push_back(Statement("print melon", 4, 13));
			procStmList.push_back(Statement("call fruit4", 2, 14));
			procList.push_back(Statement("procedure fruit3", procStmList, 8, 0));
			procStmList.clear();

			procStmList.push_back(Statement("pear = jackfruit + apple", 1, 15));
			procList.push_back(Statement("procedure fruit4", procStmList, 8, 0));
			procStmList.clear();

			parser.parse(procList, 0, "");
		}

		TEST_METHOD(GeneralInformationTest) {
			PKB pkb = PKB();
      
			Assert::IsTrue(PKB().getProcList() == procList);
			Assert::AreEqual(PKB().getTotalStmNo(), 15);
			Assert::IsTrue(PKB().getReadStms() == readStmList);
			Assert::IsTrue(PKB().getPrintStms() == printStmList);
			Assert::IsTrue(PKB().getAssignStms() == assignStmList);
			Assert::IsTrue(PKB().getIfStms() == ifStmList);
			Assert::IsTrue(PKB().getWhileStms() == whileStmList);
			Assert::IsTrue(PKB().getCallStms() == callStmList);
			Assert::IsTrue(PKB().getVariables() == varList);
			Assert::IsTrue(PKB().getConstants() == constList);
			Assert::IsTrue(PKB().getReadPairs() == readPairList);
			Assert::IsTrue(PKB().getPrintPairs() == printPairList);
		}

		TEST_METHOD(FollowRelationTest) {
			PKB pkb = PKB();
			Assert::IsTrue(pkb.getAllFollowers() == followers);
			Assert::IsTrue(pkb.getAllFollowed() == followed);
			Assert::IsTrue(pkb.getFollowPairs() == followPairs);
			Assert::IsTrue(pkb.getFollower(2) == followTable.at(2).follower);
			Assert::IsTrue(pkb.getStmFollowedBy(10) == followTable.at(10).followed);

			//The following should still be empty as DesignExtractor has not populated them
			Assert::IsTrue(pkb.getAllFollowedBy(5) == std::unordered_set<int>{});
			Assert::IsTrue(pkb.getAllFollowing(1) == std::unordered_set<int>{});
			Assert::IsTrue(pkb.getFollowStarPairs() ==
						   std::unordered_set<std::pair<int, int>, intPairhash>{});
		}

		TEST_METHOD(ParentRelationTest) {
			PKB pkb = PKB();
			Assert::IsTrue(pkb.getAllParents() == parents);
			Assert::IsTrue(pkb.getAllChildren() == children);
			Assert::IsTrue(pkb.getParentChildPairs() == parentPair);
			Assert::IsTrue(pkb.getParent(9) == parentTable.at(9).parent);
			Assert::IsTrue(pkb.getChildren(6) == parentTable.at(6).children);

			//The following should still be empty as DesignExtractor has not populated them
			Assert::IsTrue(pkb.getAncestors(7) == std::unordered_set<int>{});
			Assert::IsTrue(pkb.getDescendants(5) == std::unordered_set<int>{});
			Assert::IsTrue(pkb.getAncDescPairs() ==
						   std::unordered_set<std::pair<int, int>, intPairhash>{});
		}

		TEST_METHOD(ModifiesRelationTest) {
			PKB pkb = PKB();
			Assert::IsTrue(pkb.isStmModifying(1, "apple"));
			Assert::IsFalse(pkb.isStmModifying(2, "pineapple"));
			Assert::IsTrue(pkb.getVarModifiedByStm(4) == std::unordered_set<std::string>{"apple"});
			Assert::IsTrue(pkb.getVarModifiedByStm(2) == std::unordered_set<std::string>{});
			Assert::IsTrue(pkb.getStmModifying("apple") == std::unordered_set<int>{1, 4});
			Assert::IsTrue(pkb.getStmModifying("") == std::unordered_set<int>{1, 4, 7, 8, 10, 15});
			Assert::IsTrue(pkb.getStmVarModifyPairs() ==
						   std::unordered_set<std::pair<int, std::string>, intStringhash>{
				std::pair<int, std::string>(1, "apple"), std::pair<int, std::string>(4, "apple"),
				std::pair<int, std::string>(7, "durian"), std::pair<int, std::string>(8, "figs"),
				std::pair<int, std::string>(10, "pineapple"), std::pair<int, std::string>(15, "pear") });
			
			//There is no proc modifies relations as DesignExtractor as not populated it
			Assert::IsTrue(pkb.getProcVarModifyPairs() ==
						   std::unordered_set<std::pair<std::string, std::string>, strPairhash>{});
		}
    
		TEST_METHOD(UsesRelationTest) {
			PKB pkb = PKB();
			Assert::IsTrue(pkb.isStmUsing(3, "banana"));
			Assert::IsFalse(pkb.isStmUsing(2, "apple"));
			Assert::IsTrue(pkb.getVarUsedByStm(7) == std::unordered_set<std::string>{"grapes", "banana"});
			Assert::IsTrue(pkb.getVarUsedByStm(12) == std::unordered_set<std::string>{});
			Assert::IsTrue(pkb.getStmUsing("apple") == std::unordered_set<int>{5, 8, 10, 15});
			Assert::IsTrue(pkb.getStmUsing("") ==
						   std::unordered_set<int>{3, 4, 5, 6, 7, 8, 10, 11, 13, 15});
			Assert::IsTrue(pkb.getStmVarUsePairs() ==
						   std::unordered_set<std::pair<int, std::string>, intStringhash>{
				std::pair<int, std::string>(3, "banana"), std::pair<int, std::string>(4, "banana"),
					std::pair<int, std::string>(4, "cherry"), std::pair<int, std::string>(5, "apple"),
					std::pair<int, std::string>(6, "durian"), std::pair<int, std::string>(6, "cherry"),
					std::pair<int, std::string>(7, "grapes"), std::pair<int, std::string>(7, "banana"),
					std::pair<int, std::string>(8, "apple"), std::pair<int, std::string>(8, "melon"),
					std::pair<int, std::string>(8, "cherry"), std::pair<int, std::string>(10, "apple"),
					std::pair<int, std::string>(10, "melon"), std::pair<int, std::string>(11, "banana"),
					std::pair<int, std::string>(13, "melon"), std::pair<int, std::string>(15, "jackfruit"),
					std::pair<int, std::string>(15, "apple") });

			//There is no proc uses relations as DesignExtractor as not populated it
			Assert::IsTrue(pkb.getProcVarUsePairs() ==
						   std::unordered_set<std::pair<std::string, std::string>, strPairhash>{});
		}

		TEST_METHOD(CallRelationTest) {
			PKB pkb = PKB();
			Assert::IsTrue(pkb.getAllCallers() == callerList);
			Assert::IsTrue(pkb.getAllCallees() == calleeList);
			Assert::IsTrue(pkb.getCallPairs() == callPairList);
			Assert::IsTrue(pkb.getCaller("fruit3") == callTable.at("fruit3").caller);
			Assert::IsTrue(pkb.getCallee("fruit") == callTable.at("fruit").callees);

			//The following should still be empty as DesignExtractor has not populated them
			Assert::IsTrue(pkb.getCallAnc("fruit4") == std::unordered_set<std::string>{});
			Assert::IsTrue(pkb.getCallDesc("fruit") == std::unordered_set<std::string>{});
			Assert::IsTrue(pkb.getCallStarPairs() ==
						   std::unordered_set<std::pair<std::string, std::string>, strPairhash>{});
		}

		TEST_METHOD(PatternTest) {
			PKB pkb = PKB();
			Assert::IsTrue(PKB().findPatternPairs("", false) == patternPairs);
			Assert::IsTrue(PKB().findPattern("pear", " + jackfruit apple ", true) ==
						   std::unordered_set<int>{15});
			Assert::IsTrue(PKB().findPattern(" * 10 banana ", false) ==
						   std::unordered_set<int>{4});

			Assert::IsTrue(CtrlVarStorage().getIfStmWithControlVariable("apple") ==
						   std::unordered_set<int>{5});
			Assert::IsTrue(CtrlVarStorage().getWhileStmWithControlVariable("cherry") ==
						   std::unordered_set<int>{6});
			Assert::IsTrue(CtrlVarStorage().getIfStmControlVariablePair() == ifPatternPair);
			Assert::IsTrue(CtrlVarStorage().getWhileStmControlVariablePair() == whilePatternPair);
		}

		TEST_METHOD(NextRelationTest) {
			PKB pkb = PKB();
			Assert::IsTrue(pkb.getAllNext() == nextList);
			Assert::IsTrue(pkb.getAllPrev() == prevList);
			Assert::IsTrue(pkb.getNextPairs() == nextPairList);
			Assert::IsTrue(pkb.getNext(5) == nextTable.at(5).next);
			Assert::IsTrue(pkb.getPrev(6) == nextTable.at(6).previous);
		}
	};
}