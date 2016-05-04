#pragma once
#include "../../Vectors/vector2.h"

class BaseShape2D
{
public:
	BaseShape2D();
	virtual ~BaseShape2D();

	virtual void ChangePosition(const Vector2f aPosition);

	Vector2f myMainPoint;
};

