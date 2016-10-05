#pragma once
#include "Engine\Effect\Effect.h"

namespace ENGINE_NAMESPACE
{
	class ParticleEffect :
		public Effect
	{
	public:
		ParticleEffect(const char * aVertexPath = "shaders/particleShader.fx", const char * aVertexEntryPoint = "VShader", const char * aPixelPath = "shaders/particleShader.fx", const char * aPixelEntryPoint = "PShader", const char * aGeometryPath = "shaders/particleShader.fx", const char * aGeometryEntryPoint = "GShader");
		~ParticleEffect();
	};
}

