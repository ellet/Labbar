#pragma once
#include <dxgiformat.h>
#include "DataTypeEnum.h"


DXGI_FORMAT ConvertToDXGI(const eDataType aDataTypeEnum)
{
	switch (aDataTypeEnum)
	{
	case eDataType::Float:
		return DXGI_FORMAT_R32_FLOAT;
		break;
	case eDataType::Float2:
		return DXGI_FORMAT_R32G32_FLOAT;
		break;
	case eDataType::Float3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
		break;
	case eDataType::Float4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	}
	return DXGI_FORMAT_UNKNOWN;
}