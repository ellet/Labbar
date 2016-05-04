// lab_25.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GrowingArray\GrowingArray.h"
#include "assert.h"
#include <stdlib.h>

using namespace CommonUtilities;

// --------------------------------
// OBS! Ej komplett testkod. Testar bara basic saker. Räkna med att ni får utöka det om det ska testa för alla fel.
// --------------------------------

int _tmain(int argc, _TCHAR* argv[])
{
	GrowingArray<int> growingArray;
	GrowingArray<int> growingArray2;
	growingArray.Init(100);
	// Verifiera att storleken på arrayen är 100 	
	growingArray2.Init(50);
	
	for(int i =0;i<105;i++)
	{
		growingArray.Add(rand());
		if (i == 98)
		{
			int derp = 5;
			++derp;
		}
	}

	
	// verifiera att arrayenväxte korrekt.
	growingArray2=growingArray;

	// verifiera att growingArray2 är en perfekt kopia av growingarray
	int test=growingArray.GetLast();
	growingArray.RemoveCyclicAtIndex(10);
	assert(growingArray[10]==test);
	// verifiera att cyclic remove At index fungerar
	assert(growingArray.Size()!=growingArray2.Size());
	// verifiera att de verkligen har seperat minne så att förändrignar av growingarray inte påverkar growingarray2
	int temp=11;
	growingArray.Insert(10,temp);
	assert(growingArray[11]==test);
	assert(growingArray.Size()==growingArray2.Size());
	// verifierr att insert fungerar;
	growingArray.RemoveCyclic(test);
	assert(growingArray.Size()!=growingArray2.Size());
	// verifiera att cyclic remove fungerar
	growingArray2.RemoveAll();
	assert(growingArray2.Size()==0);
	// verifiera att remove funkar
	growingArray.ReInit(10);
	assert(growingArray.Size()==0);
	//verifiera att reinit funkar
	GrowingArray<int*> growingArray3;
	growingArray3.Init(100);
	for(int i =0;i<105;i++)
	{
		growingArray3.Add(new int(rand()));
	}

	const GrowingArray<int*>& refObject = growingArray3;
	int* test2=refObject.GetLast();
	growingArray3.DeleteCyclicAtIndex(10);
	assert(refObject[10]==test2);
	// verifiera att cyclic delete At index fungerar
	growingArray3.DeleteCyclic(test2);
	assert(refObject[10]!=test2);
	assert(refObject.Size()==103);
	// verifiera att cyclic delete fungerar

	growingArray3.DeleteAll();
	assert(refObject.Size()==0);
	// verifiera att cyclic delete fungerar

	//test2=growingArray3[10];  // denna raden ska smälla

	//assert(0 && "Krashade inte på förra raden FAIL");

	return 0;
}

