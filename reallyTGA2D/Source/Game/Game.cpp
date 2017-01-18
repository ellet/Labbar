#include "stdafx.h"
#include <tga2d/Engine.h>
#include "Game.h"

#include <tga2d/error/error_manager.h>

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


bool CGame::Init(const std::wstring& aVersion, HWND aHWND)
{
	unsigned short windowWidth = 1920;
	unsigned short windowHeight = 1080;


    Tga2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps | Tga2D::eDebugFeature_Mem | Tga2D::eDebugFeature_Filewatcher | Tga2D::eDebugFeature_Cpu | Tga2D::eDebugFeature_Drawcalls | Tga2D::eDebugFeature_OptimiceWarnings;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
	createParameters.myWinProcCallback = std::bind(&CGame::WinProc, this, _1, _2, _3, _4);
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = windowWidth;
	createParameters.myTargetHeight = windowHeight;
	createParameters.myWindowSetting = Tga2D::EWindowSetting_Overlapped;
	createParameters.myAutoUpdateViewportWithWindow = false;
    createParameters.myClearColor.Set(0.0f / 255.0f, 143.0f / 255.0f, 212.0f / 255.0f, 1.0f );
	createParameters.myStartInFullScreen = false;

	if (aHWND != nullptr)
	{
		createParameters.myHwnd = new HWND(aHWND);
	}
	
	std::wstring architecture = L"32 Bit";
#ifdef _AMD64_
	architecture = L"64 Bit";
#endif
	std::wstring appname = L"TGA 2D RELEASE [" + aVersion + L"] " + architecture;
#ifdef _DEBUG
	appname = L"TGA 2D DEBUG  [" + aVersion + L"] " + architecture;
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

    Tga2D::CEngine::CreateInstance( createParameters );

    if( !Tga2D::CEngine::GetInstance()->Start() )
    {
        ERROR_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
		return false;
    }

	return true;
}


LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CGame::InitCallBack()
{
    myGameWorld.Init();
}


void CGame::UpdateCallBack()
{
	const float timeDelta = 1.0f / 60.0f;
	myGameWorld.Update(timeDelta);
}


void CGame::LogCallback( std::string aText )
{
}
