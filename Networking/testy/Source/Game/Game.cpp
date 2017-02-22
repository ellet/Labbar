#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>


using namespace std::placeholders;


#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")

#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG


CGame::CGame()
{
}


CGame::~CGame()
{
}


void CGame::Init()
{
	unsigned short windowWidth = 1280;
	unsigned short windowHeight = 720;


    DX2D::SEngineCreateParameters createParameters;
    createParameters.myActivateDebugSystems = true;
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myEnableVSync = true;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );

    std::wstring appname = L"TGA 2D RELEASE";
#ifdef _DEBUG
    appname = L"TGA 2D DEBUG";
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

    DX2D::CEngine::CreateInstance( createParameters );

	myTimerManager.CreateTimer();

    if( !DX2D::CEngine::GetInstance()->Start() )
    {
        ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
    }

}


void CGame::InitCallBack()
{
    myGameWorld.Init();
}


void CGame::UpdateCallBack()
{
	myTimerManager.UpdateTimers();
	const float deltaTime = (float)myTimerManager.GetTimer(0).GetDeltaTime().GetMicroseconds() / 1000000.f;

	const float TimeStep = 1.f / 60.f;

	static float TimerCounter = 0;
	TimerCounter += deltaTime;

	while (TimerCounter > TimeStep)
	{
		myGameWorld.Update(TimeStep);
		TimerCounter -= TimeStep;
	}

	myGameWorld.Render();
}


void CGame::LogCallback( std::string aText )
{
}
