#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <CU/Map/Map.h>
#include <CU/NameSpaceAliases.h>

namespace HashingTheHAshTestdaHashWithTehhash
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CreateTheMap)
		{
			CU::Map<std::string, int> test;
		}

		TEST_METHOD(KeyExists)
		{
			CU::Map<std::string, int> testMap;

			Assert::IsFalse(testMap.KeyExists("derp"));
		}

		TEST_METHOD(SetValue)
		{
			CU::Map<std::string, int> testMap;

			testMap["derp"] = 3;

			Assert::IsTrue(testMap.KeyExists("derp"));
			Assert::IsFalse(testMap.KeyExists("herp"));
		}

		TEST_METHOD(AccessValue)
		{
			CU::Map<std::string, int> testMap;

			testMap["derp"] = 3;

			Assert::IsTrue(testMap["derp"] == 3);
		}

		TEST_METHOD(AccessManyValues)
		{
			CU::Map<std::string, int> testMap;

			testMap["derp"] = 3;
			testMap["herp"] = 1;
			testMap["merp"] = 4;
			testMap["serp"] = 5;

			Assert::IsTrue(testMap["derp"] == 3);
			Assert::IsTrue(testMap["herp"] == 1);
			Assert::IsTrue(testMap["merp"] == 4);
			Assert::IsTrue(testMap["serp"] == 5);
			Assert::IsFalse(testMap.KeyExists("klerk"));
		}

		TEST_METHOD(DeleteValue)
		{
			CU::Map<std::string, int> testMap;

			testMap["derp"] = 3;
			testMap["herp"] = 1;

			Assert::IsTrue(testMap["derp"] == 3);
			Assert::IsTrue(testMap["herp"] == 1);

			testMap.Delete("herp");

			Assert::IsTrue(testMap.KeyExists("derp"));
			Assert::IsTrue(testMap["derp"] == 3);
			Assert::IsFalse(testMap.KeyExists("herp"));
		}

		TEST_METHOD(TestWithStrings)
		{
			CU::Map<std::string, std::string> testMap;

			Assert::IsFalse(testMap.KeyExists("lerp"));

			testMap["lerp"] = "YlvaBehöverSova";

			Assert::IsTrue(testMap.KeyExists("lerp"));

			Assert::IsTrue(testMap["lerp"] == "YlvaBehöverSova");
		}

		TEST_METHOD(TestWithPointers)
		{
			CU::Map<std::string, float*> testMap;

			float * testPointer1 = new float(3.f);
			float * testPointer2 = new float(4.3f);

			Assert::IsFalse(testMap.KeyExists("lerp"));

			testMap["lerp"] = testPointer1;
			testMap["ylf"] = testPointer2;

			Assert::IsTrue(testMap.KeyExists("lerp"));

			Assert::IsTrue(testMap.KeyExists("ylf"));
			Assert::IsTrue(testMap["lerp"] == testPointer1);
		}
	};
}