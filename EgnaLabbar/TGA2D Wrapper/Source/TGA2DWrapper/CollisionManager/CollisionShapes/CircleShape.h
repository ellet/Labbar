#pragma once
#include "BaseCollisionShape.h"

class CircleShape : public BaseCollisionShape
{
public:
	CircleShape();
	~CircleShape();

	CircleShape(const Vector2f aPosition, const float aRadius);

	inline const Intersection2D::Circle2D & CircleShape::GetCollisionBox() const;

	virtual bool CheckCollision(const BaseCollisionShape & aCollisionShape) const override;

	virtual bool CheckShapeVsPoint(const PointShape & aPointShape) const override;

	virtual bool CheckShapeVsLine(const LineShape & aLineShape) const override;

	virtual void ChangePosition(const Vector2f aPosition) override;


private:
	Intersection2D::Circle2D myCircle;
};

const Intersection2D::Circle2D & CircleShape::GetCollisionBox() const
{
	return myCircle;
}