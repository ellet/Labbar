#include "stdafx.h"
#include "MapGenerationAlgorithm.h"
#include "Player.h"
#include "Map.h"
#include "MapFactory.h"
#include "MapSetting.h"

MapGenerationAlgorithm::MapGenerationAlgorithm(EntityFactory& aEntityFactory, EnemyFactory& aEnemyFactory, Map& aMap, MapSetting& myMapSettings, MapFactory& anMapFactory) : 
	myEntityFactory(aEntityFactory), myEnemyFactory(aEnemyFactory), myMap(aMap), myMapSetting(myMapSettings), myMapFactory(anMapFactory)
{
}


MapGenerationAlgorithm::~MapGenerationAlgorithm()
{
}


void MapGenerationAlgorithm::Init()
{
	myRoomTypeManager.LoadRoomTypes();
}

void MapGenerationAlgorithm::InitMap(const int aWidth, const int aHeight)
{
	myMap.CreateMap(aWidth, aHeight);
	myMap.FillWithWalls(myMapFactory);
}

// Call "template method" pattern
void MapGenerationAlgorithm::GenerateMap(Player &aPlayer)
{
	InitMap(myMapSetting.GetMapWidth(), myMapSetting.GetMapHeight());
	CreateSpatialAreas();
	CreateEntrance();
	RemoveTilesNotConnectedToEntrance();
	CreateSpecials();
	CreateEnemies(myMapSetting.GetEnemyMaxCount(), myMapSetting.GetEnemyMinCount());
	CreateItems(myMapSetting.GetItemMaxCount(), myMapSetting.GetItemMinCount());
	CreateExit();
	GenerateWallSides();
}

void MapGenerationAlgorithm::CreateSpecials()
{
	myMap.CreateSpecials(myMapFactory, 5);
}

void MapGenerationAlgorithm::CreateExit()
{
	int bestTile = -1;
	int bestDistance = 0;
	for (int i = 0; i < 100; ++i)
	{
		int randomTile = myMap.FindRandomFloorTile();
		int distance = abs((randomTile % myMap.GetMapWidth()) - (myStartTileIndex % myMap.GetMapWidth())) +
			abs(randomTile / myMap.GetMapWidth() - myStartTileIndex / myMap.GetMapWidth());
		if (distance > bestDistance)
		{
			bestDistance = distance;
			bestTile = randomTile;
		}
	}
	assert(bestTile != -1 && "No exit tile could be created!");

	myMap.CreateExit(myMapFactory, bestTile);
}

void MapGenerationAlgorithm::CreateEntrance()
{
	myStartTileIndex = myMap.FindRandomFloorTile();
	myMap.SetStartPosition(myStartTileIndex);
}

void MapGenerationAlgorithm::CreateEnemies(const int aMaxCount, const int aMinCount)
{
	int enemies = aMinCount + rand() % MAX(aMaxCount - aMinCount, 1);
	for (int i = 0; i < enemies; ++i)
	{
		int index = myMap.FindRandomFloorTile();
		myMap.AddEnemy(myMapFactory.CreateEnemy(), index);
	}
}

void MapGenerationAlgorithm::RemoveTilesNotConnectedToEntrance()
{

	CU::GrowingArray<bool> visitedTiles;
	visitedTiles.Resize(myMap.GetMapWidth() * myMap.GetMapHeight());
	for (int i = 0; i < visitedTiles.Size(); ++i)
	{
		visitedTiles[i] = false;
	}

	VisitTile(myMap.GetStartTileIndex(), visitedTiles);

	for (int i = 0; i < visitedTiles.Size(); ++i)
	{
		if (visitedTiles[i] == false)
		{
			myMap.CreateWall(i, myMapFactory);
		}
	}
}

// TODO! Check index+1/-1 doesn't break line
void MapGenerationAlgorithm::VisitTile(int aIndex, CU::GrowingArray<bool>& someVisitedTiles) const
{
	if (myMap.IndexIsWall(aIndex) == false)
	{
		someVisitedTiles[aIndex] = true;
		const int MapWidth = myMap.GetMapWidth();

		if (IndexOutOfBounds(aIndex + 1) == false && someVisitedTiles[aIndex + 1] == false)
		{
			VisitTile(aIndex + 1, someVisitedTiles);
		}

		if (IndexOutOfBounds(aIndex - 1) == false && someVisitedTiles[aIndex - 1] == false)
		{
			VisitTile(aIndex - 1, someVisitedTiles);
		}

		if (IndexOutOfBounds(aIndex + MapWidth) == false && someVisitedTiles[aIndex + MapWidth] == false)
		{
			VisitTile(aIndex + MapWidth, someVisitedTiles);
		}

		if (IndexOutOfBounds(aIndex - MapWidth) == false && someVisitedTiles[aIndex - MapWidth] == false)
		{
			VisitTile(aIndex - MapWidth, someVisitedTiles);
		}
	}
}

bool MapGenerationAlgorithm::IndexOutOfBounds(const int aIndex) const
{
	return (aIndex < 0 || aIndex >= (myMap.GetMapWidth() * myMap.GetMapHeight()));
}

void MapGenerationAlgorithm::GenerateWallSides()
{
	for (int i = 0; i < myMap.GetMapWidth() * myMap.GetMapHeight() - myMap.GetMapWidth(); ++i)
	{
		if (myMap.IndexIsWall(i) == true && myMap.IndexIsWall(i + myMap.GetMapWidth()) == false)
		{
			myMap.CreateWallSide(i, myMapFactory);
		}
	}
}

void MapGenerationAlgorithm::CreateItems(const int aMaxCount, const int aMinCount)
{
	int items = aMinCount + rand() % MAX(aMaxCount - aMinCount, 1);
	for (int i = 0; i < items; ++i)
	{
		int index = myMap.FindRandomFloorTile();
		myMap.AddItem(myMapFactory.CreateItem(), index, myEntityFactory);
	}
}