#pragma once
#pragma message( "Compiled " __FILE__ " on " __DATE__ " at " __TIME__ ) 

#include "..\GrowingArray.h"
#include "Greater.h"
#include "Lesser.h"
#include "GreaterPointer.h"
#include "LesserPointer.h"
namespace ENGINE_NAMESPACE
{
	template<typename TYPE, typename COMPARER>
	class Heap
	{
	public:
		Heap();
		Heap(unsigned short aSize);
		Heap(ENGINE_NAMESPACE::GrowingArray<TYPE, unsigned int> aArray);
		ENGINE_NAMESPACE::GrowingArray<TYPE, unsigned int> &GetArray(){ return myArray; }

		void Remove(TYPE &aData);
		TYPE &GetTop();
		void Enqueue(TYPE aData);
		TYPE Dequeue();
		bool IsEmpty() { if (myArray.Size() > 0) return false; return true; };

		void SiftDown(unsigned int aIndex);
		void RemoveAll();
		void Print();
	private:
		void FloydSort();
		void RecursiveSort(unsigned int aStartIndex);
		ENGINE_NAMESPACE::GrowingArray<TYPE, unsigned int> myArray;
		COMPARER Compare;
		unsigned int myLastIndex;
		unsigned int myLastNonLeaf;
	};

	
	
	

};
#include "Heap.inl"