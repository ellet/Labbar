#ifndef GAME_H
#define GAME_H

#include "GrowingArray.h"
#include "Vector2.h"
#include <thread>
#include "RadixSort.h"
#include "HeapSort.h"

typedef  CU::GrowingArray<unsigned long,int> LISTTYPE;

enum eColour
{
	eWhite = 0,
	eRed = 1,
	eBlue = 2,
	eGreen = 3,
	ePurple = 4
};

class HGE;

class Game
{
public:
	Game(HGE& aHGE);
	~Game(void);
	bool Update();
	void Init();
	void Render();

	void ThreadedQuickSort	(LISTTYPE& someData);
	void QuickSort			(LISTTYPE& someData, int aP, int aR);
	void ThreadedMergeSort	(LISTTYPE& someData);
	void MergeSort			(LISTTYPE& someData,	LISTTYPE& anEmptyArray, unsigned long low, unsigned long high);
	void Merge				(LISTTYPE&,				LISTTYPE&,unsigned long,unsigned long,unsigned long);
	void ThreadedShellSort	(LISTTYPE& someData);
	void ThreadedRadixSort	(LISTTYPE& someData);
	void ThreadedHeapSort	(LISTTYPE& someData);

	

private:
	DWORD ConvertColor(eColour colour);
	unsigned long Rand();
	unsigned long mySeed;
	bool myGotInput;
	HGE &myHGE;
	unsigned long myListSize;
	const unsigned char myNumberOfAlgorithms;
	CU::GrowingArray<LISTTYPE> myPoints;
	RadixSort myRadixSort;
	HeapSort myHeapSort;


	std::thread* myQuickSortThread;
	std::thread* myMergeSortThread;
	std::thread* myRadixSortThread;
	std::thread* myHeapSortThread;
	std::thread* myShellSortThread;
	LISTTYPE myUnsortedList;

	inline bool operator=(const Game& aGame);

};

inline bool Game::operator=(const Game&)
{

}


#endif