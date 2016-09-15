#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <atomic>
#include <assert.h>
#include "GrowingArray.h"
#include <Windows.h>

typedef  CU::GrowingArray<unsigned long, int> LISTTYPE;

class HeapSort
{
public:
	void Init(LISTTYPE aArrayPointer, int aSize);
	void Sort(std::atomic_bool& aStartFlag, LISTTYPE& anArray);


	int	myArraySize;

private:
	void HeapSortFun(LISTTYPE& arr, int size);
	void Heapify(LISTTYPE& arr, int low, int high);
	void ShiftRight(LISTTYPE& arr, int low, int high);

};

#endif