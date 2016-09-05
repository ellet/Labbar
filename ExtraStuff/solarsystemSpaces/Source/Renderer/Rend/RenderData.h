#pragma once

#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>


struct RenderData
{
	RenderData():myColor(CU::Vector4f::One)
	{
		mySize = CU::Vector2f::One;
	}

	CU::Vector2f mySizeInPixels;
	CU::Vector4f myColor;
	CU::Vector2f mySize;
};