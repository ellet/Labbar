#include "stdafx.h"
#include "WorldTiles.h"
#include "Utilities\Container\GrowingArray.h"


WorldTiles::WorldTiles(const float aTileDistance, const unsigned short aWidth, const unsigned short aHeight) : myGrid(aWidth, aHeight, true)
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
		}
	}
}


WorldTiles::~WorldTiles()
{
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
	const SB::GrowingArray<Tile*> & currentTiles = myGrid.GetArray();
	for (unsigned short iTile = 0; iTile < currentTiles.Size(); ++iTile)
	{
		currentTiles[iTile]->Render();
	}
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

void WorldTiles::TileDataSetup()
{
	myTileData.Resize(static_cast<unsigned short>(TileTypes::enumLength));

	myTileData[static_cast<unsigned short>(TileTypes::eField)].SpriteFilePath = "Sprites/fieldTile.dds";



	myTileData[static_cast<unsigned short>(TileTypes::eRoad)].SpriteFilePath = "Sprites/roadTile.dds";
}

