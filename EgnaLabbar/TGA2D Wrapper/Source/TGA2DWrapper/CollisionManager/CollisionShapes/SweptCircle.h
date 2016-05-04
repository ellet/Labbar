#pragma once
#include "BaseCollisionShape.h"
#include <Intersection/Shapes2D/LineSegment2D.h>

class SweptCircle : public BaseCollisionShape
{
public:
	SweptCircle();
	~SweptCircle();

	SweptCircle(const Vector2f aStartPosition, const Vector2f aEndPosition, const float aRadius);

	inline const Intersection2D::LineSegment2D &  GetCollisionLine() const;

	float inline GetRadius() const;

	virtual bool CheckCollision(const BaseCollisionShape & aCollisionShape) const override;

	virtual void ChangePosition(const Vector2f aStartPosition, const Vector2f aEndPosition);

	virtual bool CheckShapeVsLine(const LineShape & aLineShape) const override;

private:
	Intersection2D::LineSegment2D myLine;
	float myRadius;
};

inline const Intersection2D::LineSegment2D & SweptCircle::GetCollisionLine() const
{
	return myLine;
}

inline float SweptCircle::GetRadius() const
{
	return myRadius;
}