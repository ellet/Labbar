#include "stdafx.h"
#include "CellularAutomata.h"
#include "Map.h"
#include "MapSetting.h"
#include "MapFactory.h"

CellularAutomata::CellularAutomata(EntityFactory& aEntityFactory, EnemyFactory& aEnemyFactory, Map& aMap, MapSetting& aMapSettings, MapFactory &aMapFactory) :
	MapGenerationAlgorithm(aEntityFactory, aEnemyFactory, aMap, aMapSettings, aMapFactory)
{
}

CellularAutomata::~CellularAutomata()
{
}

void CellularAutomata::CreateSpatialAreas() 
{
	CreateCaves();
}

void CellularAutomata::CreateCaves()
{
	RandomizeWalls();
	SmoothMap(4, 3, 1);
	SmoothMap(12, 8, 2);
}


void CellularAutomata::RandomizeWalls()
{
	for (int y = 1; y < myMap.GetMapHeight() - 1; ++y)
	{
		for (int x = 1; x < myMap.GetMapWidth() - 1; ++x)
		{
			int tileIndex = myMap.CalculateTileIndexByIndex(x, y);
			int tileIsFloor = rand() % 10;
			if (tileIsFloor < 6)
			{
				myMap.CreateFloor(tileIndex, myMapFactory);
			}
			else
			{
				myMap.CreateWall(tileIndex, myMapFactory);
			}
		}
	}
}

void CellularAutomata::SmoothMap(const int aWallLimit, const int aFloorLimit, const int aSize)
{
	for (int y = 1; y < myMap.GetMapHeight() - 1; ++y)
	{
		for (int x = 1; x < myMap.GetMapWidth() - 1; ++x)
		{
			int surroundingWallCount = GetSurroundingWallCount(x, y, aSize);
			int tileIndex = myMap.CalculateTileIndexByIndex(x, y);
			if (surroundingWallCount > aWallLimit)
			{
				myMap.CreateWall(tileIndex, myMapFactory);
			}
			else if (surroundingWallCount < aFloorLimit)
			{
				myMap.CreateFloor(tileIndex, myMapFactory);
			}
		}
	}
}

int	CellularAutomata::GetSurroundingWallCount(const int aX, const int aY, const int aSize)
{
	int walls = 0;
	for (int y = aY - aSize; y <= aY + aSize; ++y)
	{
		for (int x = aX - aSize; x <= aX + aSize; ++x)
		{
			if ((y == aY && x == aX) == false && myMap.OutOfBounds(x, y) == false && myMap.IndexIsWall(myMap.CalculateTileIndexByIndex(x, y)) == true ||
				x == 0 || y == 0 || x == myMap.GetMapWidth() - 1 || y == myMap.GetMapHeight() - 1)
			{
				++walls;
			}
		}
	}

	return walls;
}
