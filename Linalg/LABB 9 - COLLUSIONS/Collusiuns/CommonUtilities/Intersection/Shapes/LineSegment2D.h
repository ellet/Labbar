#pragma once
#include "BaseShape.h"

namespace Intersection
{


	class LineSegment2D : public BaseShape
	{
	public:
		LineSegment2D();
		~LineSegment2D();


		Vector2f myStartPos;
		Vector2f myEndPos;

	};

};