#include "stdafx.h"
#include "Engine\Texture\TextureLoader.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Texture\TextureCube.h"

namespace SB
{
	Texture * ResourceLoader<Texture>::Load(const std::string& aPath, LoadError& aError)
	{
		return new Texture(aPath);
	}

	TextureCube* ResourceLoader<TextureCube>::Load(const std::string& aPath, LoadError& aError)
	{
		return new TextureCube(aPath);
	}
}
