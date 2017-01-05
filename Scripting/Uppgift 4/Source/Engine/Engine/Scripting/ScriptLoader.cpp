#include "stdafx.h"
#include "ScriptLoader.h"
#include "ScriptFile.h"
#include <lua.hpp>
#include "Script.h"
#include "ScriptHost.h"

namespace SB
{
	ScriptFile * ResourceLoader<ScriptFile>::Load(const std::string& aPath, LoadError& aError)
	{
		return Engine::GetScriptHost().LoadScriptFile(aPath);
	}
}