#pragma once

#include "GrowingArray.h"

namespace SB
{

	template<typename T>
	class Stack
	{
	public:
		Stack(unsigned short aReserveSize = 16)
		{
			myStack.Reserve(aReserveSize);
		}

		T Pop()
		{
			assert(myStack.Size() > 0 && "STACK IS EMPTY");
			T value = myStack.GetLast();
			myStack.RemoveAtIndex(myStack.Size() - 1);
			return value;
		}
		
		T & Top()
		{
			assert(myStack.Size() > 0 && "STACK IS EMPTY");
			return myStack.GetLast();
		}

		const T & Top() const
		{
			assert(myStack.Size() > 0 && "STACK IS EMPTY");
			return myStack.GetLast();
		}

		unsigned short Size() const
		{
			return myStack.Size();
		}
	
		void Push(const T& aValue)
		{
			myStack.Add(aValue);
		}

		void PopAll()
		{
			myStack.RemoveAll();
		}

	private:
		GrowingArray <T, unsigned short> myStack;
	};

}
