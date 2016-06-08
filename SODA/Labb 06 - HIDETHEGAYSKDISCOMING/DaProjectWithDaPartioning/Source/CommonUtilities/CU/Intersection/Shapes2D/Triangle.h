#pragma once
#include "CU/Intersection/Shapes2D/LineSegment2D.h"

namespace Intersection2D
{

	class Triangle : public BaseShape2D
	{
	public:
		Triangle();
		Triangle(const CU::Point2f & aFirstPoint, const CU::Point2f & aSecondPoint, const CU::Point2f & aThirdPoint);
		~Triangle();

		void Init(const CU::Point2f & aFirstPoint, const CU::Point2f & aSecondPoint, const CU::Point2f & aThirdPoint);

		LineSegment2D myFirstLine;
		LineSegment2D mySecondLine;
		LineSegment2D myThirdLine;
	};

}
