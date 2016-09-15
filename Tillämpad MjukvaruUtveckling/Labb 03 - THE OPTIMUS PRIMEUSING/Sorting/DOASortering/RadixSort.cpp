#include "RadixSort.h"



RadixSort::RadixSort()
{

}
RadixSort::~RadixSort()
{

}

void RadixSort::Init(LISTTYPE& aArrayPointer, int aSize)
{
	//myArray = aArrayPointer;
	mySize = aSize;
}
void RadixSort::Sort(std::atomic_bool &aStartFlag, LISTTYPE& anArray)
{
	while(aStartFlag == false)
	{
		//Sleep(1);
	}

	Radixsort(anArray,mySize);
}

void RadixSort::Radixsort(LISTTYPE& input, int n)
{
  int i;

  // find the max number in the given list.
  // to be used in loop termination part.
  int maxNumber = input[0];
  for (i = 1; i < n; i++)
  {
    if (input[i] > maxNumber)
		
      maxNumber = input[i];
	//Sleep(1);
  }

  // run the loop for each of the decimal places
  int exp = 1;
  int *tmpBuffer = new int[n];
  while (maxNumber / exp > 0)
  {
    int decimalBucket[10] = {  0 };
    // count the occurences in this decimal digit.
    for (i = 0; i < n; i++)
	{
		//Sleep(1);
		decimalBucket[input[i] / exp % 10]++;
	}

    // Prepare the position counters to be used for re-ordering the numbers
    // for this decimal place.
    for (i = 1; i < 10; i++)
	{
		//Sleep(1);
		decimalBucket[i] += decimalBucket[i - 1];
	}

    // Re order the numbers in the tmpbuffer and later copy back to original buffer.
    for (i = n - 1; i >= 0; i--)
	{
		//Sleep(1);
		tmpBuffer[--decimalBucket[input[i] / exp % 10]] = input[i];
	}
    for (i = 0; i < n; i++)
	{
		//Sleep(1);
		input[i] = tmpBuffer[i];
	}

    // Move to next decimal place.
    exp *= 10;

  }
}
