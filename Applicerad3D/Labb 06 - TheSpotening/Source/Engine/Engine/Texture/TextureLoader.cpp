#include "stdafx.h"
#include "Engine\Texture\TextureLoader.h"
#include "Engine\Texture\Texture.h"

std::shared_ptr<Texture> ResourceLoader<Texture>::Load(const std::string& aPath, LoadError& aError)
{
	return std::make_shared<Texture>(aPath);
}