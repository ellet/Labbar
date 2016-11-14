#include "stdafx.h"
#include "Engine\Texture\TextureLoader.h"
#include "Engine\Texture\Texture.h"

namespace ENGINE_NAMESPACE
{
	Texture * ResourceLoader<Texture>::Load(const std::string& aPath, LoadError& aError)
	{
		return new Texture(aPath);
	}
}
