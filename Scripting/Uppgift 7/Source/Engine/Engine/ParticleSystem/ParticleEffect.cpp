#include "stdafx.h"
#include "ParticleEffect.h"

namespace SB
{
	ParticleEffect::ParticleEffect()
	{
		InputLayout layout;
		layout.Add("TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT);
		layout.Add("SIZE", 0, DXGI_FORMAT_R32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		
		AttachVertexShader("shaders/particle/shader.fx", "VShader", layout);
		AttachGeometryShader("shaders/particle/shader.fx", "GShader");
		AttachPixelShader("shaders/particle/shader.fx", "PShader");
	}

	ParticleEffect::~ParticleEffect()
	{
	}
}