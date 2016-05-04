#include "BoxShape.h"
#include "PointShape.h"

BoxShape::BoxShape()
{
}


BoxShape::~BoxShape()
{
}

BoxShape::BoxShape(const Vector2f aCenterPosition, const Vector2f aExtents)
{
	myCollisionBox = Intersection2D::AABB2D(aCenterPosition, aExtents);
}

bool BoxShape::CheckCollision(const BaseCollisionShape & aCollisionShape) const
{
	return aCollisionShape.CheckShapeVsBox((*this));
}

bool BoxShape::CheckShapeVsBox(const BoxShape & aCollisionShape) const
{
	if (Intersection2D::AABBVsAABB2D(myCollisionBox, aCollisionShape.myCollisionBox) == true)
	{
		return true;
	}

	return false;
}

bool BoxShape::CheckShapeVsPoint(const PointShape & aPointShape) const
{
	if (Intersection2D::PointInsideAABB2D(myCollisionBox, aPointShape.GetMyPoint()) == true)
	{
		return true;
	}

	return false;
}

void BoxShape::ChangePosition(const Vector2f aPosition)
{
	myCollisionBox.ChangePosition(aPosition);
}
