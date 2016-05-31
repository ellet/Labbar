#pragma once
#include "BaseShape.h"

namespace Intersection3D
{

	class AABB : public BaseShape
	{
	public:
		AABB();
		~AABB();


		CU::Vector3f myCenterPos;
		CU::Vector3f myExtents;
		CU::Vector3f myMinPos;
		CU::Vector3f myMaxPos;

		CU::Vector3f GetClosestPoint(const CU::Vector3f & aPointToCompareTo) const
		{
			CU::Vector3f temp;
			temp.x = MAX(myMinPos.x, MIN(myMaxPos.x, aPointToCompareTo.x));
			temp.y = MAX(myMinPos.y, MIN(myMaxPos.y, aPointToCompareTo.y));
			temp.z = MAX(myMinPos.z, MIN(myMaxPos.z, aPointToCompareTo.z));

			return temp;
		}

	};

};