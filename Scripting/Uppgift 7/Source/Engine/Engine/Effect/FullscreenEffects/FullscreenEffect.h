#pragma once
#include "Engine\Effect\Effect.h"

namespace SB
{
	class FullscreenEffect :
		public Effect
	{
	public:
		FullscreenEffect(const char * aVertexPath = "shaders/fullscreen/vertex.fx", const char * aVertexEntryPoint = "VShader", const char * aPixelPath = "shaders/fullscreen/pixelCopy.fx", const char * aPixelEntryPoint = "PShader");
		~FullscreenEffect();
	};
}
