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

#ifdef PUBLISH
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	LPWSTR * argList;
	int argc;
	argList = CommandLineToArgvW(GetCommandLine(), &argc);
	char ** argv = new char*[argc];
	for (int i = 0; i<argc; i++)
	{
		size_t length = wcslen(argList[i]);
		argv[i] = new char[length];
		for (size_t j = 0; j<length + 1; j++)
		{
			argv[i][j] = static_cast<char>(argList[i][j]);
		}
	}

	main(argc, argv);
}
#endif
