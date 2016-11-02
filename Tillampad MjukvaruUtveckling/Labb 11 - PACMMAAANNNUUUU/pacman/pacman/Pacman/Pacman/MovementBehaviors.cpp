#include "MovementBehaviors.h"

#include "Player.h"
#include "TileGrid.h"
#include "TI_TimeManager.h"


MovementBehaviors::MovementBehaviors()
{
}

MovementBehaviors::~MovementBehaviors()
{
}

void MovementBehaviors::Init(CU::Vector2f& aPosition)
{
	myPosition = &aPosition;
	myOriginalPosition = aPosition;
	mySpeed = 150.0f;

	myDirections[MOVE_UP].Set(0,-1);
	myDirections[MOVE_DOWN].Set(0,1);
	myDirections[MOVE_LEFT].Set(-1,0);
	myDirections[MOVE_RIGHT].Set(1,0);

	myVelocity.Set(0,0);
	myWalkable.Init(4,10);
}

void MovementBehaviors::MoveRandom()
{
	float elapsedTime = static_cast<float>(TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime());
	CU::Vector2f moveToPos = myDestination;
	moveToPos -= *myPosition;

	if(moveToPos.Length() < elapsedTime * mySpeed)
	{
		NewDirection();
	}
	else
	{
		moveToPos.Normalize();
		myPosition->x += moveToPos.myX * mySpeed * elapsedTime;
		myPosition->y += moveToPos.myY * mySpeed * elapsedTime;
	}
}

bool MovementBehaviors::MoveHome()
{
	if(myWaypoints.Count() == 0)
	{
		myWaypoints.RemoveAll();
		FindNewWaypoints(CU::Vector2f(325,350));
	}
	
	float elapsedTime = static_cast<float>(TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime());
	CU::Vector2f moveToPos(TileGrid::GetInstance()->GetPixelFromTile(myWaypoints[myWaypoints.Count()-1]));
	moveToPos.myX += 12.5f;
	moveToPos.myY += 12.5f;

	moveToPos -= *myPosition;

	if(moveToPos.Length() < elapsedTime * mySpeed)
	{
		myWaypoints.RemoveCyclicAtIndex(myWaypoints.Count()-1);
	}
	else
	{
		moveToPos.Normalize();
		myPosition->x += moveToPos.myX * mySpeed * elapsedTime;
		myPosition->y += moveToPos.myY * mySpeed * elapsedTime;
	}

	if(myWaypoints.Count() == 0)
	{
		return true;
	}

	return false;
}

bool MovementBehaviors::MoveToPlayer(Player& aPlayer)
{
	if(myWaypoints.Count() == 0)
	{
		myWaypoints.RemoveAll();
		FindNewWaypoints(aPlayer.GetPosition());
	}
	
	float elapsedTime = static_cast<float>(TI_Time::TimeManager::GetInstance()->GetElapsedTime(TI_Time::GAME_CLOCK_01).GetTime());
	CU::Vector2f moveToPos(TileGrid::GetInstance()->GetPixelFromTile(myWaypoints[myWaypoints.Count()-1]));
	moveToPos.myX += 12.5f;
	moveToPos.myY += 12.5f;

	moveToPos -= *myPosition;

	if(moveToPos.Length() < elapsedTime * mySpeed)
	{
		myWaypoints.RemoveCyclicAtIndex(myWaypoints.Count()-1);
	}
	else
	{
		moveToPos.Normalize();
		myPosition->x += moveToPos.myX * mySpeed * elapsedTime;
		myPosition->y += moveToPos.myY * mySpeed * elapsedTime;
	}

	return false;
}

void MovementBehaviors::PortalThePlayer()
{
	if(myPosition->x < 0 && myVelocity.x == -1)
	{
		myPosition->x = 650;
		NewDirection();
	}
	else if(myPosition->x > 650 && myVelocity.x == 1)
	{
		myPosition->x = 0;
		NewDirection();
	}
}

void MovementBehaviors::NewDirection()
{
	if(TileGrid::GetInstance()->IsTileWalkable(*myPosition,myDirections[MOVE_UP])
		&& myVelocity.y != 1)
	{
		myWalkable.Add(myDirections[MOVE_UP]);
	}
	if(TileGrid::GetInstance()->IsTileWalkable(*myPosition,myDirections[MOVE_LEFT])
		&& myVelocity.x != 1)
	{
		myWalkable.Add(myDirections[MOVE_LEFT]);
	}
	if(TileGrid::GetInstance()->IsTileWalkable(*myPosition,myDirections[MOVE_RIGHT])
		&& myVelocity.x != -1)
	{
		myWalkable.Add(myDirections[MOVE_RIGHT]);
	}
	if(TileGrid::GetInstance()->IsTileWalkable(*myPosition,myDirections[MOVE_DOWN])
		&& myVelocity.y != -1)
	{
		myWalkable.Add(myDirections[MOVE_DOWN]);
	}

	if(myWalkable.Count() > 1)
	{
		int index = rand()%myWalkable.Count();
		myVelocity = myWalkable[index];
		myDestination = TileGrid::GetInstance()->GetTileFromPixel(*myPosition);
		myDestination.x = static_cast<int>(myDestination.x);
		myDestination.y = static_cast<int>(myDestination.y);
		myDestination += myWalkable[index];
		myDestination = TileGrid::GetInstance()->GetPixelFromTile(myDestination);
		myDestination += 12.5f;
	}
	else 
	{
		if (myWalkable.Count() > 0)
		{
			myVelocity = myWalkable[0];
			myDestination = TileGrid::GetInstance()->GetTileFromPixel(*myPosition);
			myDestination.x = static_cast<int>(myDestination.x);
			myDestination.y = static_cast<int>(myDestination.y);
			myDestination += myWalkable[0];
			myDestination = TileGrid::GetInstance()->GetPixelFromTile(myDestination);
			myDestination += 12.5f;
		}
		else
		{
			// Something went wrong
			myPosition = &myOriginalPosition;
			FindNewWaypoints(CU::Vector2f(325, 350));
		}

	}

	myWalkable.RemoveAll();
}

void MovementBehaviors::FindNewWaypoints( CU::Vector2f aEndPosition )
{
	CU::Vector2f startTilePosition = TileGrid::GetInstance()->GetTileFromPixel(*myPosition);
	CU::Vector2f endTilePosition = TileGrid::GetInstance()->GetTileFromPixel(aEndPosition);
	myWaypoints = TileGrid::GetInstance()->GetPath(startTilePosition,endTilePosition);
}

void MovementBehaviors::SetSpeed( float aSpeed )
{
	mySpeed = aSpeed;
}

void MovementBehaviors::ResetWaypoints()
{
	myWaypoints.RemoveAll();
}