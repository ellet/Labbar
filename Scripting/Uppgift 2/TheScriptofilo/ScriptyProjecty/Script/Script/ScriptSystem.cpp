#include "ScriptSystem.h"


ScriptSystem * ScriptSystem::ourInstance = nullptr;




void ScriptSystem::Create()
{
	assert(ourInstance == nullptr && "trying to create scriptsystem twice");

	ourInstance = new ScriptSystem();
}

void ScriptSystem::Destroy()
{
	assert(ourInstance != nullptr && "trying to destroy scriptsystem but ourinstance is nullptr");

	delete ourInstance;
}



void ScriptSystem::InternalLoadLuaFile(const std::string & aFilePath)
{
	assert(myLuaState == nullptr && "lua state was not nullptr");

	myLuaState = luaL_newstate();

	luaL_openlibs(myLuaState);

	int LuaResult = luaL_loadfile(myLuaState, aFilePath.c_str());
	//luaL_dofile(myLuaState, aFilePath.c_str);


	if (LuaResult != LUA_OK)
	{
		PrintErrorMessage(myLuaState);
		return;
	}

	LuaResult = lua_pcall(myLuaState, 0, LUA_MULTRET, 0);

	if (LuaResult != LUA_OK)
	{
		PrintErrorMessage(myLuaState);
		return;
	}

	

}

void ScriptSystem::PrintErrorMessage(lua_State * aLuaState)
{
	const char* message = lua_tostring(aLuaState, -1);
	std::cout << message << std::endl;
	std::system("pause");
	lua_pop(aLuaState, 1);
}

void ScriptSystem::Update()
{

}

void ScriptSystem::RegisterFunction(const std::string & aLuaFunctionName, lua_CFunction aFunction, const std::string & /*aHelpText*/)
{
	lua_register(GetInstance().myLuaState, aLuaFunctionName.c_str(), aFunction);
}

void ScriptSystem::CallFunction(const std::string & aLuaFunctionToCall)
{
	lua_getglobal(GetInstance().myLuaState, aLuaFunctionToCall.c_str());

	int LuaResult = lua_pcall(GetInstance().myLuaState, 0, 0, 0);

	if (LuaResult != LUA_OK)
	{
		GetInstance().PrintErrorMessage(GetInstance().myLuaState);
		return;
	}

}

ScriptSystem::ScriptSystem()
{
	myLuaState = nullptr;
		
}


ScriptSystem::~ScriptSystem()
{
	lua_close(myLuaState);
}
