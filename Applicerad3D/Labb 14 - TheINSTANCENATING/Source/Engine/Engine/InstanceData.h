#pragma once
#include "Utilities\Math\Matrix44.h"
#include "Utilities\Math\Vector4.h"

namespace ENGINE_NAMESPACE
{
	struct InstanceData
	{
		Matrix44f myMatrix;
		Matrix44f myLastFrameMatrix;
		Vector4f myColor;
	};
}