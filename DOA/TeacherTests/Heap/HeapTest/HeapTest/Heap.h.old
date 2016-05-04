#ifndef HEAP_H
#define HEAP_H

#include "GrowingArray.h"
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>

#define START_SIZE 32

template<typename T>
class Heap
{
public:
	Heap(CommonUtilities::GrowingArray<T> aGrowingArray);
	Heap();
	inline void Enqueue(T aData);
	inline T Dequeue();

private:
	inline bool HasLeftChild(int aPos);
	inline bool HasRightChild(int aPos);
	inline double Log2(double aNum);
	CommonUtilities::GrowingArray<T> myHeap;


};

template<typename T>
Heap<T>::Heap(CommonUtilities::GrowingArray<T> aGrowingArray)
{
	myHeap.Init(START_SIZE);
	for(unsigned int i = 0; i < aGrowingArray.Size(); ++i)
	{
		Enqueue(aGrowingArray[i]);
	}
}

template<typename T>
Heap<T>::Heap()
{
	myHeap.Init(START_SIZE);
}


template<typename T>
inline void Heap<T>::Enqueue(T aData)
{
	myHeap.Add(aData);
	int pos =  myHeap.Size()-1;
	while((pos>0) && (myHeap[(pos-1)/2] < myHeap[pos]))
	{
		//swap
		T temp = myHeap[(pos-1)/2];
		myHeap[(pos-1)/2] = myHeap[pos];
		myHeap[pos] = temp;

		pos = (pos-1)/2;
	}

}

template<typename T>
inline T Heap<T>::Dequeue()
{
	assert(myHeap.Size() > 0 && "Dequeue failed. The Heap is empty!");
	T returnVal = myHeap[0];
	myHeap.RemoveCyclicAtIndex(0);
	int pos=0;

	while((pos < (myHeap.Size() - 1)/2) && (HasLeftChild(pos) || HasLeftChild(pos)))
	{

		if(myHeap[pos*2+1] > myHeap[pos*2+2]) 
		{
			T temp = myHeap[pos];
			myHeap[pos] = myHeap[pos*2+1];
			myHeap[pos*2+1] = temp;

			pos=pos*2+1;
		}
		else
		{
			T temp = myHeap[pos];
			myHeap[pos] = myHeap[pos*2+2];
			myHeap[pos*2+2] = temp;

			pos=pos*2+2;
		}
	}
	if(myHeap.Size() == 2)
	{
		if(myHeap[0] < myHeap[1])
		{
			T temp = myHeap[0];
			myHeap[0] = myHeap[1];
			myHeap[1] = temp;
		}
	}

	return returnVal;
}

template<typename T>
inline bool Heap<T>::HasLeftChild(int aPos)
{
	return aPos * 2 + 1 < myHeap.Size();
}

template<typename T>
inline bool Heap<T>::HasRightChild(int aPos)
{
	return aPos * 2 + 2 < myHeap.Size();
}

template<typename T>
inline double Heap<T>::Log2(double aNum)
{
	//double temp = 2;
	return (log(aNum) / log(2));
}

#endif