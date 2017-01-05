#include "stdafx.h"
#include "ShaderFileLoader.h"
#include "ShaderFile.h"

namespace SB
{
	ShaderFile * ResourceLoader<ShaderFile>::Load(const std::string& aPath, LoadError& aError)
	{
		return new ShaderFile(aPath);
	}
}
