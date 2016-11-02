#include "StdAfx.h"
#include "TileGrid.h"

FG::TileGrid::TileGrid()
{
}

FG::TileGrid::~TileGrid()
{
}

void FG::TileGrid::Init()
{
    for(int x = 0; x < GRIDSIZE_X; x++)
    {
        for(int y = 0; y < GRIDSIZE_Y; y++)
        {
            Tile newTile;
            newTile.myPosition.myX = x * TILESIZE + TILESIZE / 2;
            newTile.myPosition.myY = y * TILESIZE + TILESIZE / 2;
            myTileSet[x][y] = newTile;
        }
    }
}

FG::Tile* FG::TileGrid::GetGridTile(int aX, int aY)
{
    return &myTileSet[aX][aY];
}

FG::Tile* FG::TileGrid::GetGridTile(float aX, float aY)
{
	CU::Vector2i gridPosition;
	gridPosition.myX = static_cast<int>(aX / TILESIZE);
	gridPosition.myY = static_cast<int>(aY / TILESIZE);
	if(TileInsideGrid(gridPosition))
	{
		return &myTileSet[gridPosition.myX][gridPosition.myY];
	}
	else
	{
		return NULL;
	}
}

FG::Tile* FG::TileGrid::GetNextTile(FG::Tile* aCurrentTile, CU::Vector2i aDirection)
{
	CU::Vector2i gridPosition;
	gridPosition.myX = static_cast<int>(aCurrentTile->myPosition.myX / TILESIZE);
	gridPosition.myY = static_cast<int>(aCurrentTile->myPosition.myY / TILESIZE);

	gridPosition += aDirection;

	if(TileInsideGrid(gridPosition))
	{
		return &myTileSet[gridPosition.myX][gridPosition.myY];
	}

	return NULL;
}

bool FG::TileGrid::TileInsideGrid(CU::Vector2i aGridPosition)
{
	if(aGridPosition.myX >= 0 && aGridPosition.myX < GRIDSIZE_X)
	{
		if(aGridPosition.myY >= 0 && aGridPosition.myY < GRIDSIZE_Y)
		{
			return true;
		}

		return false;
	}

	return false;
}
