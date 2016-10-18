#include "CU_Vector.h"

#include "TI_TimeManager.h"
#include "App.h"

#include "HgeSingelton.h"

HTEXTURE tex;

HGE* HGE_Init()
{
	HGE* hgeInstance=NULL;

	hgeInstance=hgeCreate(HGE_VERSION);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	//hgeInstance->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
	hgeInstance->System_SetState(HGE_TITLE, "Pacman - FixMEPlz!");
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, 650);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, 725);
	hgeInstance->System_SetState(HGE_SCREENBPP, 32);
	hgeInstance->System_SetState(HGE_SHOWSPLASH, false);
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
	HGE* hgeEngine = HGE_Init();
	TI_Time::TimeManager::CreateInstance();
	TI_Time::TimeManager::GetInstance()->InitDefaults();
	TI_Time::TimeManager::GetInstance()->CreateTimer(TI_Time::GAME_CLOCK_01);
	TI_Time::TimeManager::GetInstance()->CreateTimer(TI_Time::GAME_CLOCK_02);
	TI_Time::TimeManager::GetInstance()->AttachTimerToTimer(TI_Time::SYSTEM_CLOCK,TI_Time::GAME_CLOCK_01);
	TI_Time::TimeManager::GetInstance()->AttachTimerToTimer(TI_Time::SYSTEM_CLOCK,TI_Time::GAME_CLOCK_02);

	TI_Time::TimeManager::GetInstance()->SetClockPauseState(TI_Time::GAME_CLOCK_01,true);

	if(hgeEngine==NULL) return(-1);

	HgeSingelton::CreateHge();
	HgeSingelton::GetInstance()->Init(hgeEngine);



	MSG windowsMessage;
	App application;

	application.Init();

	bool quitFlag=false;

	while (1) 
	{
		// check for messages
		if ( PeekMessage( &windowsMessage, NULL, 0, 0, PM_REMOVE ) ) 
		{
			// handle or dispatch messages
			if ( windowsMessage.message == WM_QUIT )
			{
				break;
			}
			TranslateMessage( &windowsMessage );
			DispatchMessage( &windowsMessage );
		} 
		else
		{
			TI_Time::TimeManager::GetInstance()->Update();
 			if(application.Update()==false)
 			{
 				break;
 			}

		}

	}

	//application.Destroy();

	HGE_Shutdown(hgeEngine);

	// Clean up and shutdown
	return 0;
}