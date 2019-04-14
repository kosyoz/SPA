#include "stdafx.h"
#include "CppUnitTest.h"
#include "Preprocessor.h"
#include "PKB.h"
#include "RunTimeDesignExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting
{
	TEST_CLASS(RTDEPKBTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize) {
			PKB store;
			store.erase();
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
			store.addUsesStm(8, "apple");
			store.addModifiesStm(1, "apple");
			store.addModifiesStm(4, "apple");


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

			store.addNext(1, 2);
			store.addNext(2, 3);
			store.addNext(3, 4);
			store.addNext(4, 5);
			store.addNext(5, 6);
			store.addNext(6, 7);
			store.addNext(7, 6);
			store.addNext(5, 8);
			store.addNext(8, 9);
			store.addNext(10, 11);
			store.addNext(11, 12);
			store.addNext(12, 11);
			store.addNext(13, 14);



			store.addFollow(1, 2);
			store.addFollow(2, 3);
			store.addFollow(3, 4);
			store.addFollow(4, 5);
			store.addFollow(8, 9);
			store.addFollow(10, 11);
			store.addFollow(13, 14);


			store.addConstant("10");
			store.addConstant("0");

			store.addIfContainerStatement(5, 6);

			store.addElseContainerStatement(5, 8);
			store.addElseContainerStatement(5, 9);

			store.addWhileContainerStatement(6, 7);
			store.addWhileContainerStatement(11, 12);
		}
		TEST_METHOD(RTDEAffectsPairTest) {

			PKB store;

			std::unordered_set<std::pair<int, int>, intPairhash> affectsReturn;

			affectsReturn = RunTimeDesignExtractor().getAffectsPair();

			std::unordered_set<std::pair<int, int>, intPairhash> expected;

			expected.insert(std::make_pair(4, 8));

			Assert::IsTrue(affectsReturn == expected);

		}

		TEST_METHOD(RTDEhasAffectsPairTest) {

			PKB store;

			bool hasAffects;

			hasAffects = RunTimeDesignExtractor().hasAffectsRelation();

			Assert::IsTrue(hasAffects);

		}

		TEST_METHOD(RTDEisAffectTest) {

			PKB store;

			bool isAffects;

			isAffects = RunTimeDesignExtractor().isAffect(4, 8);

			Assert::IsTrue(isAffects);

		}

		TEST_METHOD(RTDEAffectsStarPairTest) {

			PKB store;

			std::unordered_set<std::pair<int, int>, intPairhash> affectsStarReturn;

			affectsStarReturn = RunTimeDesignExtractor().getAffectsStarPair();

			std::unordered_set<std::pair<int, int>, intPairhash> expected;

			expected.insert(std::make_pair(4, 8));

			Assert::IsTrue(affectsStarReturn == expected);

		}

		TEST_METHOD_CLEANUP(cleanUP) {
			PKB store;
			store.erase();
		}
	};
}