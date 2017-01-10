#include "stdafx.h"
#include "StaticActor.h"
#include "..\..\PhysxIncludes\PxRigidStatic.h"

namespace SP
{

	StaticActor::StaticActor()
	{
		physx::PxMaterial * material = nullptr;
		material = CreationManager::GetPhysicsSystem().createMaterial(0.5f, 0.5f, 0.6f);

		myActor = physx::PxCreatePlane(CreationManager::GetPhysicsSystem(), physx::PxPlane(0, 1, 0, 0), *material);
	}


	StaticActor::~StaticActor()
	{
	}

}
