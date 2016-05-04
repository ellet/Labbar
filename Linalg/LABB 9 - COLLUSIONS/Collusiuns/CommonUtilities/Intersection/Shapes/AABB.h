#pragma once
#include "BaseShape.h"

namespace Intersection
{

	class AABB : public BaseShape
	{
	public:
		AABB();
		~AABB();


		Vector3f myCenterPos;
		Vector3f myExtents;
		Vector3f myMinPos;
		Vector3f myMaxPos;


	};

};