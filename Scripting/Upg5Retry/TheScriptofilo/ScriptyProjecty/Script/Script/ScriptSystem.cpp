//#include "stdafx.h"
#include "ScriptSystem.h"
#include "HelperFunctions.h"
#include "..\DataParser\DataParser.h"
#include "NodeHelperFunctions.h"

ScriptSystem * ScriptSystem::ourInstance = nullptr;

extern "C" inline int LUARegisterEventCallBack(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	std::string eventName;
	std::string callbackFunctionName;
	size_t nodeIndex;

	if (args > 3)
	{
		std::cout << "LUARegisterEventCallBack recieved too many arguments" << std::endl;
	}

	if (lua_isnoneornil(aLuaState, 2) == true)
	{
		std::cout << "a argument was none or nil " << std::endl;
		std::system("pause");
	}
	else
	{
		eventName = lua_tostring(aLuaState, 2);
	}

	if (lua_isnoneornil(aLuaState, 3) == true)
	{
		std::cout << "a argument was none or nil " << std::endl;
		std::system("pause");
	}
	else
	{
		callbackFunctionName = lua_tostring(aLuaState, 3);
	}

	if (lua_isnoneornil(aLuaState, 1) == true)
	{
		std::cout << "a argument was none or nil " << std::endl;
		std::system("pause");
	}
	else
	{
		nodeIndex = static_cast<size_t>(lua_tointeger(aLuaState, 1));
	}

	ScriptSystem::AddEventCallback(nodeIndex, eventName, callbackFunctionName);

	return 0;
}



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

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const float aFloatToAdd)
{
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<double>(aFloatToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const unsigned short aUnsignedShortToAdd)
{
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<double>(aUnsignedShortToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const int aIntToAdd)
{
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<double>(aIntToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const size_t aUnsignedIntToAdd)
{
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<double>(aUnsignedIntToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const std::string aStringToAdd)
{
	lua_pushstring(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), aStringToAdd.c_str());

	return 1;
}

lua_State * ScriptSystem::GetLuaStateAt(const size_t aNodeIndex)
{
	return GetInstance().myLuaStates[aNodeIndex].GetLuaState();
}

bool ScriptSystem::InternalSetFunctionToCall(const size_t aNodeIndex, const std::string & aFunctionToCall)
{
	lua_getglobal(GetLuaStateAt(aNodeIndex), aFunctionToCall.c_str());

	if (lua_isnoneornil(GetLuaStateAt(aNodeIndex), 1) == true)
	{
		lua_pop(GetLuaStateAt(aNodeIndex), 1);
		std::cout << ("Lua function: " + aFunctionToCall + " was none or nil ").c_str() << std::endl;
		return false;
	}

	return true;
}

void ScriptSystem::InternalFunctionCall(const size_t aNodeIndex, const unsigned short aArgumentCount)
{
	int LuaResult = lua_pcall(GetLuaStateAt(aNodeIndex), aArgumentCount, 0, 0);

	if (LuaResult != LUA_OK)
	{
		GetInstance().PrintErrorMessage(GetLuaStateAt(aNodeIndex), LuaResult);
		return;
	}
}

//void ScriptSystem::CloseFile()
//{
//	if (myLuaState != nullptr)
//	{
//		lua_close(myLuaState);
//		myLuaState = nullptr;
//	}
//}


void ScriptSystem::InternalLoadLuaFile(const size_t aNodeIndex, const std::string & aFilePath, const long long aNodeID)
{
	myLuaStates[aNodeIndex].CloseFile();

	LuaNodeDesc nodeDesc;

	nodeDesc.FilePath = aFilePath;
	nodeDesc.InternalID = aNodeIndex;
	nodeDesc.NodeID = aNodeID;
	nodeDesc.Events = &myEventLibrary;


	lua_State * newState = luaL_newstate();
	nodeDesc.LuaState = newState;
	myLuaStates[aNodeIndex].Init(nodeDesc);

	luaL_openlibs(newState);

	myFunctionExplainer = std::ofstream("exposedscriptfunctions.txt");
	ScriptSystem::RegisterFunction(aNodeIndex, "RegisterCallback", LUARegisterEventCallBack, "Registers a callback function for a given event, first argument the event second argument the name of the callback function");

	int LuaResult = luaL_loadfile(newState, aFilePath.c_str());
	//luaL_dofile(myLuaState, aFilePath.c_str);


	if (LuaResult != LUA_OK)
	{
		PrintErrorMessage(newState, LuaResult);
		return;
	}

	LuaResult = lua_pcall(newState, 0, LUA_MULTRET, 0);

	if (LuaResult != LUA_OK)
	{
		PrintErrorMessage(newState, LuaResult);
		return;
	}

	myInitFunction(aNodeIndex);

	myFunctionExplainer.close();

}

void ScriptSystem::InternalLoadScriptGraph(const std::string & aFilePath)
{
	SB::DataDocument graphFile;

	SB::DataParser::Open(aFilePath, graphFile);

	SB::DataNode nodes = graphFile["NodeTree"]["Node"];

	size_t initNodeID;
	bool initAssigned = false;

	for (unsigned short iNode = 0; iNode < nodes.Capacity(); ++iNode)
	{
		std::string nodeName = nodes[iNode]["Name"].GetString();
		std::string luaFile = std::string( "Scripts/ScriptNodes/") + nodes[iNode]["FilePath"].GetString();

		long long nodeID = std::stoll(nodes[iNode]["UID"].GetString());

		
		size_t newNodeIndex = LoadLuaFile(luaFile, nodeID);
		RegisterNodeFunctions(newNodeIndex);

		myNodeIDConverter[nodeID] = newNodeIndex;

		if (nodeName == "script init")
		{
			if (initAssigned == true)
			{
				std::cout << "more than one init node " << std::endl;
			}

			initAssigned = true;
			initNodeID = newNodeIndex;
		}

		LuaNode & newNode = myLuaStates[newNodeIndex];

		SB::DataNode connections = nodes[iNode]["Connections"]["Connection"];
		if (connections.IsArray())
		{

			for (unsigned short iConnection = 0; iConnection < connections.Capacity(); ++iConnection)
			{
				std::string connectionName = connections[iConnection]["Name"].GetString();
				std::string varType = connections[iConnection]["VarType"].GetString();
				if (varType == "impulse")
				{
					if (connections[iConnection].HasMember("PinConnection") == true)
					{
						long long connectionID = std::stoll(connections[iConnection]["PinConnection"]["ConnectedTo"].GetString());

						newNode.RegisterConnectedNode(connectionName, connectionID);
					}
				}
				else if (varType == "string")
				{
					std::string pinData = connections[iConnection]["PinData"].GetString();

					newNode.RegisterPindData(connectionName, pinData);
				}
				else
				{
					std::cout << "Connection Vartype: " << connections[iConnection]["VarType"].GetString() << " is unsupported" << std::endl;
				}

				
			}
		}
		else
		{
			std::string connectionName = connections["Name"].GetString();
			long long connectionID = std::stoll(connections["PinConnection"]["ConnectedTo"].GetString());
			newNode.RegisterConnectedNode(connectionName, connectionID);
		}

		
	}

	if (initAssigned == true)
	{
		CallFunction(initNodeID, "Run", initNodeID);
	}
	else
	{
		std::cout << "graph did not have a init node" << std::endl;
	}
	
}

void ScriptSystem::PrintErrorMessage(lua_State * aLuaState, const int aErrorCode)
{
	int apa = aErrorCode;

	std::string message = lua_tostring(aLuaState, -1);

	size_t stringStartPos = message.find("attempt to call a nil value");

	if (stringStartPos == message.npos)
	{
		std::cout << message.c_str() << std::endl;
	}
	else
	{
		HandleWrongFunctionCall(message);
	}
	std::system("pause");
	lua_pop(aLuaState, 1);
}

void ScriptSystem::HandleWrongFunctionCall(const std::string & aErrorMesage)
{
	std::string functionName = aErrorMesage.substr(aErrorMesage.find_first_of('\'') + 1, aErrorMesage.length() - aErrorMesage.find_first_of('\'') - 3);

	size_t smallestDifferene = 0xffffffff;
	unsigned short smallestIndex = 0;

	for (unsigned short iFunction = 0; iFunction < myRegisteredFunctions.size(); ++iFunction)
	{
		size_t currentDifference = uiLevenshteinDistance(functionName, myRegisteredFunctions[iFunction]);

		if (currentDifference < smallestDifferene)
		{
			smallestIndex = iFunction;
			smallestDifferene = currentDifference;
		}
	}

	std::cout << "Could not find function " + functionName + " perhaps you meant " + myRegisteredFunctions[smallestIndex] << "?" << std::endl;
}

size_t ScriptSystem::GetInternalNodeID(const long long aExternalNodeID)
{
	if (myNodeIDConverter.find(aExternalNodeID) != myNodeIDConverter.end())
	{
		return myNodeIDConverter[aExternalNodeID];
		
	}
	else
	{
		std::cout << "External ID: " << std::to_string(aExternalNodeID) + " did not exist is database" << std::endl;
		return 0;
	}
}

void ScriptSystem::Update()
{
	std::vector<std::string> aVectorOfFileChanges;
	GetInstance().myFileChangeWatcher.CheckChanges(aVectorOfFileChanges);

	if (aVectorOfFileChanges.size() > 0)
	{
		for (size_t iFile = 0; iFile < aVectorOfFileChanges.size(); ++iFile)
		{
			std::vector<LuaNode> & currentNodes = GetInstance().myLuaStates;

			for (size_t iNode = 0; iNode < currentNodes.size(); ++iNode)
			{
				if (currentNodes[iNode].GetFilePath() == aVectorOfFileChanges[iFile])
				{
					GetInstance().InternalLoadLuaFile(iNode, currentNodes[iNode].GetFilePath(), 0);
					break;
				}
			}
		}

	}

}

void ScriptSystem::RegisterFunction(const size_t aNodeIndex, const std::string & aLuaFunctionName, lua_CFunction aFunction, const std::string & aHelpText)
{
	GetInstance().myRegisteredFunctions.push_back(aLuaFunctionName);
	lua_register(GetLuaStateAt(aNodeIndex), aLuaFunctionName.c_str(), aFunction);

	GetInstance().myFunctionExplainer << std::endl;

	GetInstance().myFunctionExplainer << aLuaFunctionName << " - " << "Function Description: " << aHelpText << std::endl;

	GetInstance().myFunctionExplainer << std::endl;
}

void ScriptSystem::RegisterEvent(const std::string & aEventName)
{
	GetInstance().myEventLibrary.push_back(aEventName);
}

void ScriptSystem::AddEventCallback(const size_t aNodeIndex, const std::string & aEventName, const std::string & aCallbackName)
{
	if (aNodeIndex < GetInstance().myLuaStates.size())
	{
		GetInstance().myLuaStates[aNodeIndex].RegisterEventCallback(aEventName, aCallbackName);
	}
	else
	{
		std::cout << "Tried to add a EventCallback to a luastate that doensn't exist" << std::endl;
	}
}

size_t ScriptSystem::GetConnectedLuaNodeIndex(const size_t aStateIndex, const std::string & aConnectionName)
{
	long long externalID;
	if (GetInstance().myLuaStates[aStateIndex].GetConnectedID(aConnectionName, externalID) == true)
	{
		return GetInstance().GetInternalNodeID(externalID);
	}
	else
	{
		return SIZE_T_MAX;
	}
}

const std::string & ScriptSystem::GetPinDataFromNode(const size_t aStateIndex, const std::string & aPinName)
{
	return GetInstance().myLuaStates[aStateIndex].GetPinData(aPinName);
}

ScriptSystem::ScriptSystem()
{
}


ScriptSystem::~ScriptSystem()
{
	for (size_t iState = 0; iState < myLuaStates.size(); ++iState)
	{
		myLuaStates[iState].CloseFile();
	}

	myLuaStates.clear();
}
