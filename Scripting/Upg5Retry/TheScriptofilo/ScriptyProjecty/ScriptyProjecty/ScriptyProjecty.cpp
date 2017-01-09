// ScriptyProjecty.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Script\ScriptSystem.h"
#include "LuaTestFunctions.h"
#include <functional>

void RegisterFunctions(const size_t aNodeIndex)
{
	ScriptSystem::RegisterFunction(aNodeIndex, "testy", TestFuncton, "Just a test function");
	ScriptSystem::RegisterFunction(aNodeIndex, "Print", PrintFromLua, "Will do a cout on each in arguemnt, ends with a newline. (there is no space or newline between arguments)");
}


int main()
{
	ScriptSystem::Create();

	ScriptSystem::SetLuaFunctionRegistrationInit(std::bind(RegisterFunctions, std::placeholders::_1));
	/*ScriptSystem::LoadLuaFile("Scripts/testfile.lua");
	ScriptSystem::LoadLuaFile("Scripts/otherfile.lua");*/

	ScriptSystem::LoadScriptGraph("Graphs/test.json");

	//ScriptSystem::CallFunction("Init");

	const float FrameRate = 1.f / 60.f;

	const float TickRate = 1.f;
	float upateTimer = TickRate;

	while (true)
	{
		
		upateTimer -= FrameRate;
		if (upateTimer <= 0.f)
		{
			upateTimer = TickRate;
			//ScriptSystem::Update();
			//ScriptSystem::CallFunction("Update", 3.3456f, 2.34f);
		}
	}

	std::system("pause");

	ScriptSystem::Destroy();
    return 0;
}
