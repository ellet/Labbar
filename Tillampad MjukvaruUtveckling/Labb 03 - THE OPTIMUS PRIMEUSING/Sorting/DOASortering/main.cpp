#include <Windows.h>
#include <hge.h>
#include "Game.h"

HGE* InitHge()
{
	HGE* hgeInstance = NULL;

	hgeInstance = hgeCreate(HGE_VERSION);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	hgeInstance->System_SetState(HGE_TITLE, "Optimize me!");
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, 1280);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, 1024);
	hgeInstance->System_SetState(HGE_SHOWSPLASH, false);

	if(!hgeInstance->System_Initiate())
	{
		hgeInstance->System_Shutdown();
		hgeInstance->Release();
		hgeInstance=NULL;
	}

	return hgeInstance;
}

void ShutdownHGE(HGE* aHGEInstnace)
{
	aHGEInstnace->System_Shutdown();
	aHGEInstnace->Release();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	srand(static_cast<unsigned long>(time(0)));
	

	MSG message;
	HGE* hgeInstance = InitHge();;
	bool quitFlag = true;

	Game game(*hgeInstance);

	game.Init();

	while(quitFlag == true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
		{
			if(message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		} 
		else
		{
			quitFlag = game.Update();
		}
	}

	ShutdownHGE(hgeInstance);

	return 0;
}