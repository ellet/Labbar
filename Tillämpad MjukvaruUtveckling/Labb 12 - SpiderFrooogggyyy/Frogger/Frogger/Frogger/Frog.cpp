#include "StdAfx.h"
#include "Frog.h"
#include "TileGrid.h"
#include "TimeManager.h"
#include "SpriteContainer.h"
#include "WaterEntity.h"
#include "WaterEntityHandler.h"
#include "Renderer.h"
#include "PhysicsManager.h"

FG::Frog::Frog()
{
	
}

FG::Frog::~Frog()
{
}

void FG::Frog::Init(HGE* aHGE)
{
    myHGE = aHGE;    

	myCurrentSprite = IDLE_UP_SPRITE;

	myStartTile = MainSingleton::GetInstance()->GetTileGrid()->GetGridTile(7,12);
    myCurrentTile = myStartTile;
	//myPosition.myX = myCurrentTile->myPosition.myX;
	//myPosition.myY = myCurrentTile->myPosition.myY;
	SetSize(CommonUtilities::Vector2f(0.f, 0.f));
	SetPosition(myCurrentTile->myPosition);

	myWalkingDirection .myX = 0;
	myWalkingDirection .myY = 0;

	myWalkTimer = WALK_TIME;
	myDeathTimer = DEATH_TIMER;
	myRespawnTimer = RESPAWN_TIME;
    myWalkCooldown = 0;

    myNumberOfLives = NR_OF_LIVES;
    myCurrentScore = 0;

	myCurrentWaterEntity = NULL;
	myWantToApplyWaterEntity = nullptr;

	myIsDead = false;
	myIReallyREAAAAALLYWantToDie = false;
	myIsRespawning = false;   
	myHasFoundHome = false;
	myHasRespawned = false;

	MainSingleton::GetInstance()->GetPhysicsManager().AddFrog(this);
}

void FG::Frog::ResetFrog()
{
	myCurrentScore = 0;
	myNumberOfLives = NR_OF_LIVES;
}

int FG::Frog::GetScore()
{
    return myCurrentScore;
}
    
void FG::Frog::AddScore(int aScoreNumber)
{
    myCurrentScore += aScoreNumber;
}

FG::Tile* FG::Frog::GetCurrentTile()
{
    return myCurrentTile;
}

bool FG::Frog::IsDead()
{
    return myIsDead;
	//return myIReallyREAAAAALLYWantToDie;
}

CU::Vector2f FG::Frog::GetPosition()
{
	return Entity::GetPosition();
}
    
void FG::Frog::Update()
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	HandleInput();
	//HandleWalk();
	HandleAnimation();
	HandleDeath();
	HandleRespawn();
}

void FG::Frog::HandleInput()
{
	if(myIsDead == false)
	{
		if(myWalkTimer == WALK_TIME)
		{
            myWalkCooldown -= myDeltaTime;
            if(myWalkCooldown <= 0)
            {
			    if(myHGE->Input_GetKeyState(HGEK_UP)) SetWalkDirection(CU::Vector2i(0,-1));
			    if(myHGE->Input_GetKeyState(HGEK_DOWN)) SetWalkDirection(CU::Vector2i(0,1));
			    if(myHGE->Input_GetKeyState(HGEK_RIGHT)) SetWalkDirection(CU::Vector2i(1,0));
			    if(myHGE->Input_GetKeyState(HGEK_LEFT)) SetWalkDirection(CU::Vector2i(-1,0));
                myWalkCooldown = WALK_COOLDOWN;
            }
		}
	}
}

bool FG::Frog::IsInsideWorld(CU::Vector2f& aPosition)
{
	if(aPosition.myX > 0 && aPosition.myX < (GRIDSIZE_X * TILESIZE))
	{
		if(aPosition.myY > 0 && aPosition.myY < (GRIDSIZE_Y * TILESIZE))
		{
			return true;
		}
	}

	return false;
}

void FG::Frog::SetWalkDirection(CU::Vector2i aDirection)
{
	myWalkingDirection = aDirection;
	//myDesiredPosition.myX = myPosition.myX + (myWalkingDirection.myX * TILESIZE);
	//myDesiredPosition.myY = myPosition.myY + (myWalkingDirection.myY * TILESIZE);

	myDesiredPosition.myX = GetPosition().myX + myWalkingDirection.myX * TILESIZE;
	myDesiredPosition.myY = GetPosition().myY + myWalkingDirection.myY * TILESIZE;
}

void FG::Frog::HandleWalk(const float aDeltaTime)
{
	HandleWaterEntityMovement(aDeltaTime);

	if(IsInsideWorld(myDesiredPosition))
	{
		if(myWalkingDirection.myX != 0 || myWalkingDirection.myY != 0)
		{
			myWalkTimer -= aDeltaTime;

			CommonUtilities::Vector2f tempPosition;
			tempPosition = GetPosition();
			
			tempPosition.myX += myWalkingDirection.myX * WALK_SPEED * aDeltaTime;
			tempPosition.myY += myWalkingDirection.myY * WALK_SPEED * aDeltaTime;

			SetMoveToPosition(tempPosition);

			if(myWantToApplyWaterEntity != NULL)
			{
				
				bool collided;
				myWantToApplyWaterEntity = MainSingleton::GetInstance()->GetWaterEntityHandler()->CheckForCollisionForDesiredPosition(myDesiredPosition, collided);
				if (collided)
				{
					myDesiredPosition = myWantToApplyWaterEntity->GetDesiredPositionFromTiles(myDesiredPosition);
				}
				/*else
				{
					myWantToApplyWaterEntity = NULL;
				}*/

				//	myDesiredPosition = myWantToApplyWaterEntity->GetDesiredPositionFromTiles(myDesiredPosition);
				
			}

			if(myWalkTimer <= 0)
			{
				ArriveAtTile();
			}
		}
	}
}

