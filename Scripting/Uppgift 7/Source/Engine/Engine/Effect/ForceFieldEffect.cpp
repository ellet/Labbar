#include "stdafx.h"
#include "ForceFieldEffect.h"

namespace SB
{
	ForceFieldEffect::ForceFieldEffect(const char * aVertexPath, const char * aVertexEntryPoint, const char * aPixelPath, const char * aPixelEntryPoint)
	{

		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("BITANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

		layout.AddPerInstance("INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
		layout.AddPerInstance("INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
		layout.AddPerInstance("INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
		layout.AddPerInstance("INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

		layout.AddPerInstance("PREVIOUS_INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
		layout.AddPerInstance("PREVIOUS_INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
		layout.AddPerInstance("PREVIOUS_INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);
		layout.AddPerInstance("PREVIOUS_INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

		layout.AddPerInstance("INSTANCE_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1);

		AttachVertexShader(aVertexPath, aVertexEntryPoint, layout);
		AttachPixelShader(aPixelPath, aPixelEntryPoint);
	}

	ForceFieldEffect::~ForceFieldEffect()
	{
	}
}