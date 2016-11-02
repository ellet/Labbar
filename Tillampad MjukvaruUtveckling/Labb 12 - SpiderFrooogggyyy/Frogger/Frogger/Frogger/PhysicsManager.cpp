#include "stdafx.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include "MainSingleton.h"
#include "Frog.h"
#include "WaterEntityHandler.h"
#include "VehicleHandler.h"

PhysicsManager::PhysicsManager()
{
	myActiveEntities = &myEntitiesBuffer1;
	myBuildEntities = &myEntitiesBuffer2;

	myBuffersSwitched = false;
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Update()
{
	myPhysicsWorkingLock.lock();
	
	

	float deltaTime = static_cast<float>(MainSingleton::GetInstance()->GetTimeManager()->GetElapsedTime(CommonUtilities::GAME_CLOCK).GetTime());


	for (unsigned int iEntity = 0; iEntity < myActiveEntities->Count(); iEntity++)
	{
		(*myActiveEntities)[iEntity]->PhysicsUpdate(deltaTime);
	}

	myVerySpecialFrog->PhysicsUpdate(deltaTime);

	MainSingleton::GetInstance()->GetWaterEntityHandler()->CheckForCollision(myVerySpecialFrog);
	MainSingleton::GetInstance()->GetVehicleHandler()->CheckForCollision(myVerySpecialFrog);

	myPhysicsWorkingLock.unlock();

	while (myBuffersSwitched == false);

	myBuffersSwitched = false;
}

void PhysicsManager::SwitchBuffers()
{
	std::lock_guard<std::mutex> tempLock(myPhysicsWorkingLock);

	std::swap(myBuildEntities, myActiveEntities);

	for (unsigned int iEntity = 0; iEntity < myBuildEntities->Count(); iEntity++)
	{
		(*myBuildEntities)[iEntity]->ApplyPosition();
	}

	myVerySpecialFrog->ApplyPosition();

	myBuildEntities->RemoveAll();

	myBuffersSwitched = true;
}

void PhysicsManager::AddEntity(Entity * aEntity)
{
	myBuildEntities->Add(aEntity);
}

void PhysicsManager::AddFrog(FroggerGame::Frog * aFrog)
{
	myVerySpecialFrog = aFrog;
}
