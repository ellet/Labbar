#pragma once
#include "BaseShape.h"

namespace Intersection3D
{


	class Sphere : public BaseShape
	{
	public:
		Sphere();
		~Sphere();

		Vector3f myCenterPosition;
		float myRadius;
		float myRadiusSquared;

	};

};