#include "stdafx.h"
#include "RayCollider.h"

namespace ENGINE_NAMESPACE
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

	LineSegmentShape RayCollider::GetRayAsLineSegment(const float aLength /*= 3.f*/)
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

}