#pragma once
#include <assert.h>
#include "Lua/include/lua.hpp"

class ScriptSystem
{
public:
	static void Create();
	static void Destroy();

	static void Update();


private:

	static ScriptSystem * ourInstance;	
	ScriptSystem & GetInstance()
	{
		assert(ourInstance != nullptr && "Trying to get scriptsystem instance but ourinstance is nullptr");

		return *ourInstance;
	}

	lua_State * myLuaState;

	ScriptSystem();
	~ScriptSystem();
};

