#include "stdafx.h"
#include "CapsuleCollider.h"


namespace SB
{

	CapsuleCollider::CapsuleCollider()
	{
	}

	CapsuleCollider::~CapsuleCollider()
	{
	}


	bool CapsuleCollider::CheckCollisionAgainstCollider(const BaseCollider & aCollider) const
	{
		return aCollider.CheckCollisionAgainstCapsule(*this);
	}

	bool CapsuleCollider::CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const
	{
		return Intersection::CapsuleVsSphere(*this, aSphereCollider);
	}

	bool CapsuleCollider::CheckCollisionAgainstCapsule(const CapsuleCollider & aCapsuleCollider) const
	{
		return Intersection::CapsuleVsCapsule(aCapsuleCollider, *this);
	}


	bool CapsuleCollider::CheckCollisionAgainstRay(const RayCollider & aRayCollider) const
	{
		return Intersection::RayVsCapsule(aRayCollider, *this);
	}	

	const Vector3f & CapsuleCollider::GetPosition() const
	{
		return myPosition;
	}

	Vector3f CapsuleCollider::GetSecondPosition() const
	{
		return myPosition + myDirectionAndLength;
	}

	LineSegmentShape CapsuleCollider::GetCapsuleAsLineSegment() const
	{
		return LineSegmentShape(myPosition, GetSecondPosition());
	}

	CapsuleShape CapsuleCollider::GetCapsuleAsCapsuleShape() const
	{
		return CapsuleShape(myPosition, myDirectionAndLength, myRadius);
	}

	void CapsuleCollider::SetLengthAndDirection(const Vector3f & aLenghtAndDirection)
	{
		myDirectionAndLength = aLenghtAndDirection;
	}

	
	const Vector3f & CapsuleCollider::GetLengthAndDirection() const
	{
		return myDirectionAndLength;
	}

	const Vector3f CapsuleCollider::GetDirection() const
	{
		return myDirectionAndLength.GetNormalized();
	}


	

	void CapsuleCollider::SetRadius(const float aRadius)
	{
		myRadius = aRadius;
	}

	float CapsuleCollider::GetRadius() const
	{
		return myRadius;
	}

	void CapsuleCollider::UpdatePosition(const Vector3f & aUpdatePosition)
	{
		myPosition = aUpdatePosition;
	}

	

	

}
