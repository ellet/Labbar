#pragma once
#include "Engine/Effect/Effect.h"

namespace SB
{
	class SpriteEffect : public Effect
	{
	public:
		SpriteEffect();
		SpriteEffect(const char * aPixelFile, const char * aPixelEntryPoint);
		SpriteEffect(const char * aVertexFile, const char * aVertexEntryPoint,
			const char * aPixelFile, const char * aPixelEntryPoint);
		~SpriteEffect();
	};
}
