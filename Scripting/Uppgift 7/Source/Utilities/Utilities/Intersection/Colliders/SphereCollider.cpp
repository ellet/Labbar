#include "stdafx.h"
#include "SphereCollider.h"


namespace SB
{

	SphereCollider::SphereCollider()
	{
		Vector3f myPosition = Vector3f::Zero;
		myRadius = 1.f;
		myRadiusSquared = 1.f;
	}


	SphereCollider::SphereCollider(const Vector3f & aPosition, const float aRadius)
	{
		myPosition = aPosition;
		SetRadius(aRadius);
	}

	SphereCollider::~SphereCollider()
	{
	}

	bool SphereCollider::CheckCollisionAgainstCollider(const BaseCollider & aCollider) const
	{
		return aCollider.CheckCollisionAgainstSphere(*this);
	}

	bool SphereCollider::CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const
	{
		return Intersection::SphereVsSphere(aSphereCollider, *this);
	}

	bool SphereCollider::CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const
	{
		return Intersection::CapsuleVsSphere(aCapsuleCollider, *this);
	}

	bool SphereCollider::CheckCollisionAgainstRay(const RayCollider & aRayCollider) const
	{
		return Intersection::RayVsSphere(aRayCollider, *this);
	}


}
