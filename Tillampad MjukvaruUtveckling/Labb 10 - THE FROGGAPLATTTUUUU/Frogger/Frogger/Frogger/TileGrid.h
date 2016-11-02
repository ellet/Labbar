#ifndef TILE_GRID_HEADER
#define TILE_GRID_HEADER

#include "defines.h"
#include "namespaces.h"
#include "Vector2.h"
#include "StaticArray.h"

namespace FroggerGame
{
    struct Tile
    {
        CU::Vector2f myPosition;   
		bool myIsWater;
    };

    class TileGrid
    {

    public:

        TileGrid(); 
        ~TileGrid();        
        void Init();
		CU::StaticArray<CU::StaticArray<Tile, GRIDSIZE_Y>, GRIDSIZE_X>& GetTileSet() {return myTileSet;}
        FG::Tile* GetGridTile(int aX, int aY);
		FG::Tile* GetGridTile(float aX, float aY);
		FG::Tile* GetNextTile(FG::Tile* aCurrentTile, CU::Vector2i aDirection);

    private:
               
		bool TileInsideGrid(CU::Vector2i aGridPosition);
        CU::StaticArray<CU::StaticArray<Tile, GRIDSIZE_Y>, GRIDSIZE_X> myTileSet;
    };
};

#endif
