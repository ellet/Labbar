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

void ScriptSystem::Update()
{

}

ScriptSystem::ScriptSystem()
{
	myLuaState = luaL_newstate();
}


ScriptSystem::~ScriptSystem()
{
	lua_close(myLuaState);
}
