#include "stdafx.h"
#include "CppUnitTest.h"
#include <Heap/Heap.h>
#include <DLDebug/DL_Debug.h>
#include <Vectors/vector2.h>
#include <Heap/Lesser.h>
#include <Heap/PointerGreater.h>
#include <Heap/PointerLesser.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TESTDAHEAPS
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_CLASS_INITIALIZE(derp)
		{
			DL_Debug::Debug::Create();
		}


		TEST_METHOD_INITIALIZE(methodName)
		{
			
		}

		
		TEST_METHOD(NormalConstructor)
		{
			CU::Heap<int> heap;
		}

		TEST_METHOD(Test_IsEmpty)
		{
			CU::Heap<int> heap;

			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_EnqueueSimple)
		{
			CU::Heap<int> heap;
			int derp = 5;
			heap.Enqueue(derp);
			Assert::IsFalse(heap.IsEmpty());
		}

		TEST_METHOD(Test_Dequeue)
		{
			CU::Heap<int> heap;
			int derp = 5;
			heap.Enqueue(derp);
			Assert::AreEqual(heap.Dequeue(), 5);
			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_peek)
		{
			CU::Heap<int> heap;
			heap.Enqueue(5);
			Assert::AreEqual(heap.Peek(), 5);
		}

		TEST_METHOD(Test_COMPAREERUR_Greater)
		{
			CommonUtilities::Greater<int> greaterComparer;
			Assert::IsTrue(greaterComparer(5, 3));
			Assert::IsFalse(greaterComparer(3, 3));
			Assert::IsFalse(greaterComparer(2, 3));
		}

		TEST_METHOD(Test_COMPAREERUR_Lesser)
		{
			CommonUtilities::Lesser<int> lesserComparer;
			Assert::IsTrue(lesserComparer(2, 3));
			Assert::IsFalse(lesserComparer(3, 3));
			Assert::IsFalse(lesserComparer(4, 3));
		}

		TEST_METHOD(Test_Climb)
		{
			CU::Heap<int> heap;
			heap.Enqueue(5);
			Assert::AreEqual(heap.Peek(), 5);
			heap.Enqueue(6);
			Assert::AreEqual(heap.Peek(), 6);
			heap.Enqueue(3);
			Assert::AreEqual(heap.Peek(), 6);
			heap.Enqueue(8);
			Assert::AreEqual(heap.Peek(), 8);

		}

		TEST_METHOD(Test_LesserSomething)
		{
			CU::Heap<int, CommonUtilities::Lesser<int>> heap;
			heap.Enqueue(5);
			Assert::AreEqual(heap.Peek(), 5);
			heap.Enqueue(6);
			Assert::AreEqual(heap.Peek(), 5);
			heap.Enqueue(3);
			Assert::AreEqual(heap.Peek(), 3);
			heap.Enqueue(8);
			Assert::AreEqual(heap.Peek(), 3);

		}

		TEST_METHOD(Test_DropToThaFloor)
		{
			CU::Heap<int, CommonUtilities::Lesser<int>> heap;
			heap.Enqueue(5);
			Assert::AreEqual(heap.Peek(), 5);
			heap.Enqueue(6);
			Assert::AreEqual(heap.Peek(), 5);
			heap.Enqueue(3);
			Assert::AreEqual(heap.Peek(), 3);
			heap.Enqueue(8);
			Assert::AreEqual(heap.Peek(), 3);

			heap.Dequeue();
			Assert::AreEqual(heap.Peek(), 5);
			heap.Dequeue();
			Assert::AreEqual(heap.Peek(), 6);

		}

		TEST_METHOD(Test_DropSmall)
		{
			CU::Heap<int, CommonUtilities::Lesser<int>> heap;
			heap.Enqueue(6);
			heap.Enqueue(5);
			heap.Enqueue(8);
			heap.Enqueue(2);

			Assert::AreEqual(heap.Dequeue(), 2);
			Assert::AreEqual(heap.Dequeue(), 5);
			Assert::AreEqual(heap.Dequeue(), 6);
			Assert::AreEqual(heap.Dequeue(), 8);
			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_IsHeap)
		{
			CU::Heap<int> heap;
			heap.Enqueue(5);

			Assert::IsTrue(heap.IsHeap());

		}

		TEST_METHOD(Test_IsHeapWithLotsies)
		{
			CU::Heap<int> heap;
			heap.Enqueue(5);
			heap.Enqueue(8);
			heap.Enqueue(2);
			heap.Enqueue(1);
			heap.Enqueue(10);
			heap.Enqueue(7);

			Assert::IsTrue(heap.IsHeap());

		}

		TEST_METHOD(Test_IsHeapWithLotsiesOnAnotherArraisies)
		{
			CU::Heap<int> heap;
			CU::GrowingArray<int> derp;
			derp.Init(6);
			derp.Add(1);
			derp.Add(7);
			derp.Add(3);
			derp.Add(2);
			derp.Add(9);
			derp.Add(12);

			Assert::IsFalse(heap.IsHeap(derp));
		}

		TEST_METHOD(TestCustomConstuctor)
		{
			CU::GrowingArray<int> derp;
			derp.Init(1);
			CU::Heap<int> heap(derp);
			Assert::IsTrue(heap.IsHeap());

		}

		TEST_METHOD(Test_GAStuff)
		{
			CU::GrowingArray<int> derp;
			derp.Init(1);
			CU::Heap<int> heap;
			for (int i = 0; i < 10; ++i)
			{
				derp.Add(i);
			}

			heap.ClearAndSort(derp);

			for (int i = 9; i >= 0; --i)
			{
				Assert::AreEqual(heap.Dequeue(), i);
			}


		}

		TEST_METHOD(Test_IsHeapWithLotsiesDoubles)
		{
			CU::Heap<double> heap;
			heap.Enqueue(5.);
			heap.Enqueue(8.);
			heap.Enqueue(2.);
			heap.Enqueue(1.);
			heap.Enqueue(10.);
			heap.Enqueue(7.);

			Assert::IsTrue(heap.IsHeap());
			Assert::AreEqual(heap.Dequeue(), 10.);
			Assert::AreEqual(heap.Dequeue(), 8.);
			Assert::AreEqual(heap.Dequeue(), 7.);
			Assert::AreEqual(heap.Dequeue(), 5.);
			Assert::AreEqual(heap.Dequeue(), 2.);
			Assert::AreEqual(heap.Dequeue(), 1.);
			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_IsHeapWithLotsiesDoublesWithIntLiterals)
		{
			CU::Heap<double> heap;
			heap.Enqueue(5);
			heap.Enqueue(8);
			heap.Enqueue(2);
			heap.Enqueue(1);
			heap.Enqueue(10);
			heap.Enqueue(7);

			Assert::IsTrue(heap.IsHeap());
		}

		TEST_METHOD(Test_IsHeapWithLotsiesFloatsWithIntLiterals)
		{
			CU::Heap<float> heap;
			heap.Enqueue(5);
			heap.Enqueue(8);
			heap.Enqueue(2);
			heap.Enqueue(1);
			heap.Enqueue(10);
			heap.Enqueue(7);

			Assert::IsTrue(heap.IsHeap());
		}

		TEST_METHOD(Test_IsHeapWithLotsiesFloats)
		{
			CU::Heap<float> heap;
			heap.Enqueue(5.f);
			heap.Enqueue(8.f);
			heap.Enqueue(2.f);
			heap.Enqueue(1.f);
			heap.Enqueue(10.f);
			heap.Enqueue(7.f);

			Assert::IsTrue(heap.IsHeap());
			Assert::AreEqual(heap.Dequeue(), 10.f);
			Assert::AreEqual(heap.Dequeue(), 8.f);
			Assert::AreEqual(heap.Dequeue(), 7.f);
			Assert::AreEqual(heap.Dequeue(), 5.f);
			Assert::AreEqual(heap.Dequeue(), 2.f);
			Assert::AreEqual(heap.Dequeue(), 1.f);
			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_IsHeapWithLotsiesFloatsPointers)
		{
			CU::Heap<float*, CommonUtilities::PointerGreater<float *>> heap;
			heap.Enqueue(new float (5.f));
			heap.Enqueue(new float (8.f));
			heap.Enqueue(new float (2.f));
			heap.Enqueue(new float (1.f));
			heap.Enqueue(new float (10.f));
			heap.Enqueue(new float (7.f));

			Assert::IsTrue(heap.IsHeap());
			Assert::AreEqual(*heap.Dequeue(), 10.f);
			Assert::AreEqual(*heap.Dequeue(), 8.f);
			Assert::AreEqual(*heap.Dequeue(), 7.f);
			Assert::AreEqual(*heap.Dequeue(), 5.f);
			Assert::AreEqual(*heap.Dequeue(), 2.f);
			Assert::AreEqual(*heap.Dequeue(), 1.f);
			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_IsHeapWithLotsiesLesserFloatsPointers)
		{
			CU::Heap<float*, CommonUtilities::PointerLesser<float *>> heap;
			heap.Enqueue(new float(5.f));
			heap.Enqueue(new float(8.f));
			heap.Enqueue(new float(2.f));
			heap.Enqueue(new float(1.f));
			heap.Enqueue(new float(10.f));
			heap.Enqueue(new float(7.f));

			Assert::IsTrue(heap.IsHeap());
			Assert::AreEqual(*heap.Dequeue(), 1.f);
			Assert::AreEqual(*heap.Dequeue(), 2.f);
			Assert::AreEqual(*heap.Dequeue(), 5.f);
			Assert::AreEqual(*heap.Dequeue(), 7.f);
			Assert::AreEqual(*heap.Dequeue(), 8.f);
			Assert::AreEqual(*heap.Dequeue(), 10.f);
			Assert::IsTrue(heap.IsEmpty());
		}

		TEST_METHOD(Test_DeletePointers)
		{
			CU::Heap<float*, CommonUtilities::PointerLesser<float *>> heap;
			heap.Enqueue(new float(5.f));
			heap.Enqueue(new float(8.f));
			heap.Enqueue(new float(2.f));
			heap.Enqueue(new float(1.f));
			heap.Enqueue(new float(10.f));
			heap.Enqueue(new float(7.f));

			heap.DeleteAll();

			Assert::IsTrue(heap.IsEmpty());
		}
	};
}