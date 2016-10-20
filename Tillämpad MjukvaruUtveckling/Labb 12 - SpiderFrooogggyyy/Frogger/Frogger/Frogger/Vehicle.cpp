#include "StdAfx.h"
#include "Vehicle.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"
#include "Renderer.h"
#include "PhysicsManager.h"

FG::Vehicle::Vehicle()
{
}

FG::Vehicle::~Vehicle()
{
}

void FG::Vehicle::Init(CU::Vector2f aPosition, VehicleTypes aType)
{
	myStartPosition = aPosition;
	SetPosition(myStartPosition);
	myType = aType;
	myIsOutside = false;
}

void FG::Vehicle::ReInit()
{
	//myPosition = myStartPosition;
	SetPosition(myStartPosition);
	myIsOutside = false;
}
	
void FG::Vehicle::Update()
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	MainSingleton::GetInstance()->GetPhysicsManager().AddEntity(this);

	//UpdateMovement();
	CheckIfOutside();
}

//void FG::Vehicle::UpdateMovement()
//{
//	//myPosition.myX += myDirection.myX * myMovementSpeed * myDeltaTime;
//	CommonUtilities::Vector2f tempPosition;
//	tempPosition = GetPosition();
//	tempPosition.myX += GetVelocity().myX * myDeltaTime;
//	SetPosition(tempPosition);
//
//	myCurrentTile = MainSingleton::GetInstance()->GetTileGrid()->GetGridTile(GetPosition().myX, GetPosition().myY);
//}

void FG::Vehicle::CheckIfOutside()
{
	if(GetVelocity().myX < 0.f)
	{
		if(GetPosition().myX + (GetSize().myX) < 0)
		{
			myIsOutside = true;
		}
	}
	else
	{
		if(GetPosition().myX - (GetSize().myX) > SCREEN_RESOLUTION_X)
		{
			myIsOutside = true;
		}
	}
}

bool FG::Vehicle::HasCollided(CU::Vector2f aPosition, float aWidth)
{
	if(aPosition.myX - aWidth > GetPosition().myX - mySprite->GetWidth() * 0.5f && 
		aPosition.myX + aWidth < GetPosition().myX + mySprite->GetWidth() * 0.5f)
	{
		if(aPosition.myY - aWidth > GetPosition().myY - mySprite->GetHeight() &&
		   aPosition.myY + aWidth < GetPosition().myY + mySprite->GetHeight())
		{
			return true;
		}
	}
	
	return false;
}
	
void FG::Vehicle::Render()
{
	//mySprite->Render(myPosition.myX, myPosition.myY);
	MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*mySprite, GetPosition());
}
