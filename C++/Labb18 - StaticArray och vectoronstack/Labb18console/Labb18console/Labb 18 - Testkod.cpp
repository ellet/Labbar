#include "stdafx.h"
#include "VectorOnStack.h"
#include "StaticArray.h"
#include <assert.h>
#include <iostream>


using namespace CommonUtilities;

template class StaticArray < int*, 10 >;
template class VectorOnStack < int*, 10 >;

int main(int argc, char* argv[])
{
	/********************************************************************************************
	 *	STATIC ARRAY - OBS! TESTAR INTE ALLT! EJ KOMPLETT TEST									*
	 ********************************************************************************************/
	

	const int StaticArraySize = 55;
	int *staticArrayNumbers[StaticArraySize];
	StaticArray<int*, StaticArraySize> staticArray1;
	StaticArray<int*, StaticArraySize> staticArray2;
	
	for( int index = 0; index < StaticArraySize; index++ ) 
	{
		staticArrayNumbers[index] = new int( rand() );
		staticArray1[index] = staticArrayNumbers[index];
	}
	
	staticArray2 = staticArray1;
	
	int *newStaticArrayNumber = new int(123);
	staticArray1[0] = newStaticArrayNumber;
	
	assert( *staticArray1[0] != *staticArray2[0] );

	staticArray1.DeleteAll();

	/********************************************************************************************
	 *	VECTOR ON STACK - OBS! TESTAR INTE ALLT! EJ KOMPLETT TEST								*
	 ********************************************************************************************/
	VectorOnStack<int,32> vector1;
	VectorOnStack<int,128> vector2;

	for(int i = 0;i< 12;i++)
	{
		vector1.Add(rand());
	}
	assert(vector1.Size() == 12);
	for(int i = 0;i< 100;i++)
	{
		vector2.Add(rand());
	}
	assert(vector2.Size() == 100);
	
	int temp = vector2[vector2.Size() -1];
	vector2.RemoveCyclicAtIndex(15);
	assert(temp == vector2[15]);

	VectorOnStack<int*, 24> objects;
	for(int i = 0;i < 24;i++)
	{
		objects.Add(new int(i));
	}
	objects.RemoveCyclic(objects[5]);
	assert(objects.Size() == 23);

	VectorOnStack<int*, 10> Derp;
	for (int i = 0; i < 8; i++)
	{
		Derp.Add(new int(i));
	}
	int * tempderp = new int(3);
	Derp.Insert(8, tempderp);
	Derp.DeleteAll();

	/*for(int i = 0;i< 12000;i++)
	{
		vector1.Add(5);
	}

	assert(false && "Fail should crash before this");

	int test = vector1[-100];
	assert(false && "This should fail too");*/
	
	return 0;
}


