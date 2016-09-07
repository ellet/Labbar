#pragma once
#include "CU/Math/Vectors/Vector.h"
#include "CU/NameSpaceAliases.h"

namespace Intersection3D
{

	class BaseShape
	{
	public:
		BaseShape();
		virtual ~BaseShape();


		CU::Vector3f myPosition;

	};

};