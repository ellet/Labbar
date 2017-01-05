#include "stdafx.h"
#include "PhysicsScene.h"



namespace SP
{

	PhysicsScene::PhysicsScene()
	{
		physx::PxSceneDesc sceneDesc(CreationManager::GetPhysicsSystem().getTolerancesScale());
		sceneDesc.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
		sceneDesc.cpuDispatcher = &CreationManager::GetDispatcher();		
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
		myScene =  CreationManager::GetPhysicsSystem().createScene(sceneDesc);
	}

	PhysicsScene::~PhysicsScene()
	{
	}

	void PhysicsScene::AddActor(BaseActor & aActorToAdd)
	{
		myScene->addActor(aActorToAdd.GetActor());
	}

	void PhysicsScene::Update(const SB::Time & aDeltaTime)
	{
		myScene->simulate(aDeltaTime.InSeconds());
		myScene->fetchResults(true);
	}

}
