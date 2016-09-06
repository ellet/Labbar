#include "stdafx.h"
#include "RenderConversions.h"

namespace HUG
{
	CU::Vector2f PixelToNormalized(const CU::Vector2f & aPixelPosition, const CU::Vector2f & aTargetResolution)
	{
		return CU::Vector2f(aPixelPosition.x / aTargetResolution.x , aPixelPosition.y / aTargetResolution.y);
	}

}