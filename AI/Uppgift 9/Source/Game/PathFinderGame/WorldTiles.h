#pragma once
#include "Utilities\Container\GridArray.h"
#include "Tile.h"
#include "Rendering\BDText.h"
#include <Utilities\Container\Heap\Heap.h>


enum class TileTypes
{
	eField,
	eRoad,
	enumLength
};

class WorldTiles
{
public:
	WorldTiles(const float aTileDistance, const unsigned int aWidth, const unsigned int aHeight);
	~WorldTiles();

	void CreatePath(const SB::Vector2f aFromPosition, const SB::Vector2f aToPosition, SB::GrowingArray<SB::Vector2f> & aVectorOfPathPositions);
	void SetTileType(const TileTypes aTileType, const SB::Vector2f & aPosition);

	void Render() const;

private:
	void CalculateMap(SB::GrowingArray<Tile*, unsigned int> & aTilesToExplore, SB::GridArray<float, unsigned int> & myMapToBuild);
	void CalculatePath(SB::GrowingArray<SB::Vector2f> & aWayPoints, const SB::GridArray<float, unsigned int> & myMapToRead, const SB::Vector2ui & aStartPos);

	void FlagPath(const SB::GrowingArray<SB::Vector2f> & aPathToFlag);

	Tile* CheckTile(const unsigned int iX, const unsigned int iY, SB::GridArray<float, unsigned int> & aMapToBuild, const float aPreviousCost);

	SB::Vector2ui GetTileIndicesAtPosition(const SB::Vector2f & aPosition);
	Tile * GetTileAtPosition(const SB::Vector2f & aPosition);
	Tile * GetTileAtPosition(const SB::Vector2ui & aPosition);
	Tile * GetTileAtPosition(const unsigned int aX, const unsigned int aY);

	void TileDataSetup();

	SB::GrowingArray<TileData> myTileData;
	

	float myTileDistance;

	SB::GridArray<float, unsigned int> myDefaultPathMap;
	SB::GridArray<Tile*, unsigned int> myGrid;
};

