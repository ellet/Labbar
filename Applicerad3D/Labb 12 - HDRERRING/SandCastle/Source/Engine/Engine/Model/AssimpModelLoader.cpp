#include "stdafx.h"
#include "Engine\Model\AssimpModelLoader.h"
#include "Engine\Model\AssimpModel.h"

namespace ENGINE_NAMESPACE
{
	AssimpModel * ResourceLoader<AssimpModel>::Load(const std::string& aPath, LoadError& aError)
	{
		return new AssimpModel(aPath);
	}
}
