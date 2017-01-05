#include "stdafx.h"
#include "DynamicActor.h"

namespace SP
{

	DynamicActor::DynamicActor(const SB::Vector3f & aPosition)
	{
		
		PxTransform startPosition(PxVec3(aPosition.x, aPosition.y, aPosition.z));
		myDynamicActor = CreationManager::GetPhysicsSystem().createRigidDynamic(startPosition);
		myActor = myDynamicActor;
		
		physx::PxRigidBodyExt::updateMassAndInertia(*myDynamicActor, 10.0f);

	}


	DynamicActor::DynamicActor() : DynamicActor(SB::Vector3f::Zero)
	{
	}

	DynamicActor::~DynamicActor()
	{
	}

	void DynamicActor::SetVelocity(const SB::Vector3f & aVelocity)
	{
		myDynamicActor->setAngularDamping(0.5f);

		physx::PxVec3 velocity(aVelocity.x, aVelocity.y, aVelocity.z);
		myDynamicActor->setLinearVelocity(velocity);
	}

}
