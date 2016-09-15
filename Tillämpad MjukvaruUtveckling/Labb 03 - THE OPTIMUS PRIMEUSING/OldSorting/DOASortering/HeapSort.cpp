#include "HeapSort.h"

void HeapSort::Init(LISTTYPE aArrayPointer, int aSize)
{
	//myArrayPointer = aArrayPointer;
	myArraySize = aSize;
}

void HeapSort::Sort(std::atomic_bool& aStartFlag, LISTTYPE& anArray)
{
	while(aStartFlag == false)
	{
		//Sleep(1);
	}
	HeapSortFun(anArray, myArraySize);
}

void HeapSort::ShiftRight(LISTTYPE& arr, int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;
        /*Check if root is less than left child*/
        if (arr[swapIdx] < arr[leftChild])
        {
            swapIdx = leftChild;
			//Sleep(1);
        }
        /*If right child exists check if it is less than current root*/
        if ((rightChild <= high) && (arr[swapIdx] < arr[rightChild]))
        {
            swapIdx = rightChild;
			//Sleep(1);
        }
        /*Make the biggest element of root, left and right child the root*/
        if (swapIdx != root)
        {
            int tmp = arr[root];
            arr[root] = arr[swapIdx];
            arr[swapIdx] = tmp;
            /*Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself*/
            root = swapIdx;
			//Sleep(1);
        }
        else
        {
            break;
        }
    }
    return;
}

void HeapSort::Heapify(LISTTYPE& arr, int low, int high)
{
    /*Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child*/
    int midIdx = (high - low -1)/2;
    while (midIdx >= 0)
    {
        ShiftRight(arr, midIdx, high);
        --midIdx;
    }
    return;
}
void HeapSort::HeapSortFun(LISTTYPE& arr, int size)
{
   // assert(arr);
   // assert(size > 0);
    /*This will put max element in the index 0*/
    Heapify(arr, 0, size-1);
    int high = size - 1;
    while (high > 0)
    {
        /*Swap max element with high index in the array*/
        int tmp = arr[high];
        arr[high] = arr[0];
        arr[0] = tmp;
        --high;
        /*Ensure heap property on remaining elements*/
        ShiftRight(arr, 0, high);
		//Sleep(1);
    }
    return;
}