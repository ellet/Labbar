#include "stdafx.h"
#include "StreakEffect.h"

namespace ENGINE_NAMESPACE
{
	StreakEffect::StreakEffect()
	{
		AttachVertexShader("shaders/streak/shader.fx", "VShader");
		AttachGeometryShader("shaders/streak/shader.fx", "GShader");
		AttachPixelShader("shaders/streak/shader.fx", "PShader");

		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT);
		layout.Add("SIZE", 0, DXGI_FORMAT_R32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

		Link(layout);
	}

	StreakEffect::~StreakEffect()
	{
	}
}