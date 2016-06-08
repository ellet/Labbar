#include "stdafx.h"
#include "Triangle.h"


Intersection2D::Triangle::Triangle()
{
}

Intersection2D::Triangle::Triangle(const CU::Point2f & aFirstPoint, const CU::Point2f & aSecondPoint, const CU::Point2f & aThirdPoint)
{
	Init(aFirstPoint, aSecondPoint, aThirdPoint);
}

Intersection2D::Triangle::~Triangle()
{
}

void Intersection2D::Triangle::Init(const CU::Point2f & aFirstPoint, const CU::Point2f & aSecondPoint, const CU::Point2f & aThirdPoint)
{
	myFirstLine = Intersection2D::LineSegment2D(aSecondPoint, aFirstPoint);
	mySecondLine = Intersection2D::LineSegment2D(aThirdPoint, aSecondPoint);
	myThirdLine = Intersection2D::LineSegment2D(aFirstPoint, aThirdPoint);
}
