#include "stdafx.h"
#include "WorldTiles.h"
#include "Utilities\Container\GrowingArray.h"


SB::GridArray<float, unsigned int> testGrid(10, 10, false);

WorldTiles::WorldTiles(const float aTileDistance, const unsigned int aWidth, const unsigned int aHeight) : myGrid(aWidth, aHeight, true), myDefaultPathMap(aWidth, aHeight, true)
{
	TileDataSetup();

	myTileDistance = aTileDistance;

	for (unsigned short iX = 0; iX < myGrid.Width(); ++iX)
	{
		for (unsigned short iY = 0; iY < myGrid.Height(); ++iY)
		{
			myGrid.Access(iX, iY) = new Tile();
			myGrid.Access(iX, iY)->SetTileData(myTileData[static_cast<unsigned short>(TileTypes::eField)]);
			myGrid.Access(iX, iY)->SetPosition({aTileDistance + (static_cast<float>(iX) * aTileDistance), aTileDistance + (static_cast<float>(iY) * aTileDistance) });
			myGrid.Access(iX, iY)->SetTileIndiceData(iX, iY);

			myDefaultPathMap.Access(iX, iY) = 9999999.f;
		}
	}

	testGrid = myDefaultPathMap;
}


WorldTiles::~WorldTiles()
{
}

void WorldTiles::CreatePath(const SB::Vector2f aFromPosition, const SB::Vector2f aToPosition, SB::GrowingArray<SB::Vector2f> & aVectorOfPathPositions)
{
	if (GetTileAtPosition(aFromPosition) == nullptr ||
		GetTileAtPosition(aToPosition) == nullptr)
	{
		return;
	}

	SB::Vector2ui startTile = GetTileIndicesAtPosition(aFromPosition);
	SB::Vector2ui goalTile = GetTileIndicesAtPosition(aToPosition);

	SB::GridArray<float, unsigned int> mappedGrid = myDefaultPathMap;
	SB::GrowingArray<Tile*, unsigned int> tilesToExplore;
	mappedGrid.Access(goalTile.x, goalTile.y) = 0.f;
	tilesToExplore.Add(GetTileAtPosition(goalTile));

	do
	{
		CalculateMap(tilesToExplore, mappedGrid);
	} while (tilesToExplore.Size() > 0);

	testGrid = mappedGrid;
}

void WorldTiles::SetTileType(const TileTypes aTileType, const SB::Vector2f & aPosition)
{
	Tile * selectedTile = GetTileAtPosition(aPosition);

	if (selectedTile != nullptr)
	{
		selectedTile->SetTileData(myTileData[static_cast<unsigned short>(aTileType)]);
	}
}

void WorldTiles::Render() const
{
	for (unsigned short iX = 0; iX < myGrid.Width(); ++iX)
	{
		for (unsigned short iY = 0; iY < myGrid.Height(); ++iY)
		{
			//myGrid.Access(iX, iY)->Render(std::to_string(iX) + " - " + std::to_string(iY));

			std::string Value = std::to_string(testGrid.Access(iX, iY));
			Value.resize(2);
			myGrid.Access(iX, iY)->Render(Value);
		}
	}
}

void WorldTiles::CalculateMap(SB::GrowingArray<Tile*, unsigned int> & aTilesToExplore, SB::GridArray<float, unsigned int> & myMapToBuild)
{
	if (aTilesToExplore.Size() < 1)
	{
		return;
	}
	const Tile & currentTile = *aTilesToExplore[0];


	SB::Vector2ui tileIndices;
	const unsigned short currentX = currentTile.GetXIndex();
	const unsigned short currentY = currentTile.GetYIndex();

	const float currentTileCost = myMapToBuild.Access(currentX, currentY);
	Tile * testTile = nullptr;
	testTile = CheckTile(currentX + 1, currentY, myMapToBuild, currentTileCost);
	if (testTile != nullptr)
	{
		aTilesToExplore.Add(testTile);
	}

	testTile = CheckTile(currentX, currentY + 1, myMapToBuild, currentTileCost);
	if (testTile != nullptr)
	{
		aTilesToExplore.Add(testTile);
	}

	testTile = CheckTile(currentX - 1, currentY, myMapToBuild, currentTileCost);
	if (testTile != nullptr)
	{
		aTilesToExplore.Add(testTile);
	}

	testTile = CheckTile(currentX, currentY - 1, myMapToBuild, currentTileCost);
	if (testTile != nullptr)
	{
		aTilesToExplore.Add(testTile);
	}

	aTilesToExplore.RemoveAtIndex(0);
}


Tile* WorldTiles::CheckTile(const unsigned int iX, const unsigned int iY, SB::GridArray<float, unsigned int> & aMapToBuild, const float aPreviousCost)
{
	Tile* currentTile = GetTileAtPosition(iX, iY);
	if (currentTile == nullptr)
	{
		return nullptr;
	}

	const float newCost = aPreviousCost + currentTile->GetTileCost();
	const float currentCost = aMapToBuild.Access(iX, iY);
	if (currentCost <= newCost)
	{
		return nullptr;
	}

	aMapToBuild.Access(iX, iY) = newCost;
	return currentTile;
}

SB::Vector2ui WorldTiles::GetTileIndicesAtPosition(const SB::Vector2f & aPosition)
{
	const float xTile = (aPosition.x - (myTileDistance / 2.f)) / myTileDistance;
	const float yTile = (aPosition.y - (myTileDistance / 2.f)) / myTileDistance;

	return SB::Vector2ui(static_cast<unsigned short>(xTile), static_cast<unsigned short>(yTile));
}

Tile * WorldTiles::GetTileAtPosition(const SB::Vector2f & aPosition)
{
	const float xTile = (aPosition.x - (myTileDistance / 2.f)) / myTileDistance;
	const float yTile = (aPosition.y - (myTileDistance / 2.f)) / myTileDistance;

	if (xTile > 0.f && xTile < static_cast<float>(myGrid.Width())
		&& yTile > 0.f && yTile < static_cast<float>(myGrid.Height()))
	{
		const unsigned short realTileX = static_cast<unsigned short>(xTile);
		const unsigned short realTileY = static_cast<unsigned short>(yTile);

		return myGrid.Access(realTileX, realTileY);
	}

	return nullptr;
}

Tile * WorldTiles::GetTileAtPosition(const SB::Vector2ui & aPosition)
{
	return GetTileAtPosition(aPosition.x, aPosition.y);
}

Tile * WorldTiles::GetTileAtPosition(const unsigned int aX, const unsigned int aY)
{
	if (aX > myGrid.Width() - 1 || aY > myGrid.Height() - 1)
	{
		return nullptr;
	}

	return myGrid.Access(aX, aY);
}

void WorldTiles::TileDataSetup()
{
	myTileData.Resize(static_cast<unsigned short>(TileTypes::enumLength));

	myTileData[static_cast<unsigned short>(TileTypes::eField)].SpriteFilePath = "Sprites/fieldTile.dds";



	myTileData[static_cast<unsigned short>(TileTypes::eRoad)].SpriteFilePath = "Sprites/roadTile.dds";
}

