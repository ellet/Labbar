#include "stdafx.h"
#include "CppUnitTest.h"
#include "GrowingArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace CommonUtilities;

template class GrowingArray<int*>;

namespace GrowingArrayTHETEST
{		
	TEST_CLASS(UnitTest1)
	{
	public:
	
		TEST_METHOD(Testing_init)
		{
			CommonUtilities::GrowingArray<int> test;
			GrowingArray<int> thisNormalArray;
			thisNormalArray.Init(110, true);


		}

		TEST_METHOD(Testing_other_constructor)
		{

			GrowingArray<int> thisPrettyArray = GrowingArray<int>(110);
		}

		TEST_METHOD(_Testing_Growth)
		{

			GrowingArray<int> thisPrettyArray = GrowingArray<int>(110);
			for (int i = 0; i < 10000; ++i)
			{
				thisPrettyArray.Add(5);
			}
			assert(thisPrettyArray.Size() >= 10000 && "Didn't grow enough");
		}

		TEST_METHOD(Testing_pointers)
		{

			GrowingArray<int*> thisPrettyArray;
			thisPrettyArray.Init(200);
			int* temp = new int(100);
			thisPrettyArray.Add(temp);
			for (int i = 1; i < 100; ++i)
			{
				thisPrettyArray.Add(new int(i));
			}

			assert(thisPrettyArray.Find(temp) != thisPrettyArray.FoundNone);
			unsigned short thisVariable = thisPrettyArray.Find(temp);
			int* thisPointer = thisPrettyArray.GetLast();
			thisPrettyArray.DeleteCyclic(temp);


			assert(thisPointer == thisPrettyArray[thisVariable]);
			assert(thisPrettyArray.Find(temp) == thisPrettyArray.FoundNone);

			thisPrettyArray.DeleteAll();

		}


		TEST_METHOD(testing_insert)
		{
			GrowingArray<int> thisPrettyArray;
			thisPrettyArray.Init(20);
			int temp = 100;
			for (int i = 0; i < 20; ++i)
			{
				thisPrettyArray.Add(i);
			}
			thisPrettyArray.Insert(7, temp);

			assert(thisPrettyArray.Find(temp) == 7);
			assert(thisPrettyArray.Size() == 21);
			assert(thisPrettyArray.Find(7) == 8);
		}


	};
}