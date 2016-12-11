#pragma once
#include <assert.h>
#include "Lua/include/lua.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include "FileWatcher/FileChangeWatcher.h"

class ScriptSystem
{
public:
	static void Create();
	static void Destroy();

	static void LoadLuaFile(const std::string & aFilePath)
	{
		GetInstance().InternalLoadLuaFile(aFilePath);
	}

	static void Update();

	static void RegisterFunction(const std::string & aLuaFunctionName, lua_CFunction aFunction, const std::string & aHelpText);

	static void CallFunction(const std::string & aLuaFunctionToCall);

private:

	void InternalLoadLuaFile(const std::string & aFilePath);
	void PrintErrorMessage(lua_State * aLuaState, const int aErrorCode);
	void HandleWrongFunctionCall(const std::string & aErrorMesage);

	static ScriptSystem * ourInstance;	
	static ScriptSystem & GetInstance()
	{
		assert(ourInstance != nullptr && "Trying to get scriptsystem instance but ourinstance is nullptr");

		return *ourInstance;
	}

	lua_State * myLuaState;

	std::vector <std::string> myRegisteredFunctions;

	ScriptSystem();
	~ScriptSystem();
};

