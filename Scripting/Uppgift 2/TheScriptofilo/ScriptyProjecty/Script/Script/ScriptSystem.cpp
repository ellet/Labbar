//#include "stdafx.h"
#include "ScriptSystem.h"
#include "HelperFunctions.h"


ScriptSystem * ScriptSystem::ourInstance = nullptr;




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



void ScriptSystem::InternalSetFunctionToCall(const std::string & aFunctionToCall)
{
	lua_getglobal(GetInstance().myLuaState, aFunctionToCall.c_str());
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

void ScriptSystem::AddToStack(const float aFloatToAdd)
{
	lua_pushnumber(GetInstance().myLuaState, static_cast<float>(aFloatToAdd));
}

void ScriptSystem::CloseFile()
{
	if (myLuaState != nullptr)
	{
		lua_close(myLuaState);
		myLuaState = nullptr;
	}
}


void ScriptSystem::InternalLoadLuaFile(const std::string & aFilePath)
{
	CloseFile();
	myLuaFilePath = aFilePath;
	myLuaState = luaL_newstate();

	luaL_openlibs(myLuaState);

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

	myFunctionExplainer = std::ofstream("exposedscriptfunctions.txt");

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

ScriptSystem::ScriptSystem()
{
	myLuaState = nullptr;
}


ScriptSystem::~ScriptSystem()
{
	CloseFile();
}
