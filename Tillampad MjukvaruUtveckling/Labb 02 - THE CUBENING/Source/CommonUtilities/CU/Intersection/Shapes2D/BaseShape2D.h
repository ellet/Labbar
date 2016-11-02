#pragma once
#include "CU/Math/Vectors/vector2.h"
#include "CU/NameSpaceAliases.h"

class BaseShape2D
{
public:
	BaseShape2D();
	virtual ~BaseShape2D();

	virtual void ChangePosition(const CU::Vector2f aPosition);

	CU::Vector2f myMainPoint;
};