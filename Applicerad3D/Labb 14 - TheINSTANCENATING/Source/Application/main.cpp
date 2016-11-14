#include "stdafx.h"
#include <Game\Game.h>
#include <Engine\Debugging\CommandLineParameters.h>

#ifdef PUBLISH
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
#else
int main(int argc, char * argv[])
#endif
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
