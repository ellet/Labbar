//#include "StdAfx.h"
#include "TileGrid.h"


const int locTILESIZE = 25;
const int locRowSize = 27;
const int locColSize = 29;

TileGrid* TileGrid::myInstance = NULL;


TileGrid::TileGrid()
{
	myTilesGridSize = locRowSize*locColSize;
	myTileSize = locTILESIZE;
	myRowSize = locRowSize;
	myColSize = locColSize;

	myTileGrid.Init(900,100);
	LoadTileGrid();
	
	myAstar = new Astar(myTileGrid,locRowSize,locColSize);

	myBlockRep.Init("Data/blockTile.png");
	myWalkRep.Init("Data/walkTile.png");

	myBigDotRep.Init("Data/bigDot.png");
	mySmalDotRep.Init("Data/smalDot.png");

}

TileGrid::~TileGrid()
{
}

void TileGrid::Create()
{
	myInstance = new TileGrid();
}

TileGrid* TileGrid::GetInstance()
{
	return myInstance;
}


const CU::GrowingArray<bool>& TileGrid::GetTileGrid()
{
 	return myTileGrid;
}

CU::Vector2f TileGrid::GetTileFromPixel(const CU::Vector2f aPixelPosition)
{
	return CU::Vector2f(aPixelPosition.myX/locTILESIZE, aPixelPosition.myY/locTILESIZE);
}

CU::Vector2f TileGrid::GetPixelFromTile(const CU::Vector2f aTilePosition )
{
	return CU::Vector2f(aTilePosition.myX*locTILESIZE, aTilePosition.myY*locTILESIZE);
}

const CU::GrowingArray<CU::Vector2f>& TileGrid::GetPath(const CU::Vector2f& aStartTile, const CU::Vector2f& aEndTile )
{
	return myAstar->GetPath(aStartTile,aEndTile);
}

void TileGrid::Render()
{
	CU::Vector2f TilePosition(0,0);
	CU::Vector2f PixelPos(0,0);

	for(int i = 0; i < myTilesGridSize; i++)
	{
		PixelPos = GetPixelFromTile(TilePosition);

		if(myTileGrid[i] == true)
		{
			myWalkRep.Render(PixelPos);
		}
		else
		{
			myBlockRep.Render(PixelPos);
		}

		TilePosition.myX++;
		if(TilePosition.myX == locRowSize)
		{
			TilePosition.myX = 0;
			TilePosition.myY++;
		}
	}
}


const int& TileGrid::GetRowSize()
{
	return myRowSize;
}

const int& TileGrid::GetTileSize()
{
	return myTileSize;
}


void TileGrid::LoadTileGrid()
{
	FILE* myFile;
	fopen_s(&myFile,"level.txt","r");

	unsigned char input;
	bool found=true;
	do {
		if(fread(&input,1,1,myFile)!=1)
		{
			return;
		}
		found=false;
		
		if(input == 'E')
		{
			return;
		}

		if(input == 'b')
		{
			myTileGrid.Add(false);
		}
		else if(input !=10)
		{
			myTileGrid.Add(true);
		}
		

	} while (input != 'E'|| (found==true));
	 
	 fclose(myFile);

}

bool TileGrid::IsTileWalkable( const CU::Vector2f& aPixelPosition, CU::Vector2f aDirection )
{
	int index = GetTileIndex(aPixelPosition, aDirection);

	return myTileGrid[index];

}

bool TileGrid::IsWalkable( const CU::Vector2f& aPixelPosition )
{
	int index = GetTileIndex(aPixelPosition, CU::Vector2f(0,0));
	return myTileGrid[index];
}
int TileGrid::GetTileIndex( const CU::Vector2f& aPixelPosition, CU::Vector2f aDirection )
{
	CU::Vector2f tilePos = GetTileFromPixel(aPixelPosition);
	return static_cast<int>(tilePos.myX+aDirection.x) + static_cast<int>(tilePos.myY+aDirection.y)*myRowSize;

}

