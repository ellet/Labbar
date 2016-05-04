#pragma once
#include "BaseCollisionShape.h"

class LineShape : public BaseCollisionShape
{
public:
	LineShape();
	~LineShape();

	inline const Intersection2D::LineSegment2D & GetMyLine() const;

	LineShape(const Vector2f aStartPosition, const Vector2f aEndPosition)
	{
		myCollisionLine = Intersection2D::LineSegment2D(aStartPosition, aEndPosition);
	}

	virtual bool CheckCollision(const BaseCollisionShape & aCollisionShape) const override;

	virtual bool CheckShapeVsBox(const BoxShape & aCollisionShape) const override;

	virtual bool CheckShapeVsCircle(const CircleShape & aCollisionShape) const override;

	virtual void ChangePosition(const Vector2f aPosition) override;

	virtual bool CheckShapeVsSweptCircle(const SweptCircle & aSweptCircle) const override;

	Vector2f GetNormal();

private:
	Intersection2D::LineSegment2D myCollisionLine;
};

inline const Intersection2D::LineSegment2D & LineShape::GetMyLine() const
{
	return myCollisionLine;
}