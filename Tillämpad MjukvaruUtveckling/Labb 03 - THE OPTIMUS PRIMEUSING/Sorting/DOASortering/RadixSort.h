#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <atomic>
#include <Windows.h>
#include "GrowingArray.h"

typedef  CU::GrowingArray<unsigned long, int> LISTTYPE;

class RadixSort
{
public:
	RadixSort();
	~RadixSort();

	void Init(LISTTYPE& aArrayPointer, int aSize);
	void Sort(std::atomic_bool &aStartFlag, LISTTYPE& anArray);

	int mySize;

private:
	void Radixsort(LISTTYPE& input, int n);

};



#endif