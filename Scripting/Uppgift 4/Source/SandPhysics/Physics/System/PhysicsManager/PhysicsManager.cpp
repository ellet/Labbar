#include "stdafx.h"
#include "PhysicsManager.h"

namespace SP
{

	PhysicsManager::PhysicsManager()
	{
		myScene = std::make_unique<PhysicsScene>();
	}

	PhysicsManager::~PhysicsManager()
	{
	}

	void PhysicsManager::AddActor(BaseActor & aAcotr)
	{
		myScene->AddActor(aAcotr);
	}

	void PhysicsManager::Update(const SB::Time & aDeltaTime)
	{
		myScene->Update(aDeltaTime);
	}

}

