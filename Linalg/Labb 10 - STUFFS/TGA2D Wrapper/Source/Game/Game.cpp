#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>
#include <functional>
#include <time.h>
#include <InputWrapper\InputWrapper.h>

//#include 

using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")

#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG

#include <RendererManager\RenderManager.h>
#include <Utility\ScreenResolution.h>
#include <DLDebug\DL_Debug.h>
#include <Timer\TimeManager.h>
#include <CollisionManager/CollisionManager.h>

namespace CU = CommonUtilities;

CGame::CGame()
{
}
CGame::~CGame()
{
	RenderManager::Destroy();
	ScreenResolution::Destroy();
	CU::TimeManager::Destroy();
	CU::InputWrapper::Destroy();
	CollisionManager::Destroy();
}

void CGame::Init()
{

	DL_Debug::Debug::Create();

	unsigned short windowWidth = 800;//static_cast<unsigned short>(mySettings.myResolution.x);
	unsigned short windowHeight = 600;//static_cast<unsigned short>(mySettings.myResolution.y);

	//TODO::Set window size.

	DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = true;
	createParameters.myInitFunctionToCall = std::bind(&CGame::InitCallBack, this);
	createParameters.myUpdateFunctionToCall = std::bind(&CGame::UpdateCallBack, this);
	createParameters.myLogFunction = std::bind(&CGame::LogCallback, this, _1);
	createParameters.myWindowHeight = windowHeight;
	createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myClearColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
	createParameters.myStartInFullScreen = false;

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


	CU::TimeManager::Create();
	ScreenResolution::Create();
	RenderManager::Create();
	CU::InputWrapper::Create();
	CU::InputWrapper::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));
	CollisionManager::Create();

	myTestState = new TestState();
	myTestState->Init();


	mySyncronizer.AddThreadMethod(&CGame::ThreadFunctionUpdate, *this);
	mySyncronizer.AddThreadMethod(&CGame::ThreadFunctionRender, *this);
	mySyncronizer.Start();
	
	
}
void CGame::UpdateCallBack()
{
	
	mySyncronizer.Run();
	
	RenderManager::SwapBuffers();

}
void CGame::LogCallback(std::string aText)
{
	DL_PRINT(aText.c_str());
}

void CGame::ThreadFunctionUpdate()
{

	CommonUtilities::TimeManager::Update();
	CU::InputWrapper::Update();

	
	myTestState->Update(CU::TimeManager::GetDeltaTime());
	myTestState->Draw();
}
void CGame::ThreadFunctionRender()
{
	RenderManager::Render();
}