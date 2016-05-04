#include "Sphere.h"

namespace Intersection3D
{


	Sphere::Sphere()
	{
	}


	Sphere::Sphere(const Vector3f & aCenterPosition, const float aRadius)
	{
		myCenterPosition = aCenterPosition;
		myRadius = aRadius;
		myRadiusSquared = aRadius * aRadius;
	}

	Sphere::~Sphere()
	{
	}

};