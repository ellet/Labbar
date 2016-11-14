#include "stdafx.h"
#include "CapsuleCollider.h"


namespace ENGINE_NAMESPACE
{

	CapsuleCollider::CapsuleCollider()
	{
	}

	CapsuleCollider::~CapsuleCollider()
	{
	}

	void CapsuleCollider::SetPosition(const Vector3f & aPostion)
	{
		myPosition = aPostion;
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


	float CapsuleCollider::GetRadius() const
	{
		return myRadius;
	}

}
