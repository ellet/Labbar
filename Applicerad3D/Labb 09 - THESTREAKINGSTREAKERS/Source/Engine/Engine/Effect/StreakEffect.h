#pragma once
#include "Engine\Effect\Effect.h"

namespace ENGINE_NAMESPACE
{
	class StreakEffect :
		public Effect
	{
	public:
		StreakEffect(const char * aVertexPath = "shaders/streakShader.fx", const char * aVertexEntryPoint = "VShader", const char * aPixelPath = "shaders/streakShader.fx", const char * aPixelEntryPoint = "PShader", const char * aGeometryPath = "shaders/streakShader.fx", const char * aGeometryEntryPoint = "GShader");
		~StreakEffect();
	};
}

