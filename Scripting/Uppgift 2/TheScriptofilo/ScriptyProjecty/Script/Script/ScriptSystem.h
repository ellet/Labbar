#pragma once
#include <assert.h>
#include "Lua/include/lua.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include "FileWatcher/FileChangeWatcher.h"
#include <functional>

class ScriptSystem
{
public:
	static void Create();
	static void Destroy();

	static void LoadLuaFile(std::function<void()> aInitFunciton, const std::string & aFilePath)
	{
		GetInstance().myInitFunction = aInitFunciton;
		GetInstance().InternalLoadLuaFile(aFilePath);
	}

	static void Update();

	static void RegisterFunction(const std::string & aLuaFunctionName, lua_CFunction aFunction, const std::string & aHelpText);

	static void CallFunction(const std::string & aLuaFunctionToCall)
	{
		GetInstance().InternalSetFunctionToCall(aLuaFunctionToCall);
		GetInstance().InternalFunctionCall(0);
	}

	template <typename ...Arguments>
	static void CallFunction(const std::string & aLuaFunctionToCall, Arguments... args)
	{
		GetInstance().InternalSetFunctionToCall(aLuaFunctionToCall);
		const unsigned short aArgumentCount = AddArgumentsToStack(args...);
		GetInstance().InternalFunctionCall(aArgumentCount);
	}

private:
	void InternalSetFunctionToCall(const std::string & aFunctionToCall);
	void InternalFunctionCall(const unsigned short aArgumentCount);

	template <typename Type,typename ...Arguments>
	static unsigned short AddArgumentsToStack(const Type aTypeToAdd, Arguments... TheRest)
	{
		AddArgumentsToStack(aTypeToAdd);
		return 1 + AddArgumentsToStack(TheRest...);
	}

	template <typename Type>
	static unsigned short AddArgumentsToStack(const Type aTypeToAdd)
	{
		AddToStack(aTypeToAdd);
		return 1;
	}


	static void AddToStack(const float aFloatToAdd);

	void CloseFile();
	void InternalLoadLuaFile(const std::string & aFilePath);
	void PrintErrorMessage(lua_State * aLuaState, const int aErrorCode);
	void HandleWrongFunctionCall(const std::string & aErrorMesage);

	static ScriptSystem * ourInstance;	
	static ScriptSystem & GetInstance()
	{
		assert(ourInstance != nullptr && "Trying to get scriptsystem instance but ourinstance is nullptr");

		return *ourInstance;
	}


	std::function<void()> myInitFunction;
	std::string myLuaFilePath;
	lua_State * myLuaState;

	std::vector <std::string> myRegisteredFunctions;

	SB::FileChangeWatcher myFileChangeWatcher;

	ScriptSystem();
	~ScriptSystem();
};

