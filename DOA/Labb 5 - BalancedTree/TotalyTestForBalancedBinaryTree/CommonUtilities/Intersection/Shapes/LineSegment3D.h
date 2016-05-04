#pragma once
#include "BaseShape.h"

namespace Intersection3D
{


	class LineSegment3D : public BaseShape
	{
	public:
		LineSegment3D();
		~LineSegment3D();


		Vector3f myStartPos;
		Vector3f myEndPos;

	};

};