#include "stdafx.h"
#include "SceneSystems.h"

namespace SB
{

	SceneSystems::SceneSystems()
	{
		myPhysicsManager = std::make_unique<SP::PhysicsManager>();
	}


	SceneSystems::~SceneSystems()
	{
	}

	void SceneSystems::Update(const Time & aDeltaTime)
	{
		myPhysicsManager->Update(aDeltaTime.InSeconds());
	}

	void SceneSystems::Render()
	{

	}

	SP::PhysicsManager & SceneSystems::GetPhysicsManager()
	{
		return *myPhysicsManager;
	}

}
