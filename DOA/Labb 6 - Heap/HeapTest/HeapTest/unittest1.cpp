#include "CppUnitTest.h"
#include "heap.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace CommonUtilities;

bool compare (int i,int j) 
{ 
	return (i>j); 
}

namespace HeapTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		
		TEST_METHOD(OneValue)
		{
			Heap<int> h;
			h.Enqueue(10);
			assert(h.Dequeue() == 10);
		}

		TEST_METHOD(TenValues)
		{
			Heap<int> h;
			for (int i = 0; i < 10; ++i)
				h.Enqueue(i);
			for (int j = 9; j >= 0 ; j--)
			{
				int max = h.Dequeue();
				assert(j == max);
			}
		}
		TEST_METHOD(FloydsAlgorithm)
		{
			for (int tests = 0; tests < 100; ++tests)
			{
				srand(tests);
				std::vector<int> v;
				GrowingArray<int> g;
				g.Init(50);
				for (int numbers = 0; numbers < rand()%100; ++numbers)
				{
					v.push_back(rand()%10000);
					g.Add(v.back());
				}			

				std::sort(v.begin(), v.end(), compare);

				Heap<int> h(g);
				for (unsigned int i = 0; i < v.size(); ++i)
				{
					int maxValue = h.Dequeue();
					int otherValue = v[i];
					Assert::IsTrue(v[i] == maxValue);
				}
			}			
		}

		TEST_METHOD(PopEmptyShouldCrash)
		{
			Heap<int> h;
			h.Dequeue();
		}

		TEST_METHOD(RandomAddSingle)
		{
			for (int tests = 0; tests < 100; ++tests)
			{
				std::vector<int> numbers;
				Heap<int> heap;
				srand(tests);
				for (int nrs = 0; nrs < rand() % 300; ++nrs)
				{
					numbers.push_back(rand() % 10000);
					heap.Enqueue(numbers.back());
				}

				std::sort(numbers.begin(), numbers.end(), compare);
				for (unsigned int i = 0; i < numbers.size(); ++i)
				{
					int max = heap.Dequeue();
					assert(numbers[i] == max);
				}
			}
		}



	};
}