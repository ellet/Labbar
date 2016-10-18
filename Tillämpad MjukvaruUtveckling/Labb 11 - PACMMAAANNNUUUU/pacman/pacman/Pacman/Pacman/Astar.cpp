//include "StdAfx.h"
#include "Astar.h"

#define PERFECTPATH 1 // 0 == perfect 1 == astar

Astar::Astar(CU::GrowingArray<bool>& aTileGrid, int aNrOfRows, int aNrOfCols)
:myTileGrid(aTileGrid)
{
	myOpenList.Init(aTileGrid.Count()+10,1000);
	myReturnVector.Init(aTileGrid.Count()+10,1000);

	myNrOfTiles = aNrOfRows*aNrOfCols;
	myNrOfRows = aNrOfRows;
	myNrOfCols = aNrOfCols;
	myStartTileIndex = 0;
	myEndTileIndex = 0;
	myFoundPath = false;
	myAstarTileGrid.Init(aTileGrid.Count()+10,1000);
	for(int index = 0; index < aTileGrid.Count(); index++)
	{
		AstarNode tempNode;
		tempNode.Passable = true;
		tempNode.F = 0;
		tempNode.G = 0;
		tempNode.H = 0;
		tempNode.Index = index;
		tempNode.parentIndex = 0;
		tempNode.Closed = false;
		myAstarTileGrid.Add(tempNode);
	}
}

Astar::~Astar()
{
}

const CU::GrowingArray<CU::Vector2f>& Astar::GetPath(CU::Vector2f aStartTile, CU::Vector2f aEndTile)
{
	for(int tileIndex = 0; tileIndex < myTileGrid.Count(); tileIndex++)
	{
		myAstarTileGrid[tileIndex].Closed = false;
		myAstarTileGrid[tileIndex].F = 0;
		myAstarTileGrid[tileIndex].G = 0;
		myAstarTileGrid[tileIndex].H = 0;
		myAstarTileGrid[tileIndex].parentIndex = -1;
		myAstarTileGrid[tileIndex].Passable = myTileGrid[tileIndex];
	}

	myReturnVector.RemoveAll();
	myFoundPath = false;
	myOpenList.RemoveAll();
	myStartTileIndex = static_cast<int>(aStartTile.myX)+static_cast<int>(aStartTile.myY)*myNrOfRows;
	myEndTileIndex = static_cast<int>(aEndTile.myX)+static_cast<int>(aEndTile.myY)*myNrOfRows;
	

	if(myAstarTileGrid[myEndTileIndex].Passable == false)
	{
		return myReturnVector;
	}

	myOpenList.Add(myAstarTileGrid[myStartTileIndex]);
	int tileIndex = 0;
	while(myOpenList.Count() != 0)
	{
		unsigned int lowestFCostIndex = 0;
		for(int openIndex = 0; openIndex < myOpenList.Count(); openIndex++)
		{
			if(myOpenList[openIndex].F < myOpenList[lowestFCostIndex].F)
			{
				lowestFCostIndex = openIndex;
			}
		}
		tileIndex = myOpenList[lowestFCostIndex].Index;
		myAstarTileGrid[tileIndex].Closed = true;

		int thisX = tileIndex%myNrOfRows;
		int thisY = tileIndex/myNrOfRows;
		int targetX = myEndTileIndex%myNrOfRows;
		int targetY = myEndTileIndex/myNrOfRows;

		if(thisX == targetX && thisY == targetY)
		{
			myFoundPath = true;
			break;
		}
		myOpenList.RemoveCyclicAtIndex(lowestFCostIndex);


		CheckNode(tileIndex,(-myNrOfRows));	//TOP

		CheckNode(tileIndex,1);					//RIGHT
	
		CheckNode(tileIndex,-1);			//LEFT
	
		CheckNode(tileIndex,(myNrOfRows));		//BOTTOM
		
	}
	if(myFoundPath == true)
	{
		int loopTileIndex = tileIndex;

		while(loopTileIndex != -1)
		{
			float returnX = static_cast<float>(loopTileIndex%myNrOfRows);
			float returnY = static_cast<float>(loopTileIndex/myNrOfRows);
			myReturnVector.Add(CU::Vector2f(returnX,returnY));
		
			loopTileIndex = myAstarTileGrid[loopTileIndex].parentIndex;
		}

		myReturnVector.RemoveCyclicAtIndex(myReturnVector.Count()-1);

	}
	
	return myReturnVector;
}

int Astar::calcH(int aTileIndex)
{
	CU::Vector2f curTile;
	CU::Vector2f tarTile;

	curTile.myX = static_cast<float>(aTileIndex%myNrOfRows);
	curTile.myY = static_cast<float>(aTileIndex/myNrOfRows);
	tarTile.myX = static_cast<float>(myEndTileIndex%myNrOfRows);
	tarTile.myY = static_cast<float>(myEndTileIndex/myNrOfRows);
	int temp = (10*static_cast<int>((tarTile-curTile).Length()));
	return temp;
}

void Astar::CheckNode(int aParentIndex,int aRelativIndex)
{
	if(myAstarTileGrid[aParentIndex+aRelativIndex].Closed == false && myAstarTileGrid[aParentIndex+aRelativIndex].Passable == true)
	{
		bool isInOpenList = false;
		for(int openIndex = 0; openIndex < myOpenList.Count(); openIndex++)
		{
			if(myOpenList[openIndex].Index == aParentIndex+aRelativIndex)
			{
				isInOpenList = true;
				break;
			}
		}
		int Gcost = 14;
		if(aRelativIndex == 1 || aRelativIndex == -1 || aRelativIndex == myNrOfRows || aRelativIndex == -myNrOfRows)
		{
			Gcost = 10;
		}
		if(isInOpenList == false)
		{

			myAstarTileGrid[aParentIndex+aRelativIndex].parentIndex = aParentIndex;
			myAstarTileGrid[aParentIndex+aRelativIndex].G = myAstarTileGrid[aParentIndex].G + Gcost;
			myAstarTileGrid[aParentIndex+aRelativIndex].H = calcH(aParentIndex+aRelativIndex);
			myAstarTileGrid[aParentIndex+aRelativIndex].F = myAstarTileGrid[aParentIndex+aRelativIndex].H*PERFECTPATH + myAstarTileGrid[aParentIndex+aRelativIndex].G;

			myOpenList.Add(myAstarTileGrid[aParentIndex+aRelativIndex]);
		}
		else
		{
			if(myAstarTileGrid[aParentIndex+aRelativIndex].G > myAstarTileGrid[aParentIndex].G + Gcost)
			{

				myAstarTileGrid[aParentIndex+aRelativIndex].parentIndex = aParentIndex;
				myAstarTileGrid[aParentIndex+aRelativIndex].G = myAstarTileGrid[aParentIndex].G + Gcost;
				myAstarTileGrid[aParentIndex+aRelativIndex].F = myAstarTileGrid[aParentIndex+aRelativIndex].H*PERFECTPATH + myAstarTileGrid[aParentIndex+aRelativIndex].G;
			}
		}
	}
}