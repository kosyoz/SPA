#include "stdafx.h"
#include "CppUnitTest.h"
#include "CtrlVarStorageStub.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(CtrlVarStorageTest)
	{
		TEST_METHOD_INITIALIZE(CallStorage_Initialize)
		{
			CtrlVarStorage store;
			store.clear();
			store.addIfControlVariable(5, "apple");
			store.addWhileControlVariable(6, "durian");
			store.addWhileControlVariable(6, "cherry");
			store.addWhileControlVariable(11, "banana");
		}

		TEST_METHOD(getAllIfWithControls_Correct)
		{
			Assert::IsTrue(CtrlVarStorage().getAllIfWithControls() == std::unordered_set<int>{5});
		}

		TEST_METHOD(getAllWhileWithControls_Correct)
		{
			Assert::IsTrue(CtrlVarStorage().getAllWhileWithControls() == std::unordered_set<int>{6, 11});
		}

		TEST_METHOD(getIfStmWithControlVariable_ExistingVariable_Success)
		{
			Assert::IsTrue(CtrlVarStorage().getIfStmWithControlVariable("apple") ==
						   std::unordered_set<int>{5});
		}

		TEST_METHOD(getIfStmWithControlVariable_NonExistingVariable_EmptyResult)
		{
			Assert::IsTrue(CtrlVarStorage().getIfStmWithControlVariable("nonExistant") ==
						   std::unordered_set<int>{});
		}

		TEST_METHOD(getWhileStmWithControlVariable_ExistingVariable_Success)
		{
			Assert::IsTrue(CtrlVarStorage().getWhileStmWithControlVariable("cherry") ==
						   std::unordered_set<int>{6});
		}

		TEST_METHOD(getWhileStmWithControlVariable_NonExistingVariable_EmptyResult)
		{
			Assert::IsTrue(CtrlVarStorage().getWhileStmWithControlVariable("nonExistant") ==
						   std::unordered_set<int>{});
		}

		TEST_METHOD(getIfStmControlVariablePair_Correct)
		{
			Assert::IsTrue(CtrlVarStorage().getIfStmControlVariablePair() == ifPatternPair);
		}

		TEST_METHOD(getWhileStmControlVariablePair_Correct)
		{
			Assert::IsTrue(CtrlVarStorage().getWhileStmControlVariablePair() == whilePatternPair);
		}

	};
}

