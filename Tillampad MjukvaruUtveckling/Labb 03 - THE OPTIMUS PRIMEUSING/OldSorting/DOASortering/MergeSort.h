#pragma once

#include <atomic>
#include <assert.h>
#include <Windows.h>

class MergeSort
{
public:
	static void Init(int* aArrayPointer, int aSize);
	static void Sort(std::atomic_bool& aStartFlag);

	static int* myArrayPointer;
	static int myHigh;
	static int myLow;

private:
	static void MergeSortFun(int* arr, int low, int high);
	static void Merge(int* arr, int low, int middle, int high);
};

int* MergeSort::myArrayPointer = nullptr;
int MergeSort::myHigh = 0;
int MergeSort::myLow = 0;


void MergeSort::Init(int* aArrayPointer, int aSize)
{
	myArrayPointer = aArrayPointer;
	myLow = 0;
	myHigh = aSize - 1;
}
void MergeSort::Sort(std::atomic_bool &aStartFlag)
{
	while(aStartFlag == false)
	{
		Sleep(1);
	}
	MergeSortFun(myArrayPointer,myLow,myHigh);
}
void MergeSort::Merge(int* arr, int low, int middle, int high)
{
	int* tmp = new int[high-low+1];
	int i = low;
	int j = middle+1;
	int k = 0;
	while ((i <= middle) && (j <= high))
	{
		if (arr[i] < arr[j])
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}
	if (i <= middle)
	{
		while (i <= middle)
			tmp[k++] = arr[i++];
	}
	if (j <= high)
	{
		while (j <= high)
			tmp[k++] = arr[j++];
	}

	for (k = low; k <= high; ++k)
		arr[k] = tmp[k-low];
	delete[] tmp;
	return;
}
void MergeSort::MergeSortFun(int* arr, int low, int high)
{
	assert(arr);
	if (low < high)
	{
		int middle = (high + low)/2;
		MergeSortFun(arr, low, middle);
		MergeSortFun(arr, middle+1, high);
		Merge(arr, low, middle, high);
	}
	return;
}