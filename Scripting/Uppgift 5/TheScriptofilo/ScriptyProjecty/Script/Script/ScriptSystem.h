#pragma once
#include <assert.h>
#include "Lua/include/lua.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include "FileWatcher/FileChangeWatcher.h"
#include <functional>
#include <fstream>
#include "Script/LuaNode.h"

class ScriptSystem
{
public:
	static void Create();
	static void Destroy();

	static void SetLuaFunctionRegistrationInit(std::function<void(const size_t)> aInitFunciton)
	{
		GetInstance().myInitFunction = aInitFunciton;
	}

	static void LoadLuaFile(const std::string & aFilePath)
	{
		GetInstance().myLuaStates.push_back(LuaNode());
		GetInstance().InternalLoadLuaFile(GetInstance().myLuaStates.size() - 1, aFilePath);
	}

	static void Update();

	static void RegisterFunction(const size_t aNodeIndex, const std::string & aLuaFunctionName, lua_CFunction aFunction, const std::string & aHelpText);
	static void RegisterEvent(const std::string & aEventName);
	static void AddEventCallback(const size_t aNodeIndex, const std::string & aEventName, const std::string & aCallbackName);

	static void CallEvent(const std::string & aEventName)
	{
		std::vector<LuaNode> & currentNodes = GetInstance().myLuaStates;

		for (size_t iNode = 0; iNode < currentNodes.size(); ++iNode)
		{

			/*if (GetInstance().myEvents.find(aEventName) == GetInstance().myEvents.end())
			{
			std::cout << (aEventName + " event does not exist").c_str() << std::endl;
			}*/
			if (currentNodes[iNode].GetEventFunction(aEventName) == "unassigned")
			{
				std::cout << ("Tried to call: " + aEventName + " but it hasn't been assigned a callback function").c_str() << std::endl;
			}
			else
			{
				CallFunction(iNode, currentNodes[iNode].GetEventFunction(aEventName));
			}
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
		std::vector<LuaNode> & currentNodes = GetInstance().myLuaStates;

		for (size_t iNode = 0; iNode < currentNodes.size(); ++iNode)
		{
			CallFunction(iNode, aLuaFunctionToCall);
		}
	}

	static void CallFunction(const size_t aNodeIndex, const std::string & aLuaFunctionToCall)
	{
		if (GetInstance().InternalSetFunctionToCall(aNodeIndex, aLuaFunctionToCall) == true)
		{
			GetInstance().InternalFunctionCall(aNodeIndex, 0);
		}
	}

	template <typename ...Arguments>
	static void CallFunction(const std::string & aLuaFunctionToCall, Arguments... args)
	{
		std::vector<LuaNode> & currentNodes = GetInstance().myLuaStates;

		for (size_t iNode = 0; iNode < currentNodes.size(); ++iNode)
		{
			CallFunction(iNode, aLuaFunctionToCall, args...);
		}
	}

	template <typename ...Arguments>
	static void CallFunction(const size_t aNodeIndex, const std::string & aLuaFunctionToCall, Arguments... args)
	{
		if (GetInstance().InternalSetFunctionToCall(aNodeIndex, aLuaFunctionToCall) == true)
		{
			const unsigned short aArgumentCount = AddArgumentsToStack(aNodeIndex, args...);
			GetInstance().InternalFunctionCall(aNodeIndex, aArgumentCount);
		}
	}

private:
	static lua_State * GetLuaStateAt(const size_t aNodeIndex);
	bool InternalSetFunctionToCall(const size_t aNodeIndex, const std::string & aFunctionToCall);
	void InternalFunctionCall(const size_t aNodeIndex, const unsigned short aArgumentCount);

	template <typename Type, typename ...Arguments>
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const Type aTypeToAdd, Arguments... TheRest)
	{
		AddArgumentsToStack(aNodeIndex, aTypeToAdd);
		return 1 + AddArgumentsToStack(aNodeIndex, TheRest...);
	}

	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const float aFloatToAdd);
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const int aIntToAdd);
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const unsigned short aUnsignedShortToAdd);

	//void CloseFile();
	void InternalLoadLuaFile(const size_t aNodeIndex, const std::string & aFilePath);
	void PrintErrorMessage(lua_State * aLuaState, const int aErrorCode);
	void HandleWrongFunctionCall(const std::string & aErrorMesage);

	static ScriptSystem * ourInstance;
	static ScriptSystem & GetInstance()
	{
		assert(ourInstance != nullptr && "Trying to get scriptsystem instance but ourinstance is nullptr");

		return *ourInstance;
	}

	std::vector<std::string> myEventLibrary;

	std::function<void(const size_t)> myInitFunction;
	std::vector<LuaNode> myLuaStates;

	std::ofstream myFunctionExplainer;
	std::vector <std::string> myRegisteredFunctions;

	SB::FileChangeWatcher myFileChangeWatcher;

	ScriptSystem();
	~ScriptSystem();
};


