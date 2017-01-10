#include <assert.h>
namespace SB
{

	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::Remove(TYPE &aData)
	{
		myArray.RemoveCyclic(aData);

		myLastNonLeaf = static_cast<unsigned int> ((myArray.Size() - 2) / 2);
		myLastIndex = myArray.Size() - 1;
		FloydSort();
	}
	template<typename TYPE, typename COMPARER>
	SB::Heap<TYPE, COMPARER>::Heap() :myArray(10)
	{
		myLastIndex = 0;
		myLastNonLeaf = 0;
	}
	template<typename TYPE, typename COMPARER>
	SB::Heap<TYPE, COMPARER>::Heap(unsigned short aSize) :myArray(aSize)
	{
		myLastIndex =	static_cast<unsigned int>(-1);
		myLastNonLeaf = static_cast<unsigned int>(-1);
	}
	

	template<typename TYPE, typename COMPARER>
	TYPE &SB::Heap<TYPE, COMPARER>::GetTop()
	{
		return myArray[0];
	}
	template<typename TYPE, typename COMPARER>
	SB::Heap<TYPE, COMPARER>::Heap(SB::GrowingArray<TYPE, unsigned int> aArray)
	{
		myArray = aArray;

		myLastNonLeaf = static_cast<unsigned int> ((aArray.Size() - 2) / 2);
		myLastIndex = myArray.Size() - 1;
		FloydSort();

		
	}

	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::FloydSort()
	{
		for (unsigned int i = myLastNonLeaf+1; i > 0; --i)
		{
			unsigned int pos = i-1;
			RecursiveSort(pos);
		}
	}

	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::RecursiveSort(unsigned int aStartIndex)
	{
		unsigned int pos = aStartIndex;
		if (aStartIndex > myLastNonLeaf)
		{
			return;
		}
		TYPE parent = myArray[pos];
		TYPE child1 = myArray[pos * 2 + 1];

		if (Compare(parent, child1) == false)
		{
			myArray[pos] = child1;
			myArray[pos * 2 + 1] = parent;
			RecursiveSort(pos * 2 + 1);

		}
		parent = myArray[pos];

		if ((pos * 2) + 2 >= myLastIndex)
		{
			return;
		}
		TYPE child2 = myArray[pos * 2 + 2];
		if (Compare(parent, child2) == false)
		{
			myArray[pos] = child2;
			myArray[pos * 2 + 2] = parent;
			RecursiveSort(pos * 2 + 2);

		}
	}

	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::Enqueue(TYPE aData)
	{
		myArray.Add(aData);
		myLastIndex = myArray.Size()-1;
		myLastNonLeaf = (myLastIndex - 1) / 2;

		unsigned int i = myLastIndex;
		while (i > 0 && Compare(myArray[i / 2], aData) == false)
		{
			myArray[i] = myArray[i / 2];
			i /= 2;
		}
		myArray[i] = aData;
	}

	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::SiftDown(unsigned int nodeIndex)
	{
		unsigned int leftChildIndex, rightChildIndex, minIndex;
		TYPE tmp;
		leftChildIndex = nodeIndex * 2 + 1;
		rightChildIndex = nodeIndex * 2 + 2;
		if (rightChildIndex >= myArray.Size()) 
		{
			if (leftChildIndex >= myArray.Size())
				return;
			else
				minIndex = leftChildIndex;
		}
		else {
			if (Compare(myArray[leftChildIndex], myArray[rightChildIndex]))
				minIndex = leftChildIndex;
			else
				minIndex = rightChildIndex;
		}
		if (Compare(myArray[nodeIndex], myArray[minIndex]) == false) {
			tmp = myArray[minIndex];
			myArray[minIndex] = myArray[nodeIndex];
			myArray[nodeIndex] = tmp;
			SiftDown(minIndex);
		}
	}

	template<typename TYPE, typename COMPARER>
	TYPE SB::Heap<TYPE, COMPARER>::Dequeue()
	{
		assert(IsEmpty() == false && "HEAP IS EMPTY!");
		TYPE returnValue = myArray[0];
		myArray[0] = myArray[myArray.Size() - 1];
		myArray.RemoveCyclicAtIndex(myArray.Size() - 1);
		if (IsEmpty() == false)
		{
			SiftDown(0);
		}
		return returnValue;
	}

	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::Print()
	{
		std::cout << "PRINTING" << std::endl;
		for (unsigned short i = 0; i < myArray.Size(); ++i)
		{
			std::cout << myArray[i] << std::endl;
		}
		std::cout << "---------------------------------" << std::endl;
	}
	template<typename TYPE, typename COMPARER>
	void SB::Heap<TYPE, COMPARER>::RemoveAll()
	{
		myArray.RemoveAll();
	}
};