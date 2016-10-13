#include "StdAfx.h"
#include "WaterEntityHandler.h"
#include "Turtle.h"
#include "Log.h"
#include "MainSingleton.h"
#include "CommonMacros.h"
#include "Frog.h"

FG::WaterEntityHandler::WaterEntityHandler()
{
}

FG::WaterEntityHandler::~WaterEntityHandler()
{
}

void FG::WaterEntityHandler::Init(LevelData* someLevelData)
{	
	myLevelData = someLevelData;

    InitWaterEntitys();

    for(int index = 0; index < NUM_WATER_ENTITY_TYPES; index++)
	{
		mySpawnTimers[index] = 0.0f;
	}
}

void FG::WaterEntityHandler::ReInit(LevelData* someLevelData)
{
	for(unsigned int index = 0; index < myAvailableWaterEntitys.Count(); index++)
	{
		delete(myAvailableWaterEntitys[index]);
	}

	myAvailableWaterEntitys.RemoveAll();

	for(unsigned int index = 0; index < myWaterEntitysIngame.Count(); index++)
	{
		delete(myWaterEntitysIngame[index]);
	}

	myWaterEntitysIngame.RemoveAll();

	Init(someLevelData);
}

void FG::WaterEntityHandler::InitWaterEntitys()
{
    for(int index = 0; index < myLevelData->myWaterEntityData[SMALL_TURTLE].myMaxWaterEntitys; index++)
    {
        Turtle* newTurtle = new Turtle();
		float speed = myLevelData->myWaterEntityData[SMALL_TURTLE].myMovementSpeed;
        newTurtle->Init(CU::Vector2f(SMALL_TURTLE_START_POS_X, SMALL_TURTLE_START_POS_Y), SMALL_TURTLE, true, speed);
        myAvailableWaterEntitys.Add(newTurtle);
    }

    for(int index = 0; index < myLevelData->myWaterEntityData[BIG_TURTLE].myMaxWaterEntitys; index++)
    {
        Turtle* newTurtle = new Turtle();
		float speed = myLevelData->myWaterEntityData[BIG_TURTLE].myMovementSpeed;
        newTurtle->Init(CU::Vector2f(BIG_TURTLE_START_POS_X, BIG_TURTLE_START_POS_Y), BIG_TURTLE, true, speed);
        myAvailableWaterEntitys.Add(newTurtle);
    }

    for(int index = 0; index < myLevelData->myWaterEntityData[SMALL_LOG].myMaxWaterEntitys; index++)
    {
        Log* newLog = new Log();
		float speed = myLevelData->myWaterEntityData[SMALL_LOG].myMovementSpeed;
        newLog->Init(CU::Vector2f(SMALL_LOG_START_POS_X, SMALL_LOG_START_POS_Y), SMALL_LOG, speed);
        myAvailableWaterEntitys.Add(newLog);
    }

    for(int index = 0; index < myLevelData->myWaterEntityData[MEDIUM_LOG].myMaxWaterEntitys; index++)
    {
        Log* newLog = new Log();
		float speed = myLevelData->myWaterEntityData[MEDIUM_LOG].myMovementSpeed;
        newLog->Init(CU::Vector2f(MEDIUM_LOG_START_POS_X, MEDIUM_LOG_START_POS_Y), MEDIUM_LOG, speed);
        myAvailableWaterEntitys.Add(newLog);
    }

    for(int index = 0; index < myLevelData->myWaterEntityData[BIG_LOG].myMaxWaterEntitys; index++)
    {
        Log* newLog = new Log();
		float speed = myLevelData->myWaterEntityData[BIG_LOG].myMovementSpeed;
        newLog->Init(CU::Vector2f(BIG_LOG_START_POS_X, BIG_LOG_START_POS_Y), BIG_LOG, speed);
        myAvailableWaterEntitys.Add(newLog);
    }
}

void FG::WaterEntityHandler::Update(Frog* aFrog)
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	for(unsigned int index = 0; index < myWaterEntitysIngame.Count(); index++)
	{
		myWaterEntitysIngame[index]->Update();
		if(myWaterEntitysIngame[index]->IsOutside())
		{
			myAvailableWaterEntitys.Add(myWaterEntitysIngame[index]);
			myWaterEntitysIngame[index]->ReInit();
			myWaterEntitysIngame.RemoveCyclicAtIndex(index);			
		}
	}

    for(int index = 0; index < NUM_WATER_ENTITY_TYPES; index++)
	{
		SpawnWaterEntity(static_cast<WaterEntityTypes>(index));
	}

	//CheckForCollision(aFrog);
}

FG::WaterEntity* FG::WaterEntityHandler::CheckForCollisionForDesiredPosition(CU::Vector2f aDesiredPosition, bool& aHasCollided)
{
	for(unsigned int index = 0; index < myWaterEntitysIngame.Count(); index++)
	{
		if(myWaterEntitysIngame[index]->HasCollided(aDesiredPosition, 0))
		{
			aHasCollided = true;
			return myWaterEntitysIngame[index];
		}
	}

	aHasCollided = false;
	return NULL;
}

void FG::WaterEntityHandler::CheckForCollision(Frog* aFrog)
{	
	aFrog->SetCurrentWaterEntity(NULL);

	for(unsigned int index = 0; index < myWaterEntitysIngame.Count(); index++)
	{
		if(myWaterEntitysIngame[index]->HasCollided(aFrog->GetPosition(), 0))
		{
			aFrog->SetCurrentWaterEntity(myWaterEntitysIngame[index]);
		}
	}
}

void FG::WaterEntityHandler::SpawnWaterEntity(WaterEntityTypes aType)
{
    mySpawnTimers[aType] -= myDeltaTime;
	if(mySpawnTimers[aType] <= 0)
	{
		WaterEntity* temp = FindAndRemoveAvailableType(aType);
		if(temp != NULL)
		{
            temp->ReInit();

			myWaterEntitysIngame.Add(temp);
			int min = myLevelData->myWaterEntityData[aType].myRandomSpawnDimensions.myX;
			int max = myLevelData->myWaterEntityData[aType].myRandomSpawnDimensions.myY;
			mySpawnTimers[aType] = RANDOM_FLOAT(min, max);
		}
	}
}

FG::WaterEntity* FG::WaterEntityHandler::FindAndRemoveAvailableType(WaterEntityTypes aType)
{
    for(unsigned int index = 0; index < myAvailableWaterEntitys.Count(); index++)
	{
		if(myAvailableWaterEntitys[index]->GetType() == aType)
		{
			WaterEntity* temp = myAvailableWaterEntitys[index];
			myAvailableWaterEntitys.RemoveCyclicAtIndex(index);
			return temp;
		}
	}

	return NULL;
}
	
void FG::WaterEntityHandler::Render()
{
	for(unsigned int index = 0; index < myWaterEntitysIngame.Count(); index++)
	{
		myWaterEntitysIngame[index]->Render();
	}
}