void FG::Frog::HandleWaterEntityMovement(const float aDeltaTime)
{
	if(myCurrentWaterEntity != nullptr)
	{		
		CommonUtilities::Vector2f tempPosition;
		tempPosition = GetPosition();
		tempPosition.myX += (myCurrentWaterEntity->GetVelocity().myX * aDeltaTime);
		SetMoveToPosition(tempPosition);
	}
}

void FG::Frog::ArriveAtTile()
{
	myWalkTimer = WALK_TIME;
	myCurrentTile = MainSingleton::GetInstance()->GetTileGrid()->GetGridTile(GetMoveToPosition().myX, GetMoveToPosition().myY);

	myWalkingDirection.myX = 0;
	myWalkingDirection.myY = 0;

	SetMoveToPosition(myDesiredPosition);
}

bool FG::Frog::HasRespawned()
{
	if(myHasRespawned)
	{
		myHasRespawned = false;
		return true;
	}
	return false;
}

void FG::Frog::HandleAnimation()
{
	if(myIsDead == false)
	{
		if(myWalkingDirection == CU::Vector2i(0,-1)) //UP
		{
			myCurrentSprite = IDLE_UP_SPRITE;
		}
		if(myWalkingDirection == CU::Vector2i(0,1)) //DOWN
		{
			myCurrentSprite = IDLE_DOWN_SPRITE;
		}
		if(myWalkingDirection == CU::Vector2i(-1,0)) //LEFT
		{
			myCurrentSprite = IDLE_LEFT_SPRITE;
		}
		if(myWalkingDirection == CU::Vector2i(1,0)) //RIGHT
		{
			myCurrentSprite = IDLE_RIGHT_SPRITE;
		}

		if(myWalkTimer > (WALK_TIME * 0.2f) && myWalkTimer < (WALK_TIME * 0.8f))
		{
			myCurrentSprite++;
		}
	}
	else
	{
		if(myDeathTimer < DEATH_TIMER * 0.5f)
		{
			myCurrentSprite = FROG_DEATH_1_SPRITE;
		}
		else
		{
			myCurrentSprite = FROG_DEATH_2_SPRITE;
		}
	}
}

void FG::Frog::SetFoundHome(bool aHasFoundHome)
{
	myHasFoundHome = aHasFoundHome;
}

bool FG::Frog::HasFoundHome()
{
	if(myHasFoundHome)
	{
		myHasFoundHome = false;
		return true;
	}

	return false;
}

void FG::Frog::KillFrog()
{
	myIsDead = true;
	myIReallyREAAAAALLYWantToDie = false;
	myNumberOfLives -= 1;
	myCurrentWaterEntity = NULL;
}

void FG::Frog::HandleDeath()
{
	if(myIsDead == false)
	{
		if(myCurrentTile != NULL)
		{
			if(myCurrentTile->myIsWater)
			{
				if(myCurrentWaterEntity == NULL)
				{
					Tile* tile = MainSingleton::GetInstance()->GetTileGrid()->GetGridTile(myDesiredPosition.myX, myDesiredPosition.myY);
					if(tile->myIsWater == true)
					{
						KillFrog();
					}
				}
				else
				{
					if(myCurrentWaterEntity->IsUnderWater())
					{
						KillFrog();
					}
				}
			}
		}

		if(GetPosition().myX < 0 || GetPosition().myX > SCREEN_RESOLUTION_X)
		{
			KillFrog();
		}
	}
	else
    {
		myDeathTimer -= myDeltaTime;
		
		if(myDeathTimer <= 0)
		{
			myDeathTimer = DEATH_TIMER;
			myIsRespawning = true;
		}
	}
}

void FG::Frog::HandleRespawn()
{
	if(myIsRespawning == true)
	{
		myRespawnTimer -= myDeltaTime;

		if(myRespawnTimer <= 0)
		{
			myIsDead = false;
			myIsRespawning = false;
			Respawn();
			myRespawnTimer = RESPAWN_TIME;
		}
	}
}

void FG::Frog::SetCurrentWaterEntity(WaterEntity* aWaterEntity)
{
	//myCurrentWaterEntity = aWaterEntity;
	myWantToApplyWaterEntity = aWaterEntity;
}

int FG::Frog::GetNumberOfLives()
{
    return myNumberOfLives;
}

void FG::Frog::Respawn()
{
	myHasRespawned = true;
	myCurrentTile = myStartTile;
	SetPosition(myCurrentTile->myPosition);
	myCurrentSprite = IDLE_UP_SPRITE;
}
    
void FG::Frog::Render()
{
	if(myIsRespawning == false)
	{
        SpriteType type = static_cast<SpriteType>(myCurrentSprite);
        //MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(type)->Render(myPosition.myX, myPosition.myY);		
		MainSingleton::GetInstance()->GetRenderer().AddRenderCommand(*MainSingleton::GetInstance()->GetSpriteContainer()->GetSprite(type), GetPosition());
	}
}

void FroggerGame::Frog::AlmostKilledFrog()
{
	myIReallyREAAAAALLYWantToDie = true;
}

void FroggerGame::Frog::PhysicsUpdate(const float aDeltaTime)
{
	HandleWalk(aDeltaTime);
}

void FroggerGame::Frog::ApplyPosition()
{
	Entity::ApplyPosition();
	myCurrentWaterEntity = myWantToApplyWaterEntity;
	if (myIReallyREAAAAALLYWantToDie == true)
	{
		KillFrog();
	}
}
