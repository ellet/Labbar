#include "stdafx.h"
#include "CreationManager.h"
#include "extensions\PxDefaultErrorCallback.h"
#include "extensions\PxDefaultAllocator.h"
#include "foundation\PxFoundation.h"
#include "physxprofilesdk\PxProfileZoneManager.h"
#include "common\PxTolerancesScale.h"
#include "PxPhysics.h"
#include "pvd\PxVisualDebugger.h"
#include "..\..\PhysxIncludes\extensions\PxVisualDebuggerExt.h"
#include "..\..\PhysxIncludes\extensions\PxDefaultCpuDispatcher.h"
#include "..\PhysicsErrorCallback.h"



namespace SP
{
	CreationManager * CreationManager::ourInstance = nullptr;

	void CreationManager::Create()
	{
		if (ourInstance != nullptr)
		{
			Error("Trying to create CreationManager that has already been created.");
		}

		ourInstance = new CreationManager();
	}


	void CreationManager::Destroy()
	{
		if (ourInstance == nullptr)
		{
			Error("Trying to destroy CreationManager but ourinstance is nullptr");
		}

		delete ourInstance;
		ourInstance = nullptr;
	}

	void CreationManager::ConnectToVisualDebugger()
	{
		if (GetPhysicsSystem().getPvdConnectionManager())
		{
			GetPhysicsSystem().getVisualDebugger()->setVisualizeConstraints(true);
			GetPhysicsSystem().getVisualDebugger()->setVisualDebuggerFlag(physx::PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
			GetPhysicsSystem().getVisualDebugger()->setVisualDebuggerFlag(physx::PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);
			GetInstance().myDebuggerConnection = physx::PxVisualDebuggerExt::createConnection(GetPhysicsSystem().getPvdConnectionManager(), "127.0.0.1", 5425, 10);
		}
	}

	static SP::PhysicsErrorCallback  gErrorCallback;
	static physx::PxDefaultAllocator gDefaultAllocatorCallback;

	CreationManager::CreationManager()
	{
		myFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gErrorCallback);
		if (myFoundation == nullptr)
		{
			Error("Could not create Physx Foundation");
		}

		myProfileManager = &physx::PxProfileZoneManager::createProfileZoneManager(myFoundation);
		if (myProfileManager == nullptr)
		{
			Error("Could not create physx zone manager");
		}

		myPhysicsSystem = PxCreatePhysics(PX_PHYSICS_VERSION, *myFoundation, physx::PxTolerancesScale(), true, myProfileManager);

		if (myPhysicsSystem == nullptr)
		{
			Error("Could not create PhysxSystem");
		}

		myDispatcher = physx::PxDefaultCpuDispatcherCreate(2);

		myDebuggerConnection = nullptr;
	}


	CreationManager::~CreationManager()
	{
		if (myDebuggerConnection != nullptr)
		{
			static_cast<PxVisualDebuggerConnection*>(myDebuggerConnection)->release();
		}

		myPhysicsSystem->release();
		myProfileManager->release();
		myFoundation->release();
	}

}
