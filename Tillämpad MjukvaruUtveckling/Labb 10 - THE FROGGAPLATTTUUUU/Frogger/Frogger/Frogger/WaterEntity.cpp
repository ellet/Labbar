#include "StdAfx.h"
#include "WaterEntity.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"

FG::WaterEntity::WaterEntity()
{
}

FG::WaterEntity::~WaterEntity()
{
	int apa = 10;
}

void FG::WaterEntity::Init(CU::Vector2f aPosition, WaterEntityTypes aType)
{
	myStartPosition = aPosition;
	myPosition = myStartPosition;
	myType = aType;
	myIsOutside = false;
    myIsUnderWater = false;

	InitTiles();
}

void FG::WaterEntity::InitTiles()
{
	for(int index = 0; index < myLength; index++)
	{
		myTiles.Add(CU::Vector2f(0,0));
	}
}

void FG::WaterEntity::ReInit()
{
	myPosition = myStartPosition;
	myIsOutside = false;
    myIsUnderWater = false;
}
	
void FG::WaterEntity::Update()
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	UpdateMovement();
	UpdateTiles();
	CheckIfOutside();
}

void FG::WaterEntity::UpdateTiles()
{
	CU::Vector2f pos = myPosition;
	pos.myX -= (myWidth * 0.5f);
	int index = 0;

	do
	{
		myTiles[index].myX = pos.myX+16;
		myTiles[index].myY = pos.myY;
		pos.myX += TILESIZE;
		index++;

	}while(index < myLength);
}

void FG::WaterEntity::UpdateMovement()
{
	myPosition.myX += myDirection.myX * myMovementSpeed * myDeltaTime;
}

CU::Vector2i FG::WaterEntity::GetDirection()
{
	return myDirection;
}

bool FG::WaterEntity::IsUnderWater()
{
	return myIsUnderWater;
}

float FG::WaterEntity::GetSpeed()
{
	return myMovementSpeed;
}

bool FG::WaterEntity::HasCollided(CU::Vector2f aPosition, float aWidth)
{
	if(aPosition.myX - aWidth > myPosition.myX - (myWidth * 0.5f) && 
		aPosition.myX + aWidth < myPosition.myX + (myWidth* 0.5f))
	{
		if(aPosition.myY - aWidth > myPosition.myY - mySprite->GetHeight() && 
		   aPosition.myY + aWidth < myPosition.myY + mySprite->GetHeight())
		{
			return true;
		}
	}
	
	return false;
}

CU::Vector2f FG::WaterEntity::GetDesiredPositionFromTiles(CU::Vector2f aPosition)
{
	float closestRange = 100000;
	int closestIndex = -1;

	for(unsigned int index = 0; index < myTiles.Count(); index++)
	{
		float length = (myTiles[index] - aPosition).Length();
		if(length < closestRange)
		{
			closestRange = length;
			closestIndex = index;
		}
	}

	return myTiles[closestIndex];
}

void FG::WaterEntity::CheckIfOutside()
{
	if(myDirection.myX == -1)
	{
		if(myPosition.myX + myWidth < 0)
		{
			myIsOutside = true;
		}
	}
	else
	{
		if(myPosition.myX - myWidth > SCREEN_RESOLUTION_X)
		{
			myIsOutside = true;
		}
	}
}
	
void FG::WaterEntity::Render()
{
	mySprite->Render(myPosition.myX, myPosition.myY);
}
