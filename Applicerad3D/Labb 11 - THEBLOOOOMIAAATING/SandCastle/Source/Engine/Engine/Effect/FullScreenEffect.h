#pragma once
#include "Effect.h"


namespace ENGINE_NAMESPACE
{

	class FullScreenEffect : public Effect
	{
	public:
		FullScreenEffect(const char * aPixelEntryPoint = "CopyToTarget", const char * aVertexEntryPoint = "VShader", const char * aPixelPath = "shaders/fullscreen/pixel.fx", const char * aVertexPath = "shaders/fullscreen/vertex.fx");
		~FullScreenEffect();
	};

}