#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <../include/time.h>


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
	myGameWorld.Init();
	
	imUpdating = false;
	imRendering = false;

	myDoneUpdateLock.lock();
	myDoneDrawLock.lock();
	myUpdateLock.lock();
	myDrawLock.lock();

	myUpdateThread = new std::thread(&CGame::UpdateThread, this, &myUpdateLock, &myDoneUpdateLock);
	myDrawThread = new std::thread(&CGame::DrawThread, this, &myDrawLock, &myDoneDrawLock);
	
}


void CGame::UpdateCallBack()
{
	//myUpdateLock.unlock();

	

	myGameWorld.SetDrawBuffer();

	//imUpdating = true;
	//imRendering = true;

	myUpdateLock.unlock();
	myDrawLock.unlock();

	//while (imUpdating == true);
	//while (imRendering == true);
	while (myDoneUpdateLock.try_lock() == false);
	while (myDoneDrawLock.try_lock() == false);
}

void CGame::UpdateThread(std::mutex * aUpdateLock, std::mutex * aDoneUpdateLock)
{
	bool doGame = true;

	while (doGame == true)
	{
		while (aUpdateLock->try_lock() == false);
		//while (imUpdating == false);
		DoUpdate();
		//imUpdating = false;

		aDoneUpdateLock->unlock();
	}
}

void CGame::DoUpdate()
{
	

	myTimeManager.Update();
	myGameWorld.Update(static_cast<float>(myTimeManager.GetDeltaTime()));
	myGameWorld.SetDraw();

	
}

void CGame::DrawThread(std::mutex * aDrawLock, std::mutex * aDoneDrawLock)
{
	bool doGame = true;

	while (doGame == true)
	{
		while (aDrawLock->try_lock() == false);
		//while (imRendering == false);
		DoDraw();
		//imRendering = false;
		aDoneDrawLock->unlock();
	}
}

void CGame::DoDraw()
{
	

	myGameWorld.DoDraw();

	
}

void CGame::LogCallback( std::string aText )
{
}
