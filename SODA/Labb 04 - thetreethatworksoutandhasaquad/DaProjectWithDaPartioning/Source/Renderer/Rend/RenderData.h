#pragma once

#include <CU/NameSpaceAliases.h>
#include <CU/Vectors/vector4.h>

struct RenderData
{
	RenderData():myColor(CU::Vector4f::One)
	{
		myRotation = 0.f;
	}
	RenderData(const CU::Vector4f & aColor) :
		myColor(aColor)
	{
		myRotation = 0.f;
	}

	CU::Vector4f myColor;
	float myRotation;
};