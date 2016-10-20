#include "StdAfx.h"
#include "VehicleHandler.h"
#include "Car.h"
#include "Bulldozer.h"
#include "Ferarri.h"
#include "Truck.h"
#include "Bus.h"
#include "MainSingleton.h"
#include "CommonMacros.h"
#include "Frog.h"

FG::VehicleHandler::VehicleHandler()
{
}

FG::VehicleHandler::~VehicleHandler()
{
}

void FG::VehicleHandler::Init(LevelData* someLevelData)
{
	myLevelData = someLevelData;

	InitVehicles();

	for(int index = 0; index < NUM_VEHICLE_TYPES; index++)
	{
		mySpawnTimers[index] = 0.0f;
	}
}

void FG::VehicleHandler::ReInit(LevelData* someLevelData)
{
	for(unsigned int index = 0; index < myAvailableVehicles.Count(); index++)
	{
		delete(myAvailableVehicles[index]);
	}

	myAvailableVehicles.RemoveAll();

	for(unsigned int index = 0; index < myVehiclesInGame.Count(); index++)
	{
		delete(myVehiclesInGame[index]);
	}

	myVehiclesInGame.RemoveAll();

	Init(someLevelData);
}
	
void FG::VehicleHandler::Update(Frog* aFrog)
{
	myDeltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CU::GAME_CLOCK).GetTime());

	for(unsigned int index = 0; index < myVehiclesInGame.Count(); index++)
	{
		myVehiclesInGame[index]->Update();
		if(myVehiclesInGame[index]->IsOutside())
		{
			myAvailableVehicles.Add(myVehiclesInGame[index]);
			myVehiclesInGame[index]->ReInit();
			myVehiclesInGame.RemoveCyclicAtIndex(index);			
		}
	}

	for(int index = 0; index < NUM_VEHICLE_TYPES; index++)
	{
		SpawnVehicle(static_cast<VehicleTypes>(index));
	}

	//CheckForCollision(aFrog);
}

void FG::VehicleHandler::CheckForCollision(Frog* aFrog)
{
	for(unsigned int index = 0; index < myVehiclesInGame.Count(); index++)
	{
		if(myVehiclesInGame[index]->HasCollided(aFrog->GetPosition(), 0))
		{
			if(aFrog->IsDead() == false)
			{
				aFrog->AlmostKilledFrog();
			}
		}
	}
}

void FG::VehicleHandler::Render()
{
	for(unsigned int index = 0; index < myVehiclesInGame.Count(); index++)
	{
		myVehiclesInGame[index]->Render();
	}
}

void FG::VehicleHandler::InitVehicles()
{
	for(int index = 0; index < myLevelData->myVehicleData[CAR].myMaxVehicles; index++)
	{
		Car* newCar = new Car();
		newCar->Init(CU::Vector2f(CAR_START_POS_X, CAR_START_POS_Y), myLevelData->myVehicleData[CAR].myMovementSpeed);
		myAvailableVehicles.Add(newCar);
	}

	for(int index = 0; index < myLevelData->myVehicleData[BULLDOZER].myMaxVehicles; index++)
	{
		Bulldozer* newBulldozer = new Bulldozer();
		newBulldozer->Init(CU::Vector2f(BULLDOZER_START_POS_X, BULLDOZER_START_POS_Y), myLevelData->myVehicleData[BULLDOZER].myMovementSpeed);
		myAvailableVehicles.Add(newBulldozer);
	}

	for(int index = 0; index < myLevelData->myVehicleData[FERARRI].myMaxVehicles; index++)
	{
		Ferarri* newFerarri = new Ferarri();
		newFerarri->Init(CU::Vector2f(FERARRI_START_POS_X, FERARRI_START_POS_Y), myLevelData->myVehicleData[FERARRI].myMovementSpeed);
		myAvailableVehicles.Add(newFerarri);
	}

	for(int index = 0; index < myLevelData->myVehicleData[TRUCK].myMaxVehicles; index++)
	{
		Truck* newTruck = new Truck();
		newTruck->Init(CU::Vector2f(TRUCK_START_POS_X, TRUCK_START_POS_Y), myLevelData->myVehicleData[TRUCK].myMovementSpeed);
		myAvailableVehicles.Add(newTruck);
	}

	for(int index = 0; index < myLevelData->myVehicleData[BUS].myMaxVehicles; index++)
	{
		Bus* newBus = new Bus();
		newBus->Init(CU::Vector2f(BUS_START_POS_X, BUS_START_POS_Y), myLevelData->myVehicleData[BUS].myMovementSpeed);
		myAvailableVehicles.Add(newBus);
	}
}

void FG::VehicleHandler::SpawnVehicle(VehicleTypes aType)
{
	mySpawnTimers[aType] -= myDeltaTime;
	if(mySpawnTimers[aType] <= 0)
	{
		Vehicle* temp = FindAndRemoveAvailableType(aType);
		if(temp != NULL)
		{
			temp->ReInit();
			myVehiclesInGame.Add(temp);
			int min = myLevelData->myVehicleData[aType].myRandomSpawnDimensions.myX;
			int max = myLevelData->myVehicleData[aType].myRandomSpawnDimensions.myY;
			mySpawnTimers[aType] = RANDOM_FLOAT(min, max);
		}
	}
}

FG::Vehicle* FG::VehicleHandler::FindAndRemoveAvailableType(VehicleTypes aType)
{
	for(unsigned int index = 0; index < myAvailableVehicles.Count(); index++)
	{
		if(myAvailableVehicles[index]->GetType() == aType)
		{
			Vehicle* temp = myAvailableVehicles[index];
			myAvailableVehicles.RemoveCyclicAtIndex(index);
			return temp;
		}
	}

	return NULL;
}
