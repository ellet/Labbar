#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "stack.h"

namespace TestsForStack
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_if_constructor_works)
		{
			CommonUtilities::Stack<float> stack;
		}

		TEST_METHOD(Test_size)
		{
			CommonUtilities::Stack<float> stack;
			Assert::AreEqual(stack.Size(), 0);
		}

		TEST_METHOD(Test_Push_and_Size)
		{
			CommonUtilities::Stack<float> stack;
			float meh = 2.f;
			stack.Push(meh);
			Assert::AreEqual(stack.Size(), 1);
		}

		TEST_METHOD(Test_Push_and_Size_MAAAANYYY)
		{
			CommonUtilities::Stack<float> stack;
			float meh = 3.f;
			float meh1 = 2.f;
			float meh2 = 3.f;
			float meh3 = 2.f;
			float meh4 = 5.f;
			stack.Push(meh);
			stack.Push(meh1);
			stack.Push(meh2);
			stack.Push(meh3);
			stack.Push(meh4);
			Assert::AreEqual(stack.Size(), 5);
		}

		TEST_METHOD(Test_Push_and_Top)
		{
			CommonUtilities::Stack<float> stack;
			float meh = 3.f;
			float meh1 = 2.f;
			float meh2 = 3.f;
			float meh3 = 2.f;
			float meh4 = 5.f;
			stack.Push(meh);
			stack.Push(meh1);
			stack.Push(meh2);
			stack.Push(meh3);
			stack.Push(meh4);
			Assert::AreEqual(stack.Top(), 5.f);
		}

		/*
		TEST_METHOD(Test_Push_and_Top_should_Assert)
		{
			CommonUtilities::Stack<float> stack;
			stack.Top();
		}
		*/

		TEST_METHOD(Test_Push_and_Pop_and_Top)
		{
			CommonUtilities::Stack<float> stack;
			float meh = 3.f;
			float meh1 = 1.f;
			float meh2 = 3.f;
			float meh3 = 2.f;
			float meh4 = 5.f;
			stack.Push(meh);
			stack.Push(meh1);
			stack.Push(meh2);
			stack.Push(meh3);
			stack.Push(meh4);
			stack.Pop();
			Assert::AreEqual(stack.Top(), 2.f);
			stack.Pop();
			Assert::AreEqual(stack.Top(), 3.f);

			Assert::AreEqual(stack.Size(), 3);
		}

		TEST_METHOD(Test_Push_and_Pop_and_Top_return_value)
		{
			CommonUtilities::Stack<float> stack;
			float meh = 3.f;
			float meh1 = 1.f;
			float meh2 = 3.f;
			float meh3 = 2.f;
			float meh4 = 5.f;
			stack.Push(meh);
			stack.Push(meh1);
			stack.Push(meh2);
			stack.Push(meh3);
			stack.Push(meh4);
			stack.Pop();
			Assert::AreEqual(stack.Top(), 2.f);
			stack.Pop();
			Assert::AreEqual(stack.Top(), 3.f);
			Assert::AreEqual(stack.Size(), 3);
			Assert::AreEqual(stack.Pop(), 3.f);
		}

		TEST_METHOD(Test_Push_and_Pop_and_Top_return_value_pointers)
		{
			CommonUtilities::Stack<float*> stack;
			float* meh = new float(3.f);
			float* meh1 =  new float(1.f);
			float* meh2 =  new float(3.f);
			float* meh3 =  new float(2.f);
			float* meh4 =  new float(5.f);
			stack.Push(meh);
			stack.Push(meh1);
			stack.Push(meh2);
			stack.Push(meh3);
			stack.Push(meh4);
			stack.Pop();
			Assert::AreEqual(*stack.Top(), 2.f);
			stack.Pop();
			Assert::AreEqual(*stack.Top(), 3.f);
			Assert::AreEqual(stack.Size(), 3);
			Assert::AreEqual(*stack.Pop(), 3.f);
		}

		TEST_METHOD(Test_Push_and_Pop_and_Top_return_value_more)
		{
			CommonUtilities::Stack<float> stack;
			stack.Push(6.0);
			stack.Push(1.0);
			stack.Push(3.0);
			stack.Push(2.0);
			stack.Push(5.0);
			stack.Pop();
			Assert::AreEqual(stack.Top(), 2.f);
			stack.Pop();
			Assert::AreEqual(stack.Top(), 3.f);
			Assert::AreEqual(stack.Size(), 3);
			Assert::AreEqual(stack.Pop(), 3.f);
		}
	};
}