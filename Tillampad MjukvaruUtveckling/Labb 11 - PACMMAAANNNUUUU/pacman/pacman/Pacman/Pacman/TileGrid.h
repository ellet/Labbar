#ifndef TILE_GRID_HEADER
#define TILE_GRID_HEADER

#include "Astar.h"
#include "GrowingArray.h"
#include "CU_Vector.h"

#include "VisualRep.h"


class TileGrid
{
	public:
		static void Create();
		static TileGrid* GetInstance();
		void Render();
		void SetTilePassable(CU::Vector2f aTile, bool aFlag);
		const CU::GrowingArray<bool>& GetTileGrid();
		const CU::GrowingArray<bool>& GetCreepGrid();
		CU::Vector2f GetTileFromPixel(CU::Vector2f aPixelPosition);
		CU::Vector2f GetPixelFromTile(CU::Vector2f aTilePosition);
		bool IsTileWalkable(const CU::Vector2f& aPixelPosition, CU::Vector2f aDirection);
		bool IsWalkable(const CU::Vector2f& aPixelPosition);
		const CU::GrowingArray<CU::Vector2f>& GetPath(const CU::Vector2f& aStartTile, const CU::Vector2f& aEndTile );
		void SetEditorMode(bool aFlag);
		const int& GetRowSize();
		const int& GetTileSize();
	private:
		TileGrid();
		~TileGrid();
		static TileGrid* myInstance;
		void LoadTileGrid();
		int GetTileIndex(const CU::Vector2f& aPixelPosition, CU::Vector2f aDirection);
		CU::GrowingArray<bool> myTileGrid;
		Astar* myAstar;
		VisualRep myBlockRep;
		VisualRep myWalkRep;
		VisualRep myBigDotRep;
		VisualRep mySmalDotRep;

		int myTileSize;
		int myRowSize;
		int myColSize;
		int myTilesGridSize;
	};


#endif