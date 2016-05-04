#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>

#include <DLDebug/DL_Debug.h>
#include "Renderer.h"
#include <InputWrapper/InputWrapper.h>


using namespace std::placeholders;


#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")

#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG


CGame::CGame()
{
	DL_Debug::Debug::Create();
	Renderer::Create();
	CU::InputWrapper::Create();
}


CGame::~CGame()
{
}


void CGame::Init(const std::wstring& aVersion)
{
	unsigned short windowWidth = 1280;
	unsigned short windowHeight = 720;


    DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = eDebugFeature_Fps | eDebugFeature_Mem | eDebugFeature_Filewatcher | eDebugFeature_Cpu | eDebugFeature_Drawcalls;
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = 1280;
	createParameters.myTargetHeight = 720;
	createParameters.myAutoUpdateViewportWithWindow = false;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );
	
	std::wstring appname = L"TGA 2D RELEASE [" + aVersion + L"]";
#ifdef _DEBUG
	appname = L"TGA 2D DEBUG  [" + aVersion + L"]";
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

	

    DX2D::CEngine::CreateInstance( createParameters );

    if( !DX2D::CEngine::GetInstance()->Start() )
    {
        ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
    }


}


void CGame::InitCallBack()
{
    myGameWorld.Init();
	CU::InputWrapper::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());
}


void CGame::UpdateCallBack()
{
	const float deltaTime = 1.0f / 120.0f;
	myGameWorld.Update(deltaTime);
}


void CGame::LogCallback( std::string aText )
{
}