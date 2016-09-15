#include "Game.h"
#include <hge.h>

const float locHeight = 1024.f;
const float locWidth = 1280.f;

Game::Game(HGE &aHGE)
	:myHGE(aHGE),
	myListSize(1000),
	myNumberOfAlgorithms(5),
	myGotInput(false)
{
}


Game::~Game(void)
{
}

void Game::Init()
{
	myListSize = 5000000;
	mySeed = 1;
	myUnsortedList.Init(8);
	for (unsigned int n = 0; n < myListSize; n++)
	{
		myUnsortedList.Add(Rand() % myListSize);
	}

	myPoints.Init(5);
	for (unsigned n = 0; n < 5; n++)
	{
		myPoints.Add(myUnsortedList);
	}

	myQuickSortThread = new std::thread(&Game::ThreadedQuickSort, this, std::ref(myPoints[eColour::eWhite]));
	myMergeSortThread = new std::thread(&Game::ThreadedMergeSort, this, std::ref(myPoints[eColour::eRed]));
	myShellSortThread = new std::thread(&Game::ThreadedShellSort, this, std::ref(myPoints[eColour::eBlue]));
	myHeapSortThread = new std::thread(&Game::ThreadedHeapSort, this, std::ref(myPoints[eColour::eGreen]));
	myRadixSortThread = new std::thread(&Game::ThreadedRadixSort, this, std::ref(myPoints[eColour::ePurple]));

}

bool Game::Update()
{
	Render();

	return true;
}

void Game::Render()
{
	myHGE.Gfx_BeginScene();
	myHGE.Gfx_Clear(0);

	int valueHeight = static_cast<int>(locHeight / myNumberOfAlgorithms);
	float pixelWidth = static_cast<float>(locWidth / myListSize);
	int pixelIndex = 0;
	for (unsigned long n = 0; n < myNumberOfAlgorithms; n++)
	{
		for (unsigned long i = 0; i < myListSize; i++)
		{
			eColour colour = static_cast<eColour>(n);

			DWORD lineColour = ConvertColor(colour);

			if (i % (int)(myListSize / locWidth) == 0)
			{
				float percentageOfHeight = static_cast<float>(myPoints[n][pixelIndex]) / static_cast<float>(myListSize);

				myHGE.Gfx_RenderLine(static_cast<float>	(pixelIndex*pixelWidth),
					static_cast<float>						((valueHeight)*(n + 1)),
					static_cast<float>						(pixelIndex*pixelWidth),
					static_cast<float>						((valueHeight)*(n + 1) - (percentageOfHeight*valueHeight))
					, (lineColour));
				pixelIndex = i;
			}
		}
	}
	myHGE.Gfx_EndScene();
}

DWORD Game::ConvertColor(eColour colour)
{
	DWORD lineColour = 0xFFFFFFFF;
	if (colour == eWhite)
	{
		lineColour = 0xFFFFFFFF;
	}
	else if (colour == eRed)
	{
		lineColour = 0xFFFF0000;
	}
	else if (colour == eBlue)
	{
		lineColour = 0xFF0000FF;
	}
	else if (colour == eGreen)
	{
		lineColour = 0xFF0000FF;
	}
	else if (colour == ePurple)
	{
		lineColour = 0xFF00FF00;
	}
	else if (colour == eRed)
	{
		lineColour = 0xFF000000;
	}
	return lineColour;
}

void Game::ThreadedQuickSort(LISTTYPE& someData)
{
	QuickSort(someData, 0, someData.Count() - 1);
}
void Game::ThreadedRadixSort(LISTTYPE& someData)
{
	std::atomic_bool startFlag;

	myRadixSort.Init(someData, someData.Count());
	myRadixSort.Sort(startFlag, someData);
}
void Game::ThreadedHeapSort(LISTTYPE& someData)
{
	std::atomic_bool flag;

	myHeapSort.Init(someData, someData.Count());
	myHeapSort.Sort(flag, someData);
}
void Game::ThreadedMergeSort(LISTTYPE& someData)
{
	LISTTYPE anArray;
	anArray.Init(static_cast<unsigned short>(myListSize));
	for (unsigned n = 0; n < myListSize; n++)
	{
		anArray.Add(0);
	}
	MergeSort(someData, anArray, 0, someData.Count() - 1);
}
void Game::ThreadedShellSort(LISTTYPE& someData)
{
	int i;
	int temp;
	int flag = 1;
	int numLength = someData.Count();
	int d = numLength;
	while (flag || (d > 1))      // boolean flag (true when not equal to 0)
	{
		flag = 0;           // reset flag to 0 to check for future swaps
		d = (d + 1) / 2;

		for (i = 0; i < (numLength - d); i++)
		{
			if (someData[i + d] < someData[i])
			{
				temp = someData[i + d];      // swap positions i+d and i
				someData[i + d] = someData[i];
				someData[i] = temp;
				flag = 1;                  // tells swap has occurred
				//Sleep(1);
			}
		}
	}
	return;
}
void Game::MergeSort(LISTTYPE& someData, LISTTYPE& anEmptyArray, unsigned long low, unsigned long high)
{
	int pivot;
	if (low < high)
	{

		pivot = (low + high) / 2;
		MergeSort(someData, anEmptyArray, low, pivot);
		MergeSort(someData, anEmptyArray, pivot + 1, high);
		Merge(someData, anEmptyArray, low, pivot, high);
	}
}
void Game::Merge(LISTTYPE& someData, LISTTYPE& someOtherData, unsigned long aLow, unsigned long aPivot, unsigned long aHigh)
{
	unsigned long h, i, j, k;
	h = aLow;
	i = aLow;
	j = aPivot + 1;

	while ((h <= aPivot) && (j <= aHigh))
	{
		if (someData[h] <= someData[j])
		{
			someOtherData[i] = someData[h];
			h++;
		}
		else
		{
			someOtherData[i] = someData[j];
			j++;
		}
		i++;
		//Sleep(1);
	}
	if (h > aPivot)
	{
		for (k = j; k <= aHigh; k++)
		{
			someOtherData[i] = someData[k];
			i++;
		}
	}
	else
	{
		for (k = h; k <= aPivot; k++)
		{
			someOtherData[i] = someData[k];
			i++;
		}
	}
	for (k = aLow; k <= aHigh; k++)
	{
		//Sleep(1);
		someData[k] = someOtherData[k];
	}
}
int Partition(LISTTYPE& someData, int aP, int aR);
void Game::QuickSort(LISTTYPE& someData, int aP, int aR)
{
	if (aP < aR)
	{

		int j = Partition(someData, aP, aR);
		QuickSort(someData, aP, j - 1);
		QuickSort(someData, j + 1, aR);
	}
}

unsigned long Game::Rand()
{

	mySeed = (mySeed * 1103515245U + 12345U) & 0x7fffffffU;
	return static_cast<int>(mySeed);
}

int Partition(LISTTYPE& someData, int aP, int aR)
{
	unsigned pivot = someData[aR];
	while (aP < aR)
	{

		while (someData[aP] < pivot)
		{
			aP++;
		}
		while (someData[aR] > pivot)
		{
			aR--;
		}
		if (someData[aP] == someData[aR])
		{
			aP++;
		}
		else if (aP < aR)
		{
			int tmp = someData[aP];
			someData[aP] = someData[aR];
			someData[aR] = tmp;
			//Sleep(1);
		}
	}

	return aR;
}

