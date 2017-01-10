#include "stdafx.h"
#include "RayCollider.h"

namespace SB
{

	RayCollider::RayCollider()
	{
		myDirection = Vector3f::UnitZ;
		myPosition = Vector3f::Zero;
	}


	RayCollider::~RayCollider()
	{
	}

	void RayCollider::SetPosition(const Vector3f & aPostion)
	{
		myPosition = aPostion;
	}

	const Vector3f & RayCollider::GetPosition() const
	{
		return myPosition;
	}

	LineSegmentShape RayCollider::GetRayAsLineSegment(const float aLength /*= 3.f*/) const
	{
		const Vector3f SecondPoint = myPosition + (myDirection * aLength);

		return LineSegmentShape(myPosition, SecondPoint);
	}

	void RayCollider::SetDirection(const Vector3f & aDirection)
	{
		myDirection = aDirection;
		myDirection.Normalize();
	}

	const Vector3f & RayCollider::GetDirection() const
	{
		return myDirection;
	}

	void RayCollider::UpdatePosition(const Vector3f & aUpdatePosition)
	{
		myPosition = aUpdatePosition;
	}

	void RayCollider::SetRadius(const float aRadius)
	{
		Error("Rays do not have a radius");
	}

	float RayCollider::GetRadius() const
	{
		Error("Rays do not have a radius");
	}


	bool RayCollider::CheckCollisionAgainstCollider(const BaseCollider & aCollider) const
	{
		return aCollider.CheckCollisionAgainstRay(*this);
	}

	bool RayCollider::CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const
	{
		return Intersection::RayVsSphere(*this, aSphereCollider);
	}	

	bool RayCollider::CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const
	{
		return Intersection::RayVsCapsule(*this, aCapsuleCollider);
	}


	bool RayCollider::CheckCollisionAgainstRay(const RayCollider & aRayCollider) const
	{
		Error("Dont to rays against rays");
	}	

}

