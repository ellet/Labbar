#include "stdafx.h"
#include "Game.h"
#include <Engine\Window\WindowsWindow.h>
#include <Engine\Window\WindowMessage.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Utilities\Time\Stopwatch.h>
#include <Engine\Scene\JsonScene.h>
#include <Engine\FileWatcher\FileChangeWatcher.h>
#include <Engine\Scene\SceneManager.h>
#include <Engine/Debugging/CommandLineParameters.h>
#include <Engine\PostMaster.h>
#include <Engine/Scripting/EngineScriptRegistrationList.h>
#include <Engine/GUI/GUILoader.h>
#include <Engine/Window/Cursor/Cursor.h>
#include <Engine/Scene/Messages/CreateSceneMessage.h>
#include <Engine\GenericEngineMessages.h>
#include "Game\ComponentList.h"
#include "Game\Scripting\GameScriptRegistrationList.h"
#include "Scene\SceneRegistry.h"
#include "Game\DebugRegistry.h"
#include "Scene\SceneManagerSceneRegistry.h"
#include "Scene/ModelViewerScene/ModelViewerScene.h"
#include "Game/Scenes\TestScenes\PhysxTestScene.h"
#include "GUITestScene.h"
#include "Scene\TheLabs\LabbAIScene.h"
#include "Scene\TheLabs\AIEventHandler.h"
#include "Scene\TheLabs\PollingStation.h"

Game * Game::ourInstance = nullptr;

Game::Game()
{
	AIEventHandler::Create();
	PollingStation::Create();
}

Game::~Game()
{
	AIEventHandler::Destroy();
	PollingStation::Destroy();
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
	myWindow->SetTitle("Sandbucket - AI Project");
	myWindow->SetSize(SB::Size<int>(SB::Engine::GetEngineSettings().GetResolution().x, SB::Engine::GetEngineSettings().GetResolution().y));
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
	SB::Time frameTimes[10];
	size_t totalFrameCount = 0;

	

	while (myWindow->IsOpen() && myShouldBeRunning == true)
	{
		totalFrameCount++;

		SB::Time deltaTime = CLAMP(watch.GetElapsedTime(), 0.f, 0.2f);

		SB::Engine::SetDeltaTime(deltaTime);
		frameTimes[totalFrameCount % 10] = deltaTime;

		if (totalFrameCount > 10)
		{
			float total = 0.f;
			for (int i=0; i<10; i++)
			{
				total += frameTimes[i].InSeconds();
			}
			SB::Time averageDeltaTime = static_cast<float>(total / 10.f);

			if (deltaTime.InSeconds() > averageDeltaTime.InSeconds() * 2.0f)
			{
#ifndef Publish
				SB::Engine::GetLogger().LogWarning("Hitching Warning: Frame {0} took {1}ms, which is more than {3} times the average frametime during the previous 10 frames ({2}ms)", totalFrameCount, deltaTime.InMilliseconds(), averageDeltaTime.InMilliseconds(), deltaTime.InSeconds() / averageDeltaTime.InSeconds());
#endif
			}
		}

		watch.Restart();


		// Capture the current scene preventing destruction of it until the end of the current frame
		std::shared_ptr<SB::Scene> currentScene = mySceneManager->GetCurrentScene();
		SB::PostMasterStateBinding sceneBinding = SB::PostMaster::Push(*currentScene);

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
	SB::Size<int> newSize;

	SB::WindowMessage message;
	while (myWindow->PollMessage(message))
	{
		switch (message.type)
		{
		case SB::WindowMessageType::eCloseButtonPressed:
			myWindow->Close();
			break;
		case SB::WindowMessageType::eSizeChanged:
			newSize = myWindow->GetSize();
			break;
		}
	}

	if (newSize.width > 0 && newSize.height > 0)
	{
		SB::Engine::GetInstance().GetRenderer().Resize(newSize.width, newSize.height);
		SB::PostMaster::Post(SB::WindowSizeChangedMessage(newSize.width, newSize.height));
	}
}

void Game::Initialize()
{
	mySceneManager = std::make_unique<SB::SceneManager>();

	SceneRegistry::RegisterScenes(*mySceneManager);
	Debug::RegisterGameScenes();

	
	mySceneManager->LoadPrefabs();

	std::string levelToStart = SB::CommandLineParameters::GetInstance().GetFirstValue("level", "");/*Assets/Data/emptyLevel.json*/

	if (levelToStart == "")
	{
		//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eMainMenu, SB::eSceneType::eMajor, nullptr));
		//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/JsonScenes/firstArena.json", "Assets/Skyboxes/skybox1.dds"));

		//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eYlfTest, SB::eSceneType::eMajor, nullptr));
		//mySceneManager->LoadScene<SB::ModelViewerScene>(SB::eSceneType::eMajor);
		//mySceneManager->LoadScene<PhysxTestScene>(SB::eSceneType::eMajor);
		mySceneManager->LoadScene<LabbAIScene>(SB::eSceneType::eMajor);
		// Go to menu if we were not passed a level
		//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eParticleEditor, SB::eSceneType::eMajor, nullptr));
#ifdef PUBLISH
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eSplashscreen, SB::eSceneType::eSub, nullptr));
#endif
		
		//SB::PostMaster::Post(SelectedLevelMessage(0));
		//SB::Engine::GetDebugger().LoadSceneAtIndex(0);
	}
	else
	{
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, levelToStart));
	}
}

void Game::Update(const SB::Time &aDeltaTime)
{
	SB::Engine::GetResourceManager().Update();
	SB::Engine::GetFileWatcher().PostChanges();
	SB::Engine::GetSoundManager().Update();

	SB::Engine::GetDebugger().Update();

	if ( SB::Engine::GetDebugger().CheckIfPaused() == false)
	{		
		mySceneManager->Update(aDeltaTime);
	}
}

void Game::Render()
{
	SB::Engine::GetInstance().GetRenderer().ClearFrame();

	mySceneManager->Render();
	mySceneManager->RenderGui();
	mySceneManager->CopyToBackbuffer();
	 
	SB::Engine::GetInstance().GetRenderer().Present();
}
