//#include "stdafx.h"
#include "ScriptSystem.h"
#include "HelperFunctions.h"


ScriptSystem * ScriptSystem::ourInstance = nullptr;



extern "C" inline int LUARegisterEventCallBack(lua_State * aLuaState)
{
	int args = lua_gettop(aLuaState);

	std::string eventName;
	std::string callbackFunctionName;

	if (args > 2)
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

	ScriptSystem::AddEventCallback(eventName, callbackFunctionName);

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



bool ScriptSystem::InternalSetFunctionToCall(const std::string & aFunctionToCall)
{
	lua_getglobal(GetInstance().myLuaState, aFunctionToCall.c_str());
	
	if (lua_isnoneornil(GetInstance().myLuaState, 1) == true)
	{
		lua_pop(GetInstance().myLuaState, 1);
		std::cout << ("Lua function: " + aFunctionToCall +  " was none or nil ").c_str() << std::endl;
		return false;
	}

	return true;
}

void ScriptSystem::InternalFunctionCall(const unsigned short aArgumentCount)
{
	int LuaResult = lua_pcall(GetInstance().myLuaState, aArgumentCount, 0, 0);

	if (LuaResult != LUA_OK)
	{
		GetInstance().PrintErrorMessage(GetInstance().myLuaState, LuaResult);
		return;
	}
}

unsigned short ScriptSystem::AddArgumentsToStack(const float aFloatToAdd)
{
	lua_pushnumber(GetInstance().myLuaState, static_cast<float>(aFloatToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const unsigned short aUnsignedShortToAdd)
{
	lua_pushnumber(GetInstance().myLuaState, static_cast<float>(aUnsignedShortToAdd));

	return 1;
}

unsigned short ScriptSystem::AddArgumentsToStack(const int aIntToAdd)
{
	lua_pushnumber(GetInstance().myLuaState, static_cast<float>(aIntToAdd));

	return 1;
}


void ScriptSystem::CloseFile()
{
	if (myLuaState != nullptr)
	{
		lua_close(myLuaState);
		myLuaState = nullptr;

		for (std::unordered_map<std::string, std::string>::iterator iEvent = myEvents.begin(); iEvent != myEvents.end(); ++iEvent)
		{
			iEvent->second = "unassigned";
		}
	}
}


void ScriptSystem::InternalLoadLuaFile(const std::string & aFilePath)
{
	CloseFile();
	myLuaFilePath = aFilePath;
	myLuaState = luaL_newstate();

	luaL_openlibs(myLuaState);

	myFunctionExplainer = std::ofstream("exposedscriptfunctions.txt");
	ScriptSystem::RegisterFunction("RegisterCallback", LUARegisterEventCallBack, "Registers a callback function for a given event, first argument the event second argument the name of the callback function");

	int LuaResult = luaL_loadfile(myLuaState, aFilePath.c_str());
	//luaL_dofile(myLuaState, aFilePath.c_str);


	if (LuaResult != LUA_OK)
	{
		PrintErrorMessage(myLuaState, LuaResult);
		return;
	}

	LuaResult = lua_pcall(myLuaState, 0, LUA_MULTRET, 0);

	if (LuaResult != LUA_OK)
	{
		PrintErrorMessage(myLuaState, LuaResult);
		return;
	}

	myInitFunction();

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
			if (GetInstance().myLuaFilePath == aVectorOfFileChanges[iFile])
			{
				GetInstance().InternalLoadLuaFile(GetInstance().myLuaFilePath);
				break;
			}
		}
		
	}

}

void ScriptSystem::RegisterFunction(const std::string & aLuaFunctionName, lua_CFunction aFunction, const std::string & aHelpText)
{
	GetInstance().myRegisteredFunctions.push_back(aLuaFunctionName);
	lua_register(GetInstance().myLuaState, aLuaFunctionName.c_str(), aFunction);

	GetInstance().myFunctionExplainer << std::endl;

	GetInstance().myFunctionExplainer << aLuaFunctionName << " - " << "Function Description: " << aHelpText  << std::endl;

	GetInstance().myFunctionExplainer << std::endl;
}

void ScriptSystem::RegisterEvent(const std::string & aEventName)
{
	if (GetInstance().myEvents.find(aEventName) != GetInstance().myEvents.end())
	{
		std::cout << "Adding event that already exists" << std::endl;
	}

	GetInstance().myEvents[aEventName] = "unassigned";
}

void ScriptSystem::AddEventCallback(const std::string & aEventName, const std::string & aCallbackName)
{
	if (GetInstance().myEvents.find(aEventName) == GetInstance().myEvents.end())
	{
		std::cout << (aEventName + " event does not exist").c_str() << std::endl;
	}
	else if (GetInstance().myEvents[aEventName] != "unassigned")
	{
		std::cout << (aEventName + " already has callback function: " + GetInstance().myEvents[aEventName] + " trying to overwrite with: " + aCallbackName).c_str() << std::endl;
	}
	else
	{
		GetInstance().myEvents[aEventName] = aCallbackName;
	}
}

ScriptSystem::ScriptSystem()
{
	myLuaState = nullptr;
}


ScriptSystem::~ScriptSystem()
{
	CloseFile();
}
