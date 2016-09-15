#pragma once
#include <Windows.h>
#include <atomic>

class QuickSort
{
public:
	static void Init(int* aArrayPointer, int aSize);
	static void Sort(std::atomic_bool &aStartFlag);

	static int* myArrayPointer;
	static int myHigh;
	static int myLow;

private:   
	static void QuickSortFun(int* arr, int left, int right);
};

int* QuickSort::myArrayPointer = nullptr;
int QuickSort::myHigh = 0;
int QuickSort::myLow = 0;

void QuickSort::Init(int* aArrayPointer, int aSize)
{
	myArrayPointer = aArrayPointer;
	myLow = 0;
	myHigh = aSize;
}
void QuickSort::Sort(std::atomic_bool &aStartFlag)
{
	while(aStartFlag == false)
	{
		Sleep(1);
	}
	QuickSortFun(myArrayPointer,myLow,myHigh);
}

void QuickSort::QuickSortFun(int* arr, int left, int right)
 {
  int i = left, j = right;
  int tmp;
  int pivot = arr[(left + right) / 2];

  /* partition */
  while (i <= j) {
        while (arr[i] < pivot)
              i++;
        while (arr[j] > pivot)
              j--;
        if (i <= j) {
              tmp = arr[i];
              arr[i] = arr[j];
              arr[j] = tmp;
              i++;
              j--;
    }
}
/* recursion */
if (left < j)
	QuickSortFun(arr, left, j);
if (i < right)
	QuickSortFun(arr, i, right);
}