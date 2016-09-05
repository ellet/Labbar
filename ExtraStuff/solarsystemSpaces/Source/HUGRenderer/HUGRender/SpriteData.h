#pragma once
#include "CU/NameSpaceAliases.h"
#include "CU/Vectors/vector2.h"

namespace HUG
{
	struct SpriteData
	{
		SpriteData() : myPivot(NormalizedPosition::Zero), myRotationInRadians(0.f), mySize(1.f, 1.f)
		{
		}

		NormalizedPosition myPivot;
		float myRotationInRadians;
		CU::Vector2f mySize;
	};
}