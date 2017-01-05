#include "stdafx.h"
#include "BaseActor.h"


namespace SP
{

	BaseActor::BaseActor()
	{
	}


	BaseActor::~BaseActor()
	{
		myActor->release();
	}

	void BaseActor::AddShape(const SB::BoxShape & aBoxShape)
	{
		physx::PxMaterial * material = nullptr;
		material = CreationManager::GetPhysicsSystem().createMaterial(0.5f, 0.5f, 0.6f);

		physx::PxShape* shape = nullptr;
		SB::Vector3f boxSize = aBoxShape.myExtents;
		shape = CreationManager::GetPhysicsSystem().createShape(physx::PxBoxGeometry(boxSize.x, boxSize.y, boxSize.z), *material);
		
		myActor->attachShape(*shape);

		shape->release();
		material->release();
	}

	void BaseActor::AddShape(const SB::SphereShape & aSphereShape)
	{
		physx::PxMaterial * material = nullptr;
		material = CreationManager::GetPhysicsSystem().createMaterial(0.5f, 0.5f, 0.6f);

		physx::PxShape* shape = nullptr;
		shape = CreationManager::GetPhysicsSystem().createShape(physx::PxSphereGeometry(aSphereShape.myRadius), *material);

		myActor->attachShape(*shape);

		shape->release();
		material->release();
	}

	physx::PxRigidActor & BaseActor::GetActor() const
	{
		return *myActor;
	}

	SB::Vector3f BaseActor::GetPosition() const
	{
		physx::PxVec3 temp = myActor->getGlobalPose().p;

		return SB::Vector3f(temp.x, temp.y, temp.z);
	}

	SB::Quaternion BaseActor::GetRotation() const
	{
		physx::PxQuat temp = myActor->getGlobalPose().q;

		return SB::Quaternion(temp.x, temp.y, temp.z, temp.w);
	}

}
