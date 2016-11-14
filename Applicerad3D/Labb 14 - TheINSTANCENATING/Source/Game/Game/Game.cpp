#include "stdafx.h"
#include "Game.h"
#include <Engine\Window\WindowsWindow.h>
#include <Engine\Window\WindowMessage.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Time\Stopwatch.h>
#include <Engine\Scene\JsonScene.h>
#include <Engine\FileWatcher\FileChangeWatcher.h>
#include <Engine\SplashScreen\SplashScreenScene.h>
#include "Engine\Scene\SceneManager.h"
#include "Game\Player\PlayerControllerComponent.h"
#include "Game\ComponentList.h"
#include <Engine/Debugging/CommandLineParameters.h>
#include <Engine/Component/CircleMovementComponent.h>
#include <Engine/Streak/StreakComponent.h>
#include "Engine\SoundManager\SoundManager.h"
#include <Engine\PostMaster.h>
#include <Engine\Scene\Messages\PopSceneMessage.h>
#include "Game\GenericGameMessages.h"
#include "Engine\GenericEngineMessages.h"
#include "Game\Scripting\GameScriptRegistrationList.h"
#include <Engine/Scripting/EngineScriptRegistrationList.h>
#include "Game/Scene/MainMenuScene.h"
#include "Engine/Scene/Messages/CreateSceneMessage.h"
#include "LevelProgressionManager\LevelProgressionManager.h"
#include <Engine/GUI/GUILoader.h>
#include <Engine/Window/Cursor/Cursor.h>
#include "Scene\SceneRegistry.h"
#include "Game\DebugRegistry.h"

Game * Game::ourInstance = nullptr;



Game::Game()
{
	
}

Game::~Game()
{
}

void Game::CreateInstance()
{
	assert(ourInstance == nullptr && "Instance already created");
	ourInstance = new Game();
}

void Game::DestroyInstance()
{
	assert(ourInstance != nullptr && "Instance not created");
	delete ourInstance;
	ourInstance = nullptr;
}

void Game::Start()
{
	myShouldBeRunning = true;

	SB::Engine::CreateInstance();
	RegisterGameComponents();

	myCursor = std::make_unique<SB::Cursor>();

	myWindow = std::make_unique<SB::WindowsWindow>(*myCursor);
	myWindow->SetTitle("Game Engine");
	myWindow->SetSize(SB::Size<int>(1280, 720));
	myWindow->Open();
	
	myWindow->SetCursorConfined(true);
	myWindow->SetCursorHidden(false);

	
	SB::Engine::GetInstance().GetRenderer().Initialize(myWindow->GetHandle(), myWindow->GetSize().width, myWindow->GetSize().height, false);

	SB::Engine::GetInstance().AttachDebugger(std::make_shared<SB::Debugger>(myWindow->GetHandle(), *myCursor));
	SB::Engine::Initialize();
	

	SB::EngineScriptRegistration::Register();
	GameScriptRegistration::Register();
	Initialize();
	DebugFunctions::RegisterFunctions();
	SB::Stopwatch watch;
	// SB::Stopwatch secondWatch;
	// SB::Time max;

	while (myWindow->IsOpen() && myShouldBeRunning == true)
	{
		SB::Time deltaTime = watch.GetElapsedTime();
		// if (deltaTime > max)
		// {
		// 	max = deltaTime;
		// }
		// if (secondWatch.GetElapsedTime() > 1.f)
		// {
		// 	std::cout << max.InSeconds() << " (" << 1.f / max.InSeconds() << ")" << std::endl;
		// 	max = 0.f;
		// 	secondWatch.Restart();
		// }
		watch.Restart();

		SB::PostMasterStateBinding sceneBinding = SB::PostMaster::Push(*mySceneManager->GetCurrentScene());

		SB::Engine::GetDebugger().NewFrame();

		ProcessMessages();

		Update(deltaTime);
		
		Render();

		SB::PostMaster::Post(SB::EndOfFrameMessage());
	}

	// Destroy our world releasing it's resources allowing the engine to shut down
	mySceneManager = nullptr;
	
	SB::Engine::GetDebugger().Shutdown();

	SB::Engine::GetResourceManager().CleanUp();

	SB::Engine::DestroyInstance();
}

SB::ReceiveResult Game::Receive(const SB::CloseGameMessage & aMessage)
{
	(aMessage);
	myShouldBeRunning = false;
	return SB::ReceiveResult::eContinue;
}

void Game::ProcessMessages()
{
	SB::WindowMessage message;
	while (myWindow->PollMessage(message))
	{
		switch (message.type)
		{
		case SB::WindowMessageType::eCloseButtonPressed:
			myWindow->Close();
			break;
		case SB::WindowMessageType::eSizeChanged:
			SB::Engine::GetInstance().GetRenderer().Resize(myWindow->GetSize().width, myWindow->GetSize().height);
			CreatePerspective();
			break;
		}
	}
}

void Game::Initialize()
{
	SB::Engine::GetInstance().GetGUILoader().CreateGUI("Assets/Data/Gui/GUIList.json");

	Debug::RegisterGameScenes();

	mySceneManager = std::make_unique<SB::SceneManager>();
	
	mySceneManager->LoadPrefabs();

	myLevelProgressionManager = std::make_unique<LevelProgressionManager>();
	
	std::string levelToStart = SB::CommandLineParameters::GetInstance().GetFirstValue("level", "");

	if (levelToStart == "")
	{
		// Go to menu if we were not passed a level
		//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eMainMenu, SB::eSceneType::eMajor, nullptr));
		
		//SB::PostMaster::Post(SelectedLevelMessage(0));
		SB::Engine::GetDebugger().LoadSceneAtIndex(2);
	}
	else
	{
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, levelToStart));
	}

	//mySceneManager->LoadScene<MainMenuScene>(SB::eSceneType::eMajor);
	
	CreatePerspective();
}

void Game::Update(const SB::Time &aDeltaTime)
{
	SB::Engine::GetResourceManager().Update();
	SB::Engine::GetFileWatcher().PostChanges();
	SB::Engine::GetSoundManager().Update();

	SB::Engine::GetDebugger().Update();

	if (mySceneManager->GetCurrentScene() != nullptr && SB::Engine::GetDebugger().CheckIfPaused() == false)
	{
		
		mySceneManager->GetCurrentScene()->Update(aDeltaTime);
	}
}

void Game::Render()
{
	SB::Engine::GetInstance().GetRenderer().ClearFrame();

	std::shared_ptr<SB::Scene> scene = mySceneManager->GetCurrentScene();

	if (scene != nullptr)
	{
		scene->Render();
		if (SB::Engine::GetDebugger().GetDebugState() == true)
		{
			scene->DebugRender();
		}
	}


	SB::Engine::GetInstance().GetRenderer().DoFullscreenEffects();

	if (scene != nullptr)
	{
		scene->RenderGui();
	}

	SB::Engine::GetInstance().GetRenderer().Present();
}

void Game::CreatePerspective()
{
	if (mySceneManager->GetCurrentScene() != nullptr)
	{
		mySceneManager->GetCurrentScene()->UpdatePerspective(60.f, static_cast<float>(myWindow->GetSize().width), static_cast<float>(myWindow->GetSize().height), 1000.f, 0.1f);
	}
}
