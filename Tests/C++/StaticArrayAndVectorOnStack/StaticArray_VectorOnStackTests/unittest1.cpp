#include "stdafx.h"
#include "CppUnitTest.h"
#include "StaticArray.h"
#include "VectorOnStack.h"
#include <assert.h>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

namespace StaticArray_VectorOnStackTests
{		
	template class StaticArray<int*, 10>;
	template class VectorOnStack<int*, 10>;

//#define Size GetSize

	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(StaticArraySubscript)
		{
			StaticArray<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s[i] = i;
			}

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == i);
			}			
		}

		TEST_METHOD(StaticArrayInsert)
		{
			int value = 99;
			StaticArray<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s[i] = i;
			}

			s.Insert(0, value);
			assert(s[0] == 99);
			assert(s[9] == 8);
		}

		TEST_METHOD(StaticArrayDeleteAll)
		{
			int value = 99;
			StaticArray<int*, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s[i] = new int(i);
			}

			for (int i = 0; i < 10; ++i)
			{
				assert((*s[i]) == i);
			}

			s.DeleteAll();

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == nullptr);
			}
		}

		TEST_METHOD(StaticArrayCopyCtor)
		{
			StaticArray<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s[i] = i;
			}

			StaticArray<int, 10> s2(s);

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == s2[i]);
			}
		}

		TEST_METHOD(StaticArrayEqualOperator)
		{
			StaticArray<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s[i] = i;
			}

			StaticArray<int, 10> s2;
			s2 = s;

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == s2[i]);
			}
		}

		TEST_METHOD(VectorSubscript)
		{
			VectorOnStack<int, 10> v;
			for (int i = 0; i < 10; ++i)
			{
				v.Add(i);
			}

			for (int i = 0; i < 10; ++i)
			{
				assert(v[i] == i);
			}
		}

		TEST_METHOD(VectorSize)
		{
			VectorOnStack<int, 10> v;
			assert(v.Size() == 0);
			for (int i = 0; i < 10; ++i)
				v.Add(i);
			assert(v.Size() == 10);
			v.RemoveCyclicAtIndex(2);
			assert(v.Size() == 9);
			v.Clear();
			assert(v.Size() == 0);
		}

		TEST_METHOD(VectorInsert)
		{
			VectorOnStack<int, 20> v;
			int value = 99;
			for (int i = 0; i < 10; ++i)
			{
				v.Add(i);
			}

			v.Insert(0, value);
			assert(v[0] == 99);
			assert(v[9] == 8);
			assert(v[10] == 9);
		}

		TEST_METHOD(VectorCopyCtorSafeMode)
		{
			std::string txt = "apaapaapaapaapaapaapaapaapaapaapaapaapaapaapaapaapa";
			VectorOnStack<std::string, 10> str;
			VectorOnStack<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
				str.Add(txt);
			}

			VectorOnStack<int, 10> s2(s);
			VectorOnStack<int, 10> str2(s);

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == s2[i]);
			}
		} // if crash at end of scope, string not correctly copied

		TEST_METHOD(VectorEqualOperatorSafeMode)
		{
			std::string txt = "apaapaapaapaapaapaapaapaapaapaapaapaapaapaapaapaapa";
			VectorOnStack<std::string, 10> str;
			VectorOnStack<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
				str.Add(txt);
			}

			VectorOnStack<int, 10> s2;
			VectorOnStack<std::string, 10> str2;
			str2 = str;
			s2 = s;

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == s2[i]);
			}
		} // if crash at end of scope, string not correctly copied

		TEST_METHOD(VectorCopyCtorNoSafeMode)
		{
			VectorOnStack<int, 10, short, false> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
			}

			VectorOnStack<int, 10, short, false> s2(s);

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == s2[i]);
			}
		}

		TEST_METHOD(VectorEqualOperatorNoSafeMode)
		{
			VectorOnStack<int, 10, short, false> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
			}

			VectorOnStack<int, 10, short, false> s2;
			s2 = s;

			for (int i = 0; i < 10; ++i)
			{
				assert(s[i] == s2[i]);
			}
		}

		TEST_METHOD(VectorDeleteCyclicIndex)
		{
			VectorOnStack<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
			}

			s.RemoveCyclicAtIndex(2);
			assert(s[2] == 9);
			assert(s.Size() == 9);

			s.RemoveCyclicAtIndex(0);
			assert(s[0] == 8);

			s.RemoveCyclicAtIndex(7);
			assert(s[6] == 6);

			assert(s.Size() == 7);
		}

		TEST_METHOD(VectorDeleteCyclicValue)
		{
			VectorOnStack<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
			}

			s.RemoveCyclic(2);
			assert(s[2] == 9);
			assert(s.Size() == 9);

			s.RemoveCyclic(0);
			assert(s[0] == 8);

			s.RemoveCyclic(7);
			assert(s[6] == 6);

			assert(s.Size() == 7);			
		}

		TEST_METHOD(VectorClear)
		{
			VectorOnStack<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
			}

			s.Clear();
			assert(s.Size() == 0);
		}

		TEST_METHOD(VectorClear2)
		{
			VectorOnStack<int, 10> s;
			for (int i = 0; i < 10; ++i)
			{
				s.Add(i);
			}
		}

		TEST_METHOD(_SHOULDCRASH_StaticArrayOutOfBounds)
		{
			StaticArray<int, 10> s;
			s[99] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_StaticArrayNegativeOutOfBounds)
		{
			StaticArray<int, 10> s;
			s[-99] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_VectorOutOfBounds)
		{
			VectorOnStack<int, 10> s;
			s[99] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_VectorNegativeOutOfBounds)
		{
			VectorOnStack<int, 10> s;
			s[-99] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_VectorClearOutOfBounds)
		{
			VectorOnStack<int, 10> s;
			s.Add(1);
			s.Clear();
			s[0] = 10;
		}

		TEST_METHOD(_SHOULDCRASH_VectorDeleteOutOfBounds)
		{
			VectorOnStack<int, 10> s;
			s.RemoveCyclicAtIndex(10);			
		}

		TEST_METHOD(_SHOULDCRASH_VectorInsertOutOfBounds)
		{
			int value = 99;
			VectorOnStack<int, 10> s;
			s.Insert(99, value);
		}
	};
}