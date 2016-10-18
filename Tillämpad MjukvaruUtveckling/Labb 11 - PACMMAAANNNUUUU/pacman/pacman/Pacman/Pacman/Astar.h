#ifndef ASTARO_HEADER
#define ASTARO_HEADER
#include "GrowingArray.h"
#include "CU_Vector.h"

struct AstarNode
{
	bool Passable;
	int F;
	int G;
	int H;
	unsigned int Index;
	int parentIndex;
	bool Closed;
};
class Astar
{
public:
	Astar(CU::GrowingArray<bool>& aTileGrid, int aNrOfRows, int aNrOfCols);
	~Astar();

	const CU::GrowingArray<CU::Vector2f>& GetPath(CU::Vector2f aStartTile, CU::Vector2f aEndTile);

private:
	int calcH(int aTileIndex);
	void CheckNode(int aParentIndex,int aRelativIndex);

	int myNrOfTiles;
	int myNrOfRows;
	int myNrOfCols;
	
	int myStartTileIndex;
	int myEndTileIndex;
	CU::GrowingArray<AstarNode> myAstarTileGrid;
	CU::GrowingArray<bool>& myTileGrid;
	CU::GrowingArray<AstarNode> myOpenList;
	CU::GrowingArray<CU::Vector2f> myReturnVector;
	bool myFoundPath;
};
#endif