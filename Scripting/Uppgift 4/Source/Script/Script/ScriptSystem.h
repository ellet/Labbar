#pragma once
#include <assert.h>
#include "Lua/include/lua.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include "FileWatcher/FileChangeWatcher.h"
#include <functional>
#include <fstream>

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
	static void RegisterEvent(const std::string & aEventName);
	static void AddEventCallback(const std::string & aEventName, const std::string & aCallbackName);

	static void CallEvent(const std::string & aEventName)
	{
		if (GetInstance().myEvents.find(aEventName) == GetInstance().myEvents.end())
		{
			std::cout << (aEventName + " event does not exist").c_str() << std::endl;
		}
		else if (GetInstance().myEvents[aEventName] == "unassigned")
		{
			std::cout << ("Tried to call: " + aEventName + " but it hasn't been assigned a callback function").c_str() << std::endl;
		}
		else
		{
			CallFunction(GetInstance().myEvents[aEventName]);
		}
	}

	template <typename ...Arguments>
	static void CallEvent(const std::string & aEventName, Arguments... args)
	{
		if (GetInstance().myEvents.find(aEventName) == GetInstance().myEvents.end())
		{
			std::cout << (aEventName + " event does not exist").c_str() << std::endl;
		}
		else if (GetInstance().myEvents[aEventName] == "unassigned")
		{
			std::cout << ("Tried to call: " + GetInstance().myEvents[aEventName] + " but it hasn't been assigned a callback function").c_str() << std::endl;
		}
		else
		{
			CallFunction(GetInstance().myEvents[aEventName], args...);
		}
	}

	static void CallFunction(const std::string & aLuaFunctionToCall)
	{
		if (GetInstance().InternalSetFunctionToCall(aLuaFunctionToCall) == true)
		{
			GetInstance().InternalFunctionCall(0);
		}
	}

	template <typename ...Arguments>
	static void CallFunction(const std::string & aLuaFunctionToCall, Arguments... args)
	{
		if (GetInstance().InternalSetFunctionToCall(aLuaFunctionToCall) == true)
		{
			const unsigned short aArgumentCount = AddArgumentsToStack(args...);
			GetInstance().InternalFunctionCall(aArgumentCount);
		}
	}

private:
	bool InternalSetFunctionToCall(const std::string & aFunctionToCall);
	void InternalFunctionCall(const unsigned short aArgumentCount);

	template <typename Type,typename ...Arguments>
	static unsigned short AddArgumentsToStack(const Type aTypeToAdd, Arguments... TheRest)
	{
		AddArgumentsToStack(aTypeToAdd);
		return 1 + AddArgumentsToStack(TheRest...);
	}

	static unsigned short AddArgumentsToStack(const float aFloatToAdd);
	static unsigned short AddArgumentsToStack(const int aIntToAdd);
	static unsigned short AddArgumentsToStack(const unsigned short aUnsignedShortToAdd);


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


	std::unordered_map<std::string, std::string> myEvents;

	std::function<void()> myInitFunction;
	std::string myLuaFilePath;
	// lua_State * myLuaState;
	SB::GrowingArray<LuaNode> myLuaState;



	std::ofstream myFunctionExplainer;
	std::vector <std::string> myRegisteredFunctions;

	Script::FileChangeWatcher myFileChangeWatcher;

	ScriptSystem();
	~ScriptSystem();
};

