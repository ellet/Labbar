#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>
#include "GameWorld.h"

using namespace std::placeholders;


//#include <Rend/RenderConverter.h>
#include <CU/Timer/TimeManager.h>
#include <HUGRender/Renderer.h>


#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")
#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG


CGame::CGame()
{
	CU::TimeManager::Create();
	myGameWorld = new CGameWorld();
}


CGame::~CGame()
{
	CU::MainSingleton::Destroy();
	SAFE_DELETE(myGameWorld);
}


void CGame::Init(const std::wstring& aVersion)
{
	SingletonInit();

	unsigned short windowWidth = 1920;
	unsigned short windowHeight = 1080;

	GET_RENDERER.SetTargetResolution(CU::Vector2f(1920.f, 1080.f));

    DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = DX2D::eDebugFeature_Fps | DX2D::eDebugFeature_Mem | DX2D::eDebugFeature_Filewatcher | DX2D::eDebugFeature_Cpu | DX2D::eDebugFeature_Drawcalls;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = 1920;
	createParameters.myTargetHeight = 1080;
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
    myGameWorld->Init();

	GET_INPUT.Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());
}


void CGame::UpdateCallBack()
{
	CU::TimeManager::Update();
	GET_INPUT.Update();

	myGameWorld->Update(CU::TimeManager::GetDeltaTime());
	myGameWorld->Draw();

	GET_RENDERER.Draw();
	GET_RENDERER.SwitchBuffers();

	//RenderConverter::Draw();
	//RenderConverter::SwapBuffers();
}


void CGame::LogCallback( std::string aText )
{
}

void CGame::SingletonInit()
{
	CU::MainSingleton::Create();
	
	CU::MainSingleton::SetRenderer(new HUG::Renderer());
	//RenderConverter::Create();
	//RenderConverter::Init(CU::Vector2ui(1920, 1080));
}