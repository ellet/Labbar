#include "Lua/include/lua.hpp"
#include "LuaNode.h"
#include <iostream>
#include <intsafe.h>


LuaNode::LuaNode()
{
	myLuaState = nullptr;
}


LuaNode::~LuaNode()
{
}

void LuaNode::Init(const LuaNodeDesc & aSetupData)
{
	myFilePath = aSetupData.FilePath;
	myInternalID = aSetupData.InternalID;
	myLuaState = aSetupData.LuaState;
	myNodeID = aSetupData.NodeID;

	for (size_t iEvent = 0; iEvent < aSetupData.Events->size(); ++iEvent)
	{
		if (myEvents.find((*aSetupData.Events)[iEvent]) != myEvents.end())
		{
			std::cout << "Adding event that already exists" << std::endl;
		}

		myEvents[(*aSetupData.Events)[iEvent]] = "unassigned";
	}
}

void LuaNode::CloseFile()
{
	if (myLuaState != nullptr)
	{
		lua_close(myLuaState);
		myLuaState = nullptr;
	}
}

void LuaNode::RegisterConnectedNode(const std::string & aConnectionName, const long long aNodeIndex)
{
	if (myConnectedNodes.find(aConnectionName) == myConnectedNodes.end())
	{
		myConnectedNodes[aConnectionName] = aNodeIndex;
	}
	else
	{
		std::cout << " a connection with that name already exists" << std::endl;
	}
}

void LuaNode::RegisterPindData(const std::string & aConnectionName, const std::string & aPinData)
{
	if (myPinData.find(aConnectionName) != myPinData.end())
	{
		std::cout << ("PinData with name: " + aConnectionName + " already exists").c_str() << std::endl;
	}
	else
	{
		myPinData[aConnectionName] = aPinData;
	}
}

void LuaNode::RegisterEventCallback(const std::string & aEventName, const std::string & aCallbackFunctionName)
{
	if (myEvents.find(aEventName) == myEvents.end())
	{
		std::cout << (aEventName + " event does not exist").c_str() << std::endl;
	}
	else if (myEvents[aEventName] != "unassigned")
	{
		std::cout << (aEventName + " already has callback function: " + myEvents[aEventName] + " trying to overwrite with: " + aCallbackFunctionName).c_str() << std::endl;
	}
	else
	{
		myEvents[aEventName] = aCallbackFunctionName;
	}
}

const std::string & LuaNode::GetEventFunction(const std::string & aEventName)
{
	return myEvents[aEventName];
}

bool LuaNode::GetConnectedID(const std::string & aName, long long & aIDToSet)
{
	if (myConnectedNodes.find(aName) != myConnectedNodes.end())
	{
		aIDToSet = myConnectedNodes[aName];
		return true;
	}
	else
	{
		//std::cout << "Node with name " + aName + " could not be found." << std::endl;
		return false;
	}
}

const std::string & LuaNode::GetPinData(const std::string aPinName)
{
	if (myPinData.find(aPinName) == myPinData.end())
	{
		std::cout << ("PinData with name: " + aPinName + " doesn't exists").c_str() << std::endl;
		const static std::string GoodLifeChoices("");
		return GoodLifeChoices;
	}
	else
	{
		return myPinData[aPinName];
	}
}

lua_State * LuaNode::GetLuaState() const
{
	return myLuaState;
}

const std::string & LuaNode::GetFilePath() const
{
	return myFilePath;
}

size_t LuaNode::GetInternalID() const
{
	return myInternalID;
}

long long LuaNode::GetNodeID() const
{
	return myNodeID;
}

