#include "stdafx.h"
#include "Engine\Model\AssimpModelLoader.h"
#include "Engine\Model\AssimpModel.h"

namespace SB
{
	AssimpModel * ResourceLoader<AssimpModel>::Load(const std::string& aPath, LoadError& aError)
	{
		return new AssimpModel(aPath);
	}
}
