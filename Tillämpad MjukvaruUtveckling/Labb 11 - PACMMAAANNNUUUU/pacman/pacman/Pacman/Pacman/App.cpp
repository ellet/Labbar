#include "app.h"
#include "TI_TimeManager.h"
#include "hgeFont.h"
#include "commonMacros.h"

#include "CU_Vector.h"

#include "HgeSingelton.h"

#pragma comment(lib, "legacy_stdio_definitions.lib")

App::App()
{

}

App::~App()
{
}

bool App::Init()
{

	myGame.Init();

	return(true);
};


bool App::Update()
{

	HGES->Gfx_BeginScene();
	HGES->Gfx_Clear(0);

	bool endGame = myGame.Update();
	myGame.Render();

	// DO HGE render stuff
	HGES->Gfx_EndScene();


	return(endGame);
}