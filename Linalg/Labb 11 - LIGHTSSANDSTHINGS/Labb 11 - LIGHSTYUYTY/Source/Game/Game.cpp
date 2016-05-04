#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>
#include "BIGLAMP.h"

#include <functional>
#include <../include/time.h>
#include "BaseGameStructure\GameObjectsManager.h"
#include <iostream>
#include <string>


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
	srand(static_cast<unsigned int>(time(0)));

	unsigned short windowWidth = 1024;
	unsigned short windowHeight = 768;

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
	if( !DX2D::CEngine::GetInstance()->Start() )
	{
		ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
	}


}


void CGame::InitCallBack()
{
	//DL_Debug::Debug::Create();
	BIGLAMP::Create(Vector3f(0.f, 0.f, 1.f), Vector4f(1.f, 1.0f, 1.0f, 1.f));
	GameObjectsManager::CreateGameObjectsManager();


	myGameWorld.Init();
}


void CGame::UpdateCallBack()
{
	myTimeManager.Update();
	myGameWorld.Update(static_cast<float>(myTimeManager.GetDeltaTime() ) );

	myGameWorld.Draw();
}

void CGame::LogCallback( std::string aText )
{
}
