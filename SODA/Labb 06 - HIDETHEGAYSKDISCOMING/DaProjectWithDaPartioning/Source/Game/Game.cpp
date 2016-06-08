#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>

#include <Rend/RenderConverter.h>
#include <PostMaster/SingletonPostMaster.h>

#include <CU/NameSpaceAliases.h>

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
	CU::TimeManager::Create();
	RenderConverter::Create();
	SingletonPostMaster::Create();
}


CGame::~CGame()
{
}


void CGame::Init(const std::wstring& aVersion)
{
	unsigned short windowWidth = 1024;
	unsigned short windowHeight = 1024;


    DX2D::SEngineCreateParameters createParameters;
	//createParameters.myActivateDebugSystems = DX2D::eDebugFeature_Fps | DX2D::eDebugFeature_Mem | DX2D::eDebugFeature_Filewatcher | DX2D::eDebugFeature_Cpu | DX2D::eDebugFeature_Drawcalls;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = windowWidth;
	createParameters.myTargetHeight = windowHeight;
	createParameters.myAutoUpdateViewportWithWindow = false;
    createParameters.myClearColor.Set( 0.2f, 0.4f, 0.7f, 1.0f );
	
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
	GetInput::Create();
	GetInput::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());

	RenderConverter::Init(CU::Vector2ui(1024, 1024));
    myGameWorld.Init();
}


void CGame::UpdateCallBack()
{
	CU::TimeManager::Update();

	GetInput::Update();
	myGameWorld.Update(CU::TimeManager::GetDeltaTime());
	myGameWorld.Draw();
}


void CGame::LogCallback( std::string aText )
{
}