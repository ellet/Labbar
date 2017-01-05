#include "stdafx.h"
#include "BaseCollider.h"

namespace SB
{

	BaseCollider::BaseCollider()
	{
	}


	BaseCollider::~BaseCollider()
	{
	}

	

	bool BaseCollider::CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const
	{
		Error("Sphere collision not implemented");
	}	

	bool BaseCollider::CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const
	{
		Error("Capsule collision not implemented");
	}


	bool BaseCollider::CheckCollisionAgainstRay(const RayCollider & aRayCollider) const
	{
		Error("Ray collision not implemented");
	}

}