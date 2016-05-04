#pragma once
#include "../../Vectors/Vector.h"

namespace Intersection3D
{

	class BaseShape
	{
	public:
		BaseShape();
		virtual ~BaseShape();


		Vector3f myPosition;

	};

};