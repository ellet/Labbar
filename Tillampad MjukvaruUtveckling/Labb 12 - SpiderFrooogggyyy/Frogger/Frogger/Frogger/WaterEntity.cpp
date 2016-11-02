#include "StdAfx.h"
#include "WaterEntity.h"
#include "MainSingleton.h"
#include "TileGrid.h"
#include "SpriteContainer.h"
#include "Renderer.h"
#include "PhysicsManager.h"

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
	SetPosition(myStartPosition);
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
	SetPosition(myStartPosition);
	myIsOutside = false;
    myIsUnderWater = false;
}
	
void FG::WaterEntity::Update()
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	MainSingleton::GetInstance()->GetPhysicsManager().AddEntity(this);

	//UpdateMovement();
	UpdateTiles();
	CheckIfOutside();
}

void FG::WaterEntity::UpdateTiles()
{
	CU::Vector2f pos = GetPosition();
	pos.myX -= (GetSize().myX * 0.5f);
	int index = 0;

	do
	{
		myTiles[index].myX = pos.myX+16;
		myTiles[index].myY = pos.myY;
		pos.myX += TILESIZE;
		index++;

	}while(index < myLength);
}

//void FG::WaterEntity::UpdateMovement()
//{
	//myPosition.myX += myDirection.myX * myMovementSpeed * myDeltaTime;
	//CommonUtilities::Vector2f tempPosition;
	//tempPosition = GetPosition();
	//tempPosition.myX += GetVelocity().myX * myDeltaTime;

	////SetMoveToPosition(tempPosition);
	//SetPosition(tempPosition);
//}

//CU::Vector2i FG::WaterEntity::GetDirection()
//{
//	CommonUtilities::Vector2f temp(GetVelocity());
//
//	temp.Normalize();
//
//	return CommonUtilities::Vector2i(static_cast<int>(temp.myX), static_cast<int>(temp.myY));
//}

bool FG::WaterEntity::IsUnderWater()
{
	return myIsUnderWater;
}

//float FG::WaterEntity::GetSpeed()
//{
//	return GetVelocity().myX;
//}

bool FG::WaterEntity::HasCollided(CU::Vector2f aPosition, float aWidth)
{
	if(aPosition.myX - aWidth > GetMoveToPosition().myX - (GetSize().myX * 0.5f) && 
		aPosition.myX + aWidth < GetMoveToPosition().myX + (GetSize().myX * 0.5f))
	{
		if(aPosition.myY - aWidth > GetMoveToPosition().myY - GetSize().myY * 0.5f &&
		   aPosition.myY + aWidth < GetMoveToPosition().myY + GetSize().myY* 0.5f)
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
	if(GetVelocity().myX < 0.f)
	{
		if(GetPosition().myX + GetSize().myX < 0)
		{
			myIsOutside = true;
		}
	}
	else
	{
		if(GetPosition().myX - GetSize().myX > SCREEN_RESOLUTION_X)
		{
			myIsOutside = true;
		}
	}
}
	
void FG::WaterEntity::Render()
{
	//mySprite->Render(myPosition.myX, myPosition.myY);
	MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*mySprite, GetPosition());
}
