#include "stdafx.h"
#include "StreakEffect.h"


namespace ENGINE_NAMESPACE
{
	StreakEffect::StreakEffect(const char * aVertexPath, const char * aVertexEntryPoint, const char * aPixelPath, const char * aPixelEntryPoint, const char * aGeometryPath, const char * aGeometryEntryPoint)
	{
		AttachVertexShader(aVertexPath, aVertexEntryPoint);
		AttachPixelShader(aPixelPath, aPixelEntryPoint);
		AttachGeometryShader(aGeometryPath, aGeometryEntryPoint);

		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("SIZE", 0, DXGI_FORMAT_R32_FLOAT);
		layout.Add("ALPHA", 0, DXGI_FORMAT_R32_FLOAT);

		Link(layout);
	}

	StreakEffect::~StreakEffect()
	{
	}
}
