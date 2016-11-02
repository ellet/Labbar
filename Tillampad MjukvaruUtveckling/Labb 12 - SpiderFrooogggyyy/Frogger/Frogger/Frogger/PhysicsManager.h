#pragma once
#include "GrowingArray.h"
#include <mutex>
#include <atomic>

class Entity;

namespace FroggerGame
{

	class Frog;
}

class PhysicsManager
{


public:
	PhysicsManager();
	~PhysicsManager();

	void Update();

	void SwitchBuffers();

	void AddEntity(Entity * aEntity);
	void AddFrog(FroggerGame::Frog * aFrog);

private:
	std::mutex myPhysicsWorkingLock;
	std::atomic<bool> myBuffersSwitched;

	CommonUtilities::GrowingArray<Entity*> * myActiveEntities;
	CommonUtilities::GrowingArray<Entity*> * myBuildEntities;

	CommonUtilities::GrowingArray<Entity*> myEntitiesBuffer1;
	CommonUtilities::GrowingArray<Entity*> myEntitiesBuffer2;

	FroggerGame::Frog * myVerySpecialFrog;
};

