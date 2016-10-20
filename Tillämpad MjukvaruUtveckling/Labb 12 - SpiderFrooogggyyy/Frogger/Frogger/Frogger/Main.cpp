#include <stdafx.h>
#include "..\hgelibs\include\hge.h"
#include "Game.h"
#include "defines.h"
#include "GiefThreadNAme.h"


HGE* HGE_Init()
{
	HGE* hgeInstance=NULL;

	hgeInstance=hgeCreate(HGE_VERSION);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	hgeInstance->System_SetState(HGE_TITLE, "Frogger Game - Mikael Danielsson");    
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, SCREEN_RESOLUTION_X);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, SCREEN_RESOLUTION_Y);
	hgeInstance->System_SetState(HGE_SCREENBPP, 32);
	hgeInstance->System_SetState(HGE_USESOUND, false);
	hgeInstance->System_SetState(HGE_SHOWSPLASH, false);
	hgeInstance->System_SetState(HGE_HIDEMOUSE, false);
    hgeInstance->System_SetState(HGE_ZBUFFER,false);
	if(!hgeInstance->System_Initiate())
	{
		hgeInstance->System_Shutdown();
		hgeInstance->Release();
		hgeInstance=NULL;
	}

	return hgeInstance;
};

void HGE_Shutdown(HGE* aHGEInstance)
{
	aHGEInstance->System_Shutdown();
	aHGEInstance->Release();
}




int WINAPI WinMain(HINSTANCE aHInstance, HINSTANCE aPrevHInstance, LPSTR aCommandLine, int aNumberOfCommands)
{
	HGE* hgeEngine=HGE_Init();

	if(hgeEngine==NULL) return(-1);


	MSG windowsMessage;
    FroggerGame::Game froggerGame;
	froggerGame.Init(hgeEngine);

	SetThreadName("THE THREAD TO RULE THEM ALL");

	while (1) 
	{
		// check for messages
		if ( PeekMessage( &windowsMessage, NULL, 0, 0, PM_REMOVE ) ) 
		{
			// handle or dispatch messages
			if ( windowsMessage.message == WM_QUIT )
			{
				froggerGame.Shutdown();
				break;
			}
			TranslateMessage( &windowsMessage );
			DispatchMessage( &windowsMessage );
		} 
		else
		{ 
			if(froggerGame.Update()==false)
			{
				froggerGame.Shutdown();
				break;
			}

		}

	}

	HGE_Shutdown(hgeEngine);

	// Clean up and shutdown
	return 0;
}
