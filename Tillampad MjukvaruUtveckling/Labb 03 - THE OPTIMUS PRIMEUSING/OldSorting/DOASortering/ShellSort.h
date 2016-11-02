#pragma once

#include <atomic>
#include <Windows.h>

class ShellSort
{
public:
	static void Init(int* aArrayPointer, int aSize);
	static void Sort(std::atomic_bool &aStartFlag);

	static int* myArrayPointer;
	static int mySize;

private:
	static void ShellSortFun(int *array, int number_of_elements);
};

int* ShellSort::myArrayPointer = nullptr;
int ShellSort::mySize = 0;

void ShellSort::Init(int* aArrayPointer, int aSize)
{
	myArrayPointer = aArrayPointer;
	mySize = aSize;
}

void ShellSort::Sort(std::atomic_bool &aStartFlag)
{
	while(aStartFlag == false)
	{
		Sleep(1);
	}
	ShellSortFun(myArrayPointer,mySize);
}

void ShellSort::ShellSortFun(int *array, int number_of_elements)
{
    int i, j, increment, temp;
    for(increment = number_of_elements/2;increment > 0; increment /= 2)
    {
        for(i = increment; i<number_of_elements; i++)
        {
            temp = array[i];
            for(j = i; j >= increment ;j-=increment)
            {
                if(temp < array[j-increment])
                {
                    array[j] = array[j-increment];
                }
                else
                {
                    break;
                }
            }
            array[j] = temp;
        }
    }
}