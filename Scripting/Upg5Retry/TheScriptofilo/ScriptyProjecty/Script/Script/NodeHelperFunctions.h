#pragma once
#include <algorithm>
#include <intsafe.h>




extern "C" inline int ExecutePin(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	size_t currentNode;
	currentNode = static_cast<size_t> (lua_tonumber(aLuaState, 2));

	std::string connectionName;
	connectionName = lua_tostring(aLuaState, 1);
	
	std::transform(connectionName.begin(), connectionName.end(), connectionName.begin(), ::tolower);

	size_t connectedID = ScriptSystem::GetConnectedLuaNodeIndex(currentNode, connectionName);

	if (connectedID != SIZE_T_MAX)
	{
		ScriptSystem::CallFunction(connectedID, "Run", connectedID);
	}


	return 0;
}

extern "C" inline int GetPinData(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	size_t currentNode;
	currentNode = static_cast<size_t> (lua_tonumber(aLuaState, 1));

	std::string pinName;
	pinName = lua_tostring(aLuaState, 2);

	std::transform(pinName.begin(), pinName.end(), pinName.begin(), ::tolower);

	std::string pinData = ScriptSystem::GetPinDataFromNode(currentNode, pinName);

	ScriptSystem::AddArgumentsToStack(currentNode, pinData);
	

	return 1;
}

void RegisterNodeFunctions(const size_t aNodeIndex)
{
	ScriptSystem::RegisterFunction(aNodeIndex, "ExecutePin", ExecutePin, "Executes run function on a connected graph node");
	//ScriptSystem::RegisterFunction(aNodeIndex, "ExecutePin", ExecutePin, "Executes run function on a connected graph node");
}