//#include "stdafx.h"
#include "ScriptSystem.h"
#include "HelperFunctions.h"


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

	if (lua_isnoneornil(aLuaState, 1) == true)
	{
		std::cout << "a argument was none or nil " << std::endl;
		std::system("pause");
	}
	else
	{
		eventName = lua_tostring(aLuaState, 1);
	}

	if (lua_isnoneornil(aLuaState, 2) == true)
	{
		std::cout << "a argument was none or nil " << std::endl;
		std::system("pause");
	}
	else
	{
		callbackFunctionName = lua_tostring(aLuaState, 2);
	}

	if (lua_isnoneornil(aLuaState, 3) == true)
	{
		std::cout << "a argument was none or nil " << std::endl;
		std::system("pause");
	}
	else
	{
		nodeIndex = static_cast<size_t>(lua_tointeger(aLuaState, 3));
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
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<float>(aFloatToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const unsigned short aUnsignedShortToAdd)
{
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<float>(aUnsignedShortToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const size_t aNodeIndex, const int aIntToAdd)
{
	lua_pushnumber(GetInstance().myLuaStates[aNodeIndex].GetLuaState(), static_cast<float>(aIntToAdd));

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


void ScriptSystem::InternalLoadLuaFile(const size_t aNodeIndex, const std::string & aFilePath)
{
	myLuaStates[aNodeIndex].CloseFile();

	LuaNodeDesc nodeDesc;

	nodeDesc.FilePath = aFilePath;
	nodeDesc.InternalID = aNodeIndex;
	nodeDesc.NodeID = 0;
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
					GetInstance().InternalLoadLuaFile(iNode, currentNodes[iNode].GetFilePath());
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

ScriptSystem::ScriptSystem()
{
}


ScriptSystem::~ScriptSystem()
{
	myLuaStates.clear();
}
