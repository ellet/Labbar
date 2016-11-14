#include "stdafx.h"
#include "ParticleEffect.h"

namespace ENGINE_NAMESPACE
{
	ParticleEffect::ParticleEffect()
	{
		AttachVertexShader("shaders/particle/shader.fx", "VShader");
		AttachGeometryShader("shaders/particle/shader.fx", "GShader");
		AttachPixelShader("shaders/particle/shader.fx", "PShader");

		InputLayout layout;
		layout.Add("TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT);
		layout.Add("SIZE", 0, DXGI_FORMAT_R32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

		Link(layout);
	}

	ParticleEffect::~ParticleEffect()
	{
	}
}