#include "stdafx.h"
#include "CppUnitTest.h"
#include "GrowingArray.h"
#include <string>
#include <assert.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
template CommonUtilities::GrowingArray<int*>;

struct Huge
{
	int myData[100000];
};

typedef CommonUtilities::GrowingArray<int> GAInt;
typedef CommonUtilities::GrowingArray<Huge*> GAHugePtr;
typedef CommonUtilities::GrowingArray<Huge> GAHuge;
typedef CommonUtilities::GrowingArray<int*> GAIntPtr;
typedef CommonUtilities::GrowingArray<std::string> GAStr;

namespace GrowingArray_TestProgram
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Insert)
		{
			GAInt ga;
			ga.Init(1, true);
			ga.Add(123);
			for (int i = 0; i < 10; ++i)
			{
				ga.Insert(0, i);
			}

			assert(ga[0] == 9);
			assert(ga[9] == 0);
			int val = 99;
			ga.Insert(5, val);
			assert(ga[5] == 99);
			assert(ga[9] == 1);
			assert(ga[0] == 9);
		}

		TEST_METHOD(EqualOperatorNoSafeMode)
		{
			GAInt ga;
			ga.Init(2, false);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}

			GAInt ga2;
			ga2 = ga;

			for (int i = 0; i < 10; ++i)
			{
				assert(ga[i] == ga2[i]);
			}
		}

		TEST_METHOD(EqualOperatorSafeMode)
		{
			GAStr ga;
			std::string txt = "adadjaksjdaksdjkasdksajdksajdkajasd";
			ga.Init(10, true);
			for (int i = 0; i < 20; ++i)
			{
				ga.Add(txt + char(i));
			}

			GAStr ga2;
			ga2.Init(1, false);
			ga2 = ga;
			for (int i = 0; i < 20; ++i)
			{
				assert(ga[i] == ga2[i]);
			}
		}

		TEST_METHOD(GrowingSafeMode)
		{
			GAStr ga;
			std::string txt = "adadjaksjdaksdjkasdksajdksajdkajasd";
			ga.Init(1, true);
			for (int i = 0; i < 90; ++i)
			{
				ga.Add(txt + char(i));
			}				
		}

		TEST_METHOD(RemoveCyclicIndex)
		{
			GAInt ga;
			ga.Init(1, false);

			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}

			ga.RemoveCyclicAtIndex(2);
			assert(ga[2] == 9);
			assert(ga.Size() == 9);

			ga.RemoveCyclicAtIndex(0);
			assert(ga[0] == 8);

			ga.RemoveCyclicAtIndex(7);
			assert(ga[6] == 6);

			assert(ga.Size() == 7);
		}

		TEST_METHOD(RemoveCyclicValue)
		{
			GAInt ga;
			ga.Init(1, false);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}

			ga.RemoveCyclic(2);
			assert(ga[2] == 9);
			assert(ga.Size() == 9);

			ga.RemoveCyclic(0);
			assert(ga[0] == 8);

			ga.RemoveCyclic(7);
			assert(ga[6] == 6);

			assert(ga.Size() == 7);
		}

		TEST_METHOD(RemoveAll)
		{
			GAInt ga;
			ga.Init(1, false);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}

			ga.RemoveAll();
			assert(ga.Size() == 0);
		}

		TEST_METHOD(CopyConstrSafeMode)
		{
			GAStr ga;
			std::string txt = "adadjaksjdaksdjkasdksajdksajdkajasd";
			ga.Init(10, true);
			for (int i = 0; i < 20; ++i)
			{
				ga.Add(txt + char(i));
			}

			GAStr ga2(ga);
			for (int i = 0; i < 20; ++i)
			{
				assert(ga[i] == ga2[i]);
			}
		}

		TEST_METHOD(CopyConstrNoSafeMode)
		{
			GAInt ga;
			ga.Init(10, false);
			for (int i = 0; i < 20; ++i)
			{
				ga.Add(i);
			}

			GAInt ga2(ga);
			for (int i = 0; i < 20; ++i)
			{
				assert(ga[i] == ga2[i]);
			}
		}

		TEST_METHOD(DeleteAll)
		{
			int value = 99;
			GAIntPtr s;
			s.Init(1, false);
			for (int i = 0; i < 10; ++i)
			{
				s.Add(new int(i));
			}

			for (int i = 0; i < 10; ++i)
			{
				assert((*s[i]) == i);
			}

			s.DeleteAll();

			// Test memory leaks
			GAHugePtr h;
			h.Init(1, false);

			for (int j = 0; j < 100; ++j)
			{
				for (int i = 0; i < 100; ++i)
				{
					h.Add(new Huge());
				}
				h.DeleteAll();
			}
		}

		TEST_METHOD(MemoryLeakWhenGrowing)
		{
			for (int j = 0; j < 50; ++j)
			{
				GAHuge h;
				h.Init(1, false);

				for (int i = 0; i < 100; ++i)
				{
					h.Add(Huge());
				}
			}
		}

		TEST_METHOD(GetLast)
		{
			GAInt ga;
			ga.Init(1, false);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}
			assert(ga.GetLast() == 9);
			ga.RemoveCyclic(9);
			assert(ga.GetLast() == 8);
			ga.RemoveCyclicAtIndex(8);
			assert(ga.GetLast() == 7);
			ga.Add(999);
			assert(ga.GetLast() == 999);
			ga.RemoveAll();
			ga.Add(42);
			assert(ga.GetLast() == 42);
		}

		TEST_METHOD(Find)
		{
			GAInt ga;
			ga.Init(1, false);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}
			assert(ga.Find(123) == GAInt::FoundNone);
			ga.RemoveCyclic(9);
			assert(ga.Find(9) == GAInt::FoundNone);
			ga.RemoveCyclicAtIndex(8);
			assert(ga.Find(8) == GAInt::FoundNone);
			ga.Add(999);
			assert(ga.Find(999) == ga.Size() - 1);
			assert(ga.Find(0) == 0);
			ga.RemoveAll();
			assert(ga.Find(999) == GAInt::FoundNone);
		}

		TEST_METHOD(Size)
		{
			GAInt ga;
			ga.Init(1, false);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}
			assert(ga.Size() == 10);
			ga.RemoveCyclic(9);
			assert(ga.Size() == 9);
			ga.RemoveCyclicAtIndex(8);
			assert(ga.Size() == 8);
			ga.Add(999);
			assert(ga.Size() == 9);
			ga.RemoveAll();
			assert(ga.Size() == 0);
			for (int i = 0; i < 10; ++i)
			{
				ga.Add(i);
			}
			assert(ga.Size() == 10);
			ga.ReInit(123, true);
			assert(ga.Size() == 0);

		}


		// Evil tests

		TEST_METHOD(_SHOULDCRASH_OutOfBounds)
		{
			GAInt s;
			s.Init(1, false);
			s[99] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_NegativeOutOfBounds)
		{
			GAInt s;
			s.Init(1, false);
			s[-99] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_RemoveAllOutOfBounds)
		{
			GAInt s;
			s.Init(1, false);
			s.Add(1);
			s.RemoveAll();
			s[0] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_DeleteOutOfBounds)
		{
			GAInt s;
			s.Init(1, false);
			s.RemoveCyclicAtIndex(10);
		}

		TEST_METHOD(_SHOULDCRASH_InsertOutOfBounds)
		{
			int value = 99;
			GAInt s;
			s.Init(1, false);
			s.Insert(99, value);
		}

		TEST_METHOD(_SHOULDFAIL_CopyConstrNoSafeMode)
		{
			GAStr ga;
			std::string txt = "adadjaksjdaksdjkasdksajdksajdkajasd";
			ga.Init(10, false);
			for (int i = 0; i < 20; ++i)
			{
				ga.Add(txt + char(i));
			}

			GAStr ga2(ga);
			ga2.Init(1, false);

			for (int i = 0; i < 20; ++i)
			{
				assert(ga[i] == ga2[i]);
			}
		}
	};
}