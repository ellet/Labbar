#pragma once
#include "Utilities\Math\Matrix44.h"
#include "Utilities\Math\Vector4.h"

namespace SB
{
	struct InstanceData
	{
		Matrix44f myMatrix;
		Matrix44f myLastFrameMatrix;
		Color myColor;
	};
}