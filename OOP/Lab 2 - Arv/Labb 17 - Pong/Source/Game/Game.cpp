#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>

#include <Timer\TimeManager.h>
#include <InputWrapper\InputWrapper.h>


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
	unsigned short windowWidth = 800;
	unsigned short windowHeight = 600;


    DX2D::SEngineCreateParameters createParameters;
    createParameters.myActivateDebugSystems = true;
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );

    std::wstring appname = L"TGA 2D RELEASE";
#ifdef _DEBUG
    appname = L"TGA 2D DEBUG";
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

    DX2D::CEngine::CreateInstance( createParameters );

	//myTimerManager.CreateTimer();

    if( !DX2D::CEngine::GetInstance()->Start() )
    {
        ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
    }

}


void CGame::InitCallBack()
{
	CommonUtilities::TimeManager::Create();
	CommonUtilities::InputWrapper::Create();
    myGameWorld.Init();
}


void CGame::UpdateCallBack()
{
	//myTimerManager.UpdateTimers();

	CommonUtilities::TimeManager::Update();

	myGameWorld.Update(CommonUtilities::TimeManager::GetDeltaTime());
}


void CGame::LogCallback( std::string aText )
{
}
