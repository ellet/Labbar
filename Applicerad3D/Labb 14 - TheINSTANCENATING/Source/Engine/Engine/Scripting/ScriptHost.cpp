#include "stdafx.h"
#include "ScriptHost.h"
#include <lua.hpp>
#include "ScriptFile.h"
#include "Engine\GameObject\GameObject.h"
#include "Script.h"
#include <Utilities/Math/MathMacros.h>

#pragma warning(disable : 4702)

namespace ENGINE_NAMESPACE
{
	ScriptHost::ScriptHost()
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		lua_newtable(L);
		lua_pushcfunction(L, &ScriptHost::LuaGetFunction);
		lua_setfield(L, -2, "__index");
		lua_setglobal(L, "globalComponentMeta");
	}


	int ScriptHost::LuaGetFunction(lua_State * aLuaStack)
	{
		const char * aFunctionName = lua_tostring(aLuaStack, 2);
		auto && it = Engine::GetScriptHost().myLuaFunctions.find(aFunctionName);
		if (it != Engine::GetScriptHost().myLuaFunctions.end())
		{
			Engine::GetScriptHost().myLuaFunctionToExecute = it->second;
			lua_pushcfunction(aLuaStack, &ScriptHost::LuaExecuteFunction);
			return 1;
		}
		return 0;
	}

	int ScriptHost::LuaExecuteFunction(lua_State * L)
	{
		if (lua_istable(L, 1) == false)
		{
			lua_pushstring(L, "The first argument must be a table! (did you pass self/use \":\"?)");
			lua_error(L);
		}

		lua_getfield(L, 1, "_cpointer");
		if (lua_isuserdata(L, -1) == false)
		{
			lua_pushstring(L, "The first argument's \"_cpointer\" member must be a userdata! (did you pass self/use \":\"?)");
			lua_error(L);
		}

		Script * script = *static_cast<Script**>(lua_touserdata(L, -1));
		// Pop the script reference
		lua_pop(L, 1);
		return (*Engine::GetScriptHost().myLuaFunctionToExecute)(script->GetLinkedGameObject(), L);
	}

	ScriptHost::~ScriptHost()
	{
	}

	ScriptFile * ScriptHost::LoadScriptFile(const std::string & aPath)
	{
		ScriptFile * file = new ScriptFile(L, aPath);
		return file;
	}

	void ScriptHost::RegisterFunction(const char * aFunctionName, const std::function<int(GameObject&, lua_State*)> & aFunction)
	{
		myLuaFunctions.emplace(std::string(aFunctionName), new std::function<int(GameObject&, lua_State*)>(aFunction));
	}

}

#pragma warning(default : 4702)
