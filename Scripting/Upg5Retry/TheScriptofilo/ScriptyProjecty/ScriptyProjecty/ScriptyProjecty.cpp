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

	std::cout << "Hej Ralle!" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "any key == only arrow keys" << std::endl;
	std::cout << "// Ylf and l1" << std::endl;

	ScriptSystem::RegisterEvent("KeyPress");
	ScriptSystem::SetLuaFunctionRegistrationInit(std::bind(RegisterFunctions, std::placeholders::_1));
	/*ScriptSystem::LoadLuaFile("Scripts/testfile.lua");
	ScriptSystem::LoadLuaFile("Scripts/otherfile.lua");*/

	ScriptSystem::LoadScriptGraph("Graphs/GraphFile.json");

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

			if (GetAsyncKeyState(0x25) || GetAsyncKeyState(0x26) || GetAsyncKeyState(0x27) || GetAsyncKeyState(0x28))
			{
				ScriptSystem::CallEvent("KeyPress");
			}
			//ScriptSystem::Update();
			//ScriptSystem::CallFunction("Update", 3.3456f, 2.34f);
		}
	}

	std::system("pause");

	ScriptSystem::Destroy();
    return 0;
}
