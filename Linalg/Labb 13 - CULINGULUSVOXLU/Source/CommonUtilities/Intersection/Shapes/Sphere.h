#pragma once
#include "BaseShape.h"

namespace Intersection3D
{


	class Sphere : public BaseShape
	{
	public:
		Sphere();
		Sphere(const Vector3f & aCenterPosition, const float aRadius);
		~Sphere();

		Vector3f myCenterPosition;
		float myRadius;
		float myRadiusSquared;

	};

};