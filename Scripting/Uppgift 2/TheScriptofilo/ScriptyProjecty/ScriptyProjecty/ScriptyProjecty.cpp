// ScriptyProjecty.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Script\ScriptSystem.h"
#include "LuaTestFunctions.h"

void RegisterFunctions()
{
	ScriptSystem::RegisterFunction("testy", TestFuncton, "testytestytesty");
	ScriptSystem::RegisterFunction("Print", PrintFromLua, "PrintPrintPrintPrint");
}


int main()
{
	ScriptSystem::Create();

	ScriptSystem::LoadLuaFile("testfile.lua");
	RegisterFunctions();

	ScriptSystem::CallFunction("Init");

	const float FrameRate = 1.f / 60.f;

	const float TickRate = 1.f;
	float upateTimer = TickRate;

	while (true)
	{
		
		upateTimer -= FrameRate;
		if (upateTimer <= 0.f)
		{
			upateTimer = TickRate;
			ScriptSystem::CallFunction("Update");
		}
	}

	std::system("pause");

	ScriptSystem::Destroy();
    return 0;
}

