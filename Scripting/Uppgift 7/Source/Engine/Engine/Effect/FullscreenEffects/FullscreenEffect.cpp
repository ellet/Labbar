#include "stdafx.h"
#include "FullscreenEffect.h"



namespace SB
{

	FullscreenEffect::FullscreenEffect(const char * aVertexPath /*= "shaders/fullscreen/vertex.fx"*/, const char * aVertexEntryPoint /*= "VShader"*/, const char * aPixelPath /*= "shaders/fullscreen/pixel.fx"*/, const char * aPixelEntryPoint /*= "PShader"*/)
	{
		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

		AttachVertexShader(aVertexPath, aVertexEntryPoint, layout);
		AttachPixelShader(aPixelPath, aPixelEntryPoint);
	}

	FullscreenEffect::~FullscreenEffect()
	{
	}	
}
