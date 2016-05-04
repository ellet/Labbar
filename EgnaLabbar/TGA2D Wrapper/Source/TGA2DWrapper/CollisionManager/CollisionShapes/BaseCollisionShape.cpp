#include "BaseCollisionShape.h"
#include <DLDebug/DL_Debug.h>
#include "BoxShape.h"
#include "PointShape.h"
#include "LineShape.h"
#include "CircleShape.h"
#include "SweptCircle.h"

BaseCollisionShape::BaseCollisionShape()
{
}


BaseCollisionShape::~BaseCollisionShape()
{
}

void BaseCollisionShape::DrawCollisionBox() const
{

}

void BaseCollisionShape::ChangePosition(const Vector2f aPosition)
{
	bool FalseFlag = false;
	DL_ASSERT(FalseFlag, "Change position not implemnted");

	(aPosition);
}

bool BaseCollisionShape::CheckShapeVsBox(const BoxShape & aCollisionShape) const
{
	bool FalseFlag = false;
	DL_ASSERT(FalseFlag, "Collision types vs Box check not found");

	(aCollisionShape);

	return false;
}

bool BaseCollisionShape::CheckShapeVsCircle(const CircleShape & aCollisionShape) const
{
	bool FalseFlag = false;
	DL_ASSERT(FalseFlag, "Collision types vs Circle check not found");

	(aCollisionShape);

	return false;
}

bool BaseCollisionShape::CheckShapeVsSweptCircle(const SweptCircle & aSweptCircle) const
{
	bool FalseFlag = false;
	DL_ASSERT(FalseFlag, "Collision types vs SweptCircle check not found");

	(aSweptCircle);

	return false;
}

bool BaseCollisionShape::CheckShapeVsPoint(const PointShape & aPointShape) const
{
	bool FalseFlag = false;
	DL_ASSERT(FalseFlag, "Collision types vs Point check not found");

	(aPointShape);

	return false;
}

bool BaseCollisionShape::CheckShapeVsLine(const LineShape & aLineShape) const
{
	bool FalseFlag = false;
	DL_ASSERT(FalseFlag, "Collision types vs Line check not found");


	(aLineShape);

	return false;
}