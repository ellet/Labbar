#include "stdafx.h"
#include "Script.h"
#include <lua.hpp>
#include "ScriptFile.h"

namespace ENGINE_NAMESPACE
{

	Script::Script(lua_State* aState, const std::shared_ptr<ScriptFile>& aScriptFile, int aLuaRef)
	{
		L = aState;
		myScriptFile = aScriptFile;
		myLuaRef = LUA_NOREF;
		myLinkedGameObject = nullptr;
		UpdateRef(aLuaRef);
		myArgumentCount = 0;
	}

	Script::~Script()
	{
		luaL_unref(L, LUA_REGISTRYINDEX, myLuaRef);
		myLuaRef = LUA_NOREF;

		myScriptFile->RemoveScript(*this);
	}

	void Script::UpdateRef(int aLuaRef)
	{
		luaL_unref(L, LUA_REGISTRYINDEX, myLuaRef);
		myLuaRef = aLuaRef;

		if (myLuaRef != LUA_NOREF)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, myLuaRef);
			myUserData = static_cast<void**>(lua_newuserdata(L, sizeof(void*)));
			*myUserData = this;
			lua_setfield(L, -2, "_cpointer");
			lua_pop(L, 1);
		}
	}

	void Script::PushFloat(const float aValue)
	{
		myArgumentCount++;
		lua_pushnumber(L, aValue);
	}

	void Script::PushInt(const int aValue)
	{
		myArgumentCount++;
		lua_pushinteger(L, aValue);
	}

	void Script::ExecuteFunction(const char * aFunctionName)
	{
		int argc = myArgumentCount;
		// Reset it now to support recursive calls
		myArgumentCount = 0;

		lua_rawgeti(L, LUA_REGISTRYINDEX, myLuaRef);
		lua_getfield(L, -1, aFunctionName);

		// Move function to bottom of stack
		lua_insert(L, 1);
		// Move self above function
		lua_insert(L, 2);

		if (lua_isfunction(L, 1))
		{
			if (lua_pcall(L, argc + 1, 0, 0) != 0)
			{
				Engine::GetLogger().LogError("Lua runtime error in file {0}: {1}", myScriptFile->GetPath(), lua_tostring(L, -1));
				lua_pop(L, 1);
			}
		}
		else if (lua_isnil(L, 1) == false)
		{
			Error("Tried to execute something that wasn't a function or nil.");
		}
		else
		{
			lua_pop(L, 2 + argc);
		}

	}

	void Script::LinkGameObject(GameObject & aObject)
	{
		myLinkedGameObject = &aObject;
	}

}
