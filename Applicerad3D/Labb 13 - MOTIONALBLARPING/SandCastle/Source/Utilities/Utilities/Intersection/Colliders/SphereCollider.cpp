#include "stdafx.h"
#include "SphereCollider.h"

namespace ENGINE_NAMESPACE
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
}
