#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include <GrowingArray/GrowingArray.h>
#include <NameSpaceAliases.h>
#include "TestClassAddingNumbers.h"
#include <functional>

namespace outbildGrowingArray
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestClassFunction)
		{
			CU::GrowingArray<TestClassAddingNumbers> myTestArray;
			myTestArray.Init(100);
			myTestArray.Resize(100);

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 0);
			}

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				myTestArray[iTest].IncreaseByOne();
			}

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 1);
			}
		}

		TEST_METHOD(CallFunctionOnAllMembers)
		{
			CU::GrowingArray<TestClassAddingNumbers> myTestArray;
			myTestArray.Init(100);
			myTestArray.Resize(100);

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 0);
			}

			//CU::CallMemberFunctionOnArray<TestClassAddingNumbers>(myTestArray, std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));
			myTestArray.CallFunctionOnAllMembers(std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 1);
			}

			//CU::CallMemberFunctionOnArray<TestClassAddingNumbers>(myTestArray, std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));
			myTestArray.CallFunctionOnAllMembers(std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 2);
			}
		}

		TEST_METHOD(CallFunctionWithArguments)
		{
			CU::GrowingArray<TestClassAddingNumbers> myTestArray;
			myTestArray.Init(100);
			myTestArray.Resize(100);

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 0);
			}
			
			using std::placeholders::_1;

//			CU::CallMemberFunctionOnArray<TestClassAddingNumbers>(myTestArray, std::bind(&TestClassAddingNumbers::IncreaseByNumber, _1, 3));
			myTestArray.CallFunctionOnAllMembers(std::bind(&TestClassAddingNumbers::IncreaseByNumber, _1, 3));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 3);
			}
		}

		TEST_METHOD(CallFunctionOnAllMembersOnArray)
		{
			CU::GrowingArray<TestClassAddingNumbers> myTestArray;
			myTestArray.Init(100);
			myTestArray.Resize(100);

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 0);
			}

			myTestArray.CallFunctionOnAllMembers(std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 1);
			}

			myTestArray.CallFunctionOnAllMembers(std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest].GetTestValue() == 2);
			}
		}

		TEST_METHOD(CallFunctionOnAllMembersOnArrayWithPointers)
		{
			CU::GrowingArray<TestClassAddingNumbers*> myTestArray;
			myTestArray.Init(100);
			//myTestArray.Resize(100);

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				myTestArray.Add(new TestClassAddingNumbers());
			}

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest]->GetTestValue() == 0);
			}

			myTestArray.CallFunctionOnAllMembers(std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest]->GetTestValue() == 1);
			}

			myTestArray.CallFunctionOnAllMembers(std::mem_fn(&TestClassAddingNumbers::IncreaseByOne));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest]->GetTestValue() == 2);
			}
		}

		TEST_METHOD(CallFunctionWithArgumentsPointers)
		{
			CU::GrowingArray<TestClassAddingNumbers*> myTestArray;
			myTestArray.Init(100);
			//myTestArray.Resize(100);

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				myTestArray.Add(new TestClassAddingNumbers());
			}

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest]->GetTestValue() == 0);
			}

			using std::placeholders::_1;

			//CU::CallMemberFunctionOnArray<TestClassAddingNumbers>(myTestArray, std::bind(&TestClassAddingNumbers::IncreaseByNumber, _1, 3));
			myTestArray.CallFunctionOnAllMembers(std::bind(&TestClassAddingNumbers::IncreaseByNumber, _1, 3));

			for (unsigned short iTest = 0; iTest < myTestArray.Size(); ++iTest)
			{
				Assert::IsTrue(myTestArray[iTest]->GetTestValue() == 3);
			}
		}
	};
}