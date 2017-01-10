#pragma once
#include <Engine\Effect\StandardEffect.h>
namespace SB
{
	class ForceFieldEffect : public Effect
	{
	public:
		ForceFieldEffect(const char * aVertexPath, const char * aVertexEntryPoint, const char * aPixelPath, const char * aPixelEntryPoint);
		~ForceFieldEffect();
	};
}
