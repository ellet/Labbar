#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>

#include <Rend/RenderConverter.h>
#include "GameWorld.h"

#include <Input/SingletonIsometricInputWrapper.h>

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
	SingletonPostMaster::Create();
	myGameWorld = new CGameWorld();
}


CGame::~CGame()
{
	myFileOutput.close();
	SAFE_DELETE(myGameWorld);
}


bool CGame::Init(/*const std::wstring& aVersion,*/ HWND aHWND)
{
	
	

	const std::wstring& aVersion(L"APA");
	myFileOutput.open("error.txt");
	OutputDebugString(L"APA");
	unsigned short windowWidth = 800;
	unsigned short windowHeight = 800;

	RenderConverter::Create();
	RenderConverter::Init(CU::Vector2ui(windowWidth, windowHeight));

    DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = DX2D::eDebugFeature_Fps | DX2D::eDebugFeature_Mem | DX2D::eDebugFeature_Filewatcher | DX2D::eDebugFeature_Cpu | DX2D::eDebugFeature_Drawcalls;
    
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = windowWidth;
	createParameters.myTargetHeight = windowHeight;
	createParameters.myAutoUpdateViewportWithWindow = true;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );

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

    DX2D::CEngine::CreateInstance( createParameters );

    if( !DX2D::CEngine::GetInstance()->Start() )
    {
        ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
		return false;
    }

	return true;
}


void CGame::InitCallBack()
{
	IsometricInput::Create();
	IsometricInput::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), *DX2D::CEngine::GetInstance()->GetHWND());
	

    myGameWorld->Init();
}


void CGame::UpdateCallBack()
{
	const float deltaTime = 1.0f / 120.0f;
	IsometricInput::Update();
	myGameWorld->Update(deltaTime);
	myGameWorld->Draw();

	RenderConverter::Draw();
	RenderConverter::SwapBuffers();
}


void CGame::LogCallback( std::string aText )
{
	DL_PRINT(aText.c_str());
	myFileOutput << aText.c_str() << std::endl;
	myFileOutput.flush();
}
