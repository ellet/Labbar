#pragma once
#include "../GrowingArray/GrowingArray.h"
#include "../DLDebug/DL_Debug.h"
#include "Greater.h"

namespace CommonUtilities
{
	template <typename T, typename CountType = unsigned short,typename TComparer = Greater<T>>
	class Heap
	{
	public:

		Heap();
		Heap(const CommonUtilities::GrowingArray<T, CountType> & aGrowingArray);
		void Enqueue(T someData);
		T Dequeue();
		bool IsEmpty();

		bool IsHeap();
		bool IsHeap(const CommonUtilities::GrowingArray<T, CountType> & aGrowingArray);

		const T & Peek();
		void ClearAndSort(const CommonUtilities::GrowingArray<T, CountType> & aGrowingArray);

		void DeleteAll();

		void HeapSort(CommonUtilities::GrowingArray<T, CountType> & aArrayToSortInto, CountType aIndex);
		

	private:
		GrowingArray<T, CountType> myData;
		TComparer myComparer;

		void Climb(CountType anIndex);
		void Drop(CountType anIndex);
		bool TraverseCheckIsHeap(const CommonUtilities::GrowingArray<T, CountType > & aGrowingArray, CountType anIndex);
	};
	

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	CommonUtilities::Heap<T, CountType, TComparer>::Heap(const CommonUtilities::GrowingArray<T, CountType> & aGrowingArray)
	{
		myData.Init(1);
		ClearAndSort(aGrowingArray);
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	CommonUtilities::Heap<T, CountType, TComparer>::Heap()
	{
		myData.Init(1);
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, CountType, TComparer>::Enqueue(T someData)
	{
		myData.Add(someData);
		Climb(myData.Size() - 1);
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	T CommonUtilities::Heap<T, CountType, TComparer>::Dequeue()
	{
		DL_ASSERT(myData.Size() > 0, "Heap error - Trying to dequeue an empty heap!");
		T temp = myData[0];
		myData.RemoveCyclicAtIndex(0);
		if (myData.Size() > 1)
		{
			Drop(0);
		}
		return temp;
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, CountType, TComparer>::IsEmpty()
	{
		return (myData.Size() <= 0);
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, CountType, TComparer>::IsHeap()
	{
		return IsHeap(myData);
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, CountType, TComparer>::IsHeap(const CommonUtilities::GrowingArray<T, CountType > & aGrowingArray)
	{
		if (aGrowingArray.Size() > 0)
		{
			return TraverseCheckIsHeap(aGrowingArray, 0);
		}
		else
		{
			return true;
		}
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	const T & CommonUtilities::Heap<T, CountType, TComparer>::Peek()
	{
		DL_ASSERT(myData.Size() > 0, "Heap error - Trying to peek on an empty heap!");
		return myData[0];
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, CountType, TComparer>::ClearAndSort(const CommonUtilities::GrowingArray<T, CountType > & aGrowingArray)
	{
		myData.RemoveAll();
		myData = aGrowingArray;

		for (CountType i = static_cast<CountType>(static_cast<float>(aGrowingArray.Size())/2.f - 0.5f); i < aGrowingArray.Size(); --i)
		{
			Drop(i);
		}
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, CountType, TComparer>::DeleteAll()
	{
		myData.DeleteAll();
	}

	template <typename T, typename CountType /*= unsigned short*/, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, CountType, TComparer>::HeapSort(CommonUtilities::GrowingArray<T, CountType> & aArrayToSortInto, CountType aIndex)
	{
		aArrayToSortInto[aIndex] = Dequeue();
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, CountType, TComparer>::Climb(CountType  anIndex)
	{
		if (anIndex > 0)
		{
			CountType parentIndex = (anIndex - 1) / 2;

			if (myComparer(myData[anIndex], myData[parentIndex]) == true)
			{
				std::swap(myData[anIndex], myData[parentIndex]);
				Climb(parentIndex);
			}
		}
	}

	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	void CommonUtilities::Heap<T, CountType, TComparer>::Drop(CountType anIndex)
	{
		CountType firstChildIndex = anIndex * 2 + 1;
		CountType secondChildIndex = anIndex * 2 + 2;
		if (firstChildIndex < myData.Size())
		{
			CountType greatestChild = firstChildIndex;
			if (secondChildIndex < myData.Size() && myComparer(myData[secondChildIndex], myData[firstChildIndex]) == true)
			{
				greatestChild = secondChildIndex;
			}

			if (myComparer(myData[greatestChild], myData[anIndex]) == true)
			{
				std::swap(myData[greatestChild], myData[anIndex]);
				Drop(greatestChild);
			}
		}
	}


	template <typename T, typename CountType, typename TComparer /*= Greater<T>*/>
	bool CommonUtilities::Heap<T, CountType, TComparer>::TraverseCheckIsHeap(const CommonUtilities::GrowingArray<T, CountType > & aGrowingArray, CountType anIndex)
	{
		CountType firstChildIndex = anIndex * 2 + 1;
		CountType secondChildIndex = anIndex * 2 + 2;
		if (firstChildIndex < aGrowingArray.Size())
		{
			if (secondChildIndex < myData.Size() == true)
			{
				if (myComparer(aGrowingArray[secondChildIndex], aGrowingArray[anIndex]) == true)
				{
					return false;
				}
				TraverseCheckIsHeap(aGrowingArray, secondChildIndex);
			}

			if (myComparer(aGrowingArray[firstChildIndex], aGrowingArray[anIndex]) == true)
			{
				return false;
			}
			TraverseCheckIsHeap(aGrowingArray, firstChildIndex);
		}
		return true;
	}
}