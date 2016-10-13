#include "StdAfx.h"
#include "Vehicle.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"

FG::Vehicle::Vehicle()
{
}

FG::Vehicle::~Vehicle()
{
}

void FG::Vehicle::Init(CU::Vector2f aPosition, VehicleTypes aType)
{
	myStartPosition = aPosition;
	myPosition = myStartPosition;
	myType = aType;
	myIsOutside = false;
}

void FG::Vehicle::ReInit()
{
	myPosition = myStartPosition;
	myIsOutside = false;
}
	
void FG::Vehicle::Update()
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	UpdateMovement();
	CheckIfOutside();
}

void FG::Vehicle::UpdateMovement()
{
	myPosition.myX += myDirection.myX * myMovementSpeed * myDeltaTime;
	myCurrentTile = MainSingleton::GetInstance()->GetTileGrid()->GetGridTile(myPosition.myX, myPosition.myY);
}

void FG::Vehicle::CheckIfOutside()
{
	if(myDirection.myX == -1)
	{
		if(myPosition.myX + (TILESIZE * myWidth) < 0)
		{
			myIsOutside = true;
		}
	}
	else
	{
		if(myPosition.myX - (TILESIZE * myWidth) > SCREEN_RESOLUTION_X)
		{
			myIsOutside = true;
		}
	}
}

bool FG::Vehicle::HasCollided(CU::Vector2f aPosition, float aWidth)
{
	if(aPosition.myX - aWidth > myPosition.myX - mySprite->GetWidth() * 0.5f && 
		aPosition.myX + aWidth < myPosition.myX + mySprite->GetWidth() * 0.5f)
	{
		if(aPosition.myY - aWidth > myPosition.myY - mySprite->GetHeight() && 
		   aPosition.myY + aWidth < myPosition.myY + mySprite->GetHeight())
		{
			return true;
		}
	}
	
	return false;
}
	
void FG::Vehicle::Render()
{
	mySprite->Render(myPosition.myX, myPosition.myY);
}
