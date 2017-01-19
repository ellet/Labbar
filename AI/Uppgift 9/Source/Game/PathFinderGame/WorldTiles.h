#pragma once
#include "Utilities\Container\GridArray.h"
#include "Tile.h"


enum class TileTypes
{
	eField,
	eRoad,
	enumLength
};


class WorldTiles
{
public:
	WorldTiles(const float aTileDistance, const unsigned short aWidth, const unsigned short aHeight);
	~WorldTiles();

	void SetTileType(const TileTypes aTileType, const SB::Vector2f & aPosition);

	void Render() const;

private:
	Tile * GetTileAtPosition(const SB::Vector2f & aPosition);

	void TileDataSetup();

	SB::GrowingArray<TileData> myTileData;

	float myTileDistance;

	SB::GridArray<Tile*> myGrid;
};

