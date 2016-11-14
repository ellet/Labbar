#include "stdafx.h"
#include "FullscreenEffect.h"



namespace ENGINE_NAMESPACE
{

	FullscreenEffect::FullscreenEffect(const char * aVertexPath /*= "shaders/fullscreen/vertex.fx"*/, const char * aVertexEntryPoint /*= "VShader"*/, const char * aPixelPath /*= "shaders/fullscreen/pixel.fx"*/, const char * aPixelEntryPoint /*= "PShader"*/)
	{
		AttachVertexShader(aVertexPath, aVertexEntryPoint);
		AttachPixelShader(aPixelPath, aPixelEntryPoint);

		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT);

		Link(layout);
	}

	FullscreenEffect::~FullscreenEffect()
	{
	}	
}
