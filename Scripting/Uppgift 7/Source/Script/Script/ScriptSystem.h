#pragma once
#include "Lua/include/lua.hpp"
#include <assert.h>
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

	static size_t LoadLuaFile(const std::string & aFilePath, const long long aNodeID = 0)
	{
		GetInstance().myLuaStates.resize(GetInstance().myLuaStates.size() + 1);
		GetInstance().InternalLoadLuaFile(GetInstance().myLuaStates.size() - 1, aFilePath, aNodeID);
		return GetInstance().myLuaStates.size() - 1;
	}

	static void LoadScriptGraph(const std::string & aFilePath)
	{
		GetInstance().InternalLoadScriptGraph(aFilePath);
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
				//std::cout << ("Tried to call: " + aEventName + " but it hasn't been assigned a callback function").c_str() << std::endl;
			}
			else
			{
				CallFunction(iNode, currentNodes[iNode].GetEventFunction(aEventName), iNode);
			}
		}
	}

	template <typename ...Arguments>
	static void CallEvent(const std::string & aEventName, Arguments... args)
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
				//std::cout << ("Tried to call: " + aEventName + " but it hasn't been assigned a callback function").c_str() << std::endl;
			}
			else
			{
				CallEvent(iNode, currentNodes[iNode].GetEventFunction(aEventName), args...);
			}
		}
	}

	template <typename ...Arguments>
	static void CallEvent(size_t aNodeID, const std::string & aEventName, Arguments... args)
	{
		CallFunction(GetInstance().myLuaStates[aNodeID].GetEventFunction(aEventName), aNodeID, args...);
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

	static size_t GetConnectedLuaNodeIndex(const size_t aStateIndex, const std::string & aConnectionName);
	static const std::string & GetPinDataFromNode(const size_t aStateIndex, const std::string & aPinName);

	template <typename Type, typename ...Arguments>
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const Type aTypeToAdd, Arguments... TheRest)
	{
		AddArgumentsToStack(aNodeIndex, aTypeToAdd);
		return 1 + AddArgumentsToStack(aNodeIndex, TheRest...);
	}

	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const std::string aStringToAdd);

	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const float aFloatToAdd);
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const int aIntToAdd);
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const unsigned short aUnsignedShortToAdd);
	static unsigned short AddArgumentsToStack(const size_t aNodeIndex, const size_t aUnsignedIntToAdd);

	template <typename... args>
	static std::tuple<args...> PopValues(lua_State * aLuaState)
	{
		int argumentNumner = 1;
		return std::make_tuple(PopTop<args>(aLuaState, argumentNumner)...);
	}

private:

	template <typename T>
	static T PopTop(lua_State * aLuaState, int & aCurrentArgumentNumber)
	{}

	template <>
	static int PopTop<int>(lua_State * aLuaState, int & aCurrentArgumentNumber)
	{
		int returnValue = static_cast<int>(lua_tointeger(aLuaState, -1));
		lua_remove(aLuaState, -1);
		return returnValue;
	}

	template <>
	static std::string PopTop<std::string>(lua_State * aLuaState, int & aCurrentArgumentNumber)
	{
		std::string returnValue = lua_tostring(aLuaState, -1);
		lua_remove(aLuaState, -1);
		return returnValue;
	}

	template <>
	static float PopTop<float>(lua_State * aLuaState, int & aCurrentArgumentNumber)
	{
		float returnValue = static_cast<float>( lua_tonumber(aLuaState, -1));
		lua_remove(aLuaState, -1);
		return returnValue;
	}

	static lua_State * GetLuaStateAt(const size_t aNodeIndex);
	bool InternalSetFunctionToCall(const size_t aNodeIndex, const std::string & aFunctionToCall);
	void InternalFunctionCall(const size_t aNodeIndex, const unsigned short aArgumentCount);

	//void CloseFile();
	void InternalLoadLuaFile(const size_t aNodeIndex, const std::string & aFilePath, const long long aNodeID);
	void InternalLoadScriptGraph(const std::string & aFilePath);
	void PrintErrorMessage(lua_State * aLuaState, const int aErrorCode);
	void HandleWrongFunctionCall(const std::string & aErrorMesage);

	size_t GetInternalNodeID(const long long aExternalNodeID);

	static ScriptSystem * ourInstance;
	static ScriptSystem & GetInstance()
	{
		assert(ourInstance != nullptr && "Trying to get scriptsystem instance but ourinstance is nullptr");

		return *ourInstance;
	}

	std::vector<std::string> myEventLibrary;

	std::function<void(const size_t)> myInitFunction;
	std::vector<LuaNode> myLuaStates;
	std::unordered_map<long long, size_t> myNodeIDConverter;


	std::ofstream myFunctionExplainer;
	std::vector <std::string> myRegisteredFunctions;

	Scripting::FileChangeWatcher myFileChangeWatcher;

	ScriptSystem();
	~ScriptSystem();
};


