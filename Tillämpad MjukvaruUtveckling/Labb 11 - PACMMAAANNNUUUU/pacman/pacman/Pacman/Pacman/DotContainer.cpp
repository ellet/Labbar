#include "DotContainer.h"
#include "TileGrid.h"

#include "Player.h"
#include "ScoreCounter.h"

DotContainer::DotContainer()
{
}

DotContainer::~DotContainer()
{
	for(int i = 0; i < myDotGrid.Count(); i++)
	{
		if(myDotGrid[i] != NULL)
		{
			delete myDotGrid[i];
			myDotGrid[i] = NULL;
		}
	}
}

void DotContainer::Init()
{
	myDotGrid.Init(900,100);
	LoadDotGrid();
}

void DotContainer::Update(Player& aPlayer, ScoreCounter& aScoreCounter)
{
	CU::Vector2f tilePosition = TileGrid::GetInstance()->GetTileFromPixel(aPlayer.GetPosition());
	int tileIndex = static_cast<int>(tilePosition.x) + static_cast<int>(tilePosition.y)*TileGrid::GetInstance()->GetRowSize()/*+1*/;

	if(myDotGrid[tileIndex]!= NULL)
	{
		if(myDotGrid[tileIndex]->GetIsBigDot() == true)
		{
			aPlayer.SetIsInvincible(true);
			aScoreCounter.AddScore(50);
		}
		else
		{
			aScoreCounter.AddScore(10);
		}
		myDotsLeft--;
		delete myDotGrid[tileIndex];
		myDotGrid[tileIndex] = NULL;
	}

}

void DotContainer::Render()
{
	for(int i = 0; i < myDotGrid.Count(); i++)
	{
		if(myDotGrid[i]!= NULL)
		{
			myDotGrid[i]->Render();
		}
	}
}

void DotContainer::LoadDotGrid()
{
	myDotsLeft = 0;
	FILE* myFile;
	fopen_s(&myFile,"level.txt","r");

	CU::Vector2f TilePosition(0,0);
	CU::Vector2f PixelPos(0,0);

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

 		if(input == 'o')
 		{
			myDotsLeft++;
			Dot* dot = new Dot();
			CU::Vector2f position = TileGrid::GetInstance()->GetPixelFromTile(TilePosition);
			dot->Init(position,false);
 			myDotGrid.Add(dot);
 		}
 		else if(input == 'O')
 		{
			myDotsLeft++;
			Dot* dot = new Dot();
			CU::Vector2f position = TileGrid::GetInstance()->GetPixelFromTile(TilePosition);
			dot->Init(position,true);
			myDotGrid.Add(dot);
 		}
		else if(input != 10)
		{
			myDotGrid.Add(NULL);
		}

		if(input != 10)
		{
			
			TilePosition.myX++;
			if(TilePosition.myX == TileGrid::GetInstance()->GetRowSize())
			{
				TilePosition.myX = 0;
				TilePosition.myY++;
			}
		}
		


	} while (input != 'E'|| (found==true));

	fclose(myFile);

}

int DotContainer::GetDotsLeft()
{
	return myDotsLeft;
}