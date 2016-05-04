#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>
#include "Inventory\Inventory.h"
#include <functional>
#include <time.h>
#include "TestMainLoop.h"
#include "States\NewStateSwitch.h"
#include "JsonParser\JsonParser.h"
#include <InputWrapper\InputWrapper.h>
#include "Interface\InterfaceManager.h"
#include <input/MouseInput/MouseInput.h>
//#include 

using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")

#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG

#include <StateManager\StateManager.h>
#include <RendererManager\RenderManager.h>
#include <BaseClasses\FactoryGameObject\FactoryGameObject.h>
#include <Utility\ScreenResolution.h>
#include <DLDebug\DL_Debug.h>
#include <Timer\TimeManager.h>
#include <CollisionManager/CollisionManager.h>
#include "Object/ObjectManager.h"
#include "Interface/Dialog/DialogManager.h"
#include "Object/ElemenTypes.h"
#include <thread>

namespace CU = CommonUtilities;

CGame::CGame()
	: myIsFullscreen(false)
{
}
CGame::~CGame()
{

	delete myPlayer;
	myPlayer = nullptr;

	delete myInventory;
	myInventory = nullptr;

	StateManager::Destroy();
	FactoryGameObject::Destroy();
	RenderManager::Destroy();
	ScreenResolution::Destroy();
	CU::TimeManager::Destroy();
	CU::InputWrapper::Destroy();
	CollisionManager::Destroy();
	JsonParser::Destroy();
	EventManager::Destroy();
	LevelManager::Destroy();
	InterfaceManager::Destroy();
	ObjectManager::Destroy();
	SoundManager::Destroy();
}

void CGame::Init(const std::wstring& aVersion)
{

	DL_Debug::Debug::Create();
	SoundManager::Create();
	JsonParser::Create();
	EventManager::Create();
	EventManager::Init();
	JsonParser::InitSettings(mySettings);

	unsigned short renderWidth = 1920;
	unsigned short renderHeight = 1080;
	
	DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = true;
	createParameters.myInitFunctionToCall = std::bind(&CGame::InitCallBack, this);
	createParameters.myUpdateFunctionToCall = std::bind(&CGame::UpdateCallBack, this);
	createParameters.myLogFunction = std::bind(&CGame::LogCallback, this, _1);
	createParameters.myWindowHeight = renderHeight;
	createParameters.myWindowWidth = renderWidth;
	createParameters.myRenderHeight = renderHeight;
	createParameters.myRenderWidth = renderWidth;
	createParameters.myClearColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
	createParameters.myStartInFullScreen = myIsFullscreen;

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
	}


}

void CGame::InitCallBack()
{

	if (myIsFullscreen == false)
	{

		unsigned short windowWidth = static_cast<unsigned short>(mySettings.myResolution.x);
		unsigned short windowHeight = static_cast<unsigned short>(mySettings.myResolution.y);

		SetWindowPos(*DX2D::CEngine::GetInstance()->GetHWND(), 0, 0, 0, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	}

	myPlayer = new Player();
	myInventory = new Inventory();
	DialogManager::Create();
	SoundManager::LoadSound();
	ObjectManager::Create();
	JsonParser::InitPlayer(myPlayer);
	CU::TimeManager::Create();
	ScreenResolution::Create();
	RenderManager::Create();
	FactoryGameObject::Create();
	StateManager::Create();
	MouseInput::Create();
	MouseInput::SetInventoryPointer(myInventory);
	LevelManager::Create();
	CU::InputWrapper::Create();
	CU::InputWrapper::Initialize(DX2D::CEngine::GetInstance()->GetHInstance(), (*DX2D::CEngine::GetInstance()->GetHWND()));
	CollisionManager::Create();
	
	JsonParser::InitActionWheel(&MouseInput::GetActionWheel());
	CommonUtilities::GrowingArray<InterfaceBase*> interfaces;
	interfaces.Init(5);
	InterfaceManager::Create();
	InterfaceManager::Init();
	JsonParser::InitInterfaces(interfaces, myInventory);

	for (unsigned short i = 0; i < interfaces.Size(); i++)
	{
		InterfaceManager::AddInterface(interfaces[static_cast<int>(i)]);
	}


	JsonParser::InitDialog(*DialogManager::GetInstance());
	InterfaceManager::AddInterface(DialogManager::GetInstance());
	LevelManager::Init(myPlayer, myInventory);


	ThreadData * tempData = new ThreadData();
	tempData->SetThread(new std::thread(&CGame::ThreadFunctionUpdate, this, tempData));
	mySyncronizer.AddThread(tempData);

	tempData = new ThreadData();
	tempData->SetThread(new std::thread(&CGame::ThreadFunctionRender, this, tempData));
	mySyncronizer.AddThread(tempData);

	/*mySyncronizer.AddThreadMethod(&CGame::ThreadFunctionUpdate, *this);
	mySyncronizer.AddThreadMethod(&CGame::ThreadFunctionRender, *this);
	mySyncronizer.Start();*/

	

	AddStates();
	StateManager::SetActiveState(StateHandling::GetStateEnum(mySettings.myStartState));
}
void CGame::UpdateCallBack()
{
	//mySyncronizer.Run();
	mySyncronizer.ContinueAllMyThreads();
	mySyncronizer.WaitForAllMyThreads();

	RenderManager::SwapBuffers();

}
void CGame::LogCallback(std::string aText)
{
	DL_PRINT(aText.c_str());
}

void CGame::ThreadFunctionUpdate(ThreadData * const myThreadData)
{
	while (mySyncronizer.AllThreadsShouldRun() == true)
	{
		myThreadData->WaitForOtherThreadsToBedone();
		myThreadData->StartedWorking();

		CommonUtilities::TimeManager::Update();
		CU::InputWrapper::Update();


		StateManager::Update(CommonUtilities::TimeManager::GetDeltaTime());
		StateManager::Draw();

		myThreadData->DoneThread();
	}
}
void CGame::ThreadFunctionRender(ThreadData * const myThreadData)
{
	while (mySyncronizer.AllThreadsShouldRun() == true)
	{
		myThreadData->WaitForOtherThreadsToBedone();
		myThreadData->StartedWorking();

		RenderManager::Render();

		myThreadData->DoneThread();
	}
}

void CGame::AddStates()
{
	//TODO::LESS UGLY SOLUTION, SHOULD STILL FIX
	CU::GrowingArray<BaseState*> tempArrayOfStates;
	tempArrayOfStates.Init(static_cast<unsigned short>(enumGameStates::enumLength));
	tempArrayOfStates.Resize(static_cast<unsigned short>(enumGameStates::enumLength));

	for (unsigned short iState = 0; iState < static_cast<unsigned short>(enumGameStates::enumLength); ++iState)
	{
		tempArrayOfStates[iState] = StateHandling::CreateNewState(static_cast<enumGameStates>(iState));
	}

	StateManager::AddStates(tempArrayOfStates);
	StateManager::InitAllState();
}