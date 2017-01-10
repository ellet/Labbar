// Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Game\Game.h>
#include <Engine\Debugging\CommandLineParameters.h>

int main(int argc, char * argv[])
{
	SB::CommandLineParameters::CreateInstance();

	SB::CommandLineParameters::GetInstance().Parse(argc, argv);

	SB::PostMaster::Initialize();

	{
		Game::CreateInstance();
		Game::GetInstance().Start();
	}

	SB::PostMaster::Shutdown();
	SB::CommandLineParameters::DestroyInstance();

    return 0;
}

