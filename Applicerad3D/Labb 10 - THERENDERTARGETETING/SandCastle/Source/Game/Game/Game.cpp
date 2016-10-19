#include "stdafx.h"
#include "Game.h"
#include <Engine\Window\WindowsWindow.h>
#include <Engine\Window\WindowMessage.h>
#include <Engine\Rendering\DXRenderer.h>
#include <Engine\Camera\Camera.h>
#include <Engine\Time\Stopwatch.h>
#include <Engine\Scene\JsonScene.h>
#include "Game\Scene\SlideShowScene.h"
#include "Game\Scene\InstancedTestScene.h"
#include <Engine\FileWatcher\FileChangeWatcher.h>
#include "Game\Scene\LightingTestScene.h"
#include <Engine\SplashScreen\SplashScreenScene.h>
#include "Game\Scene\SoundTestScene.h"
#include "Engine\Scene\SceneManager.h"

#include "TestObjectEventSystemScene.h"
#include "Game\Scene\PbrTestScene.h"
#include "Game\Scene\PlayerTestScene.h"
#include "Game\Scene\TestCollision\CollisionTestScene.h"
#include "Game\Player\PlayerControllerComponent.h"
#include "Game\ComponentList.h"
#include <Engine/Debugging/CommandLineParameters.h>
#include "Scene\TestCollision\TestEnemyCollisionScene.h"
#include <Engine/Component/CircleMovementComponent.h>
#include <Engine/Streak/StreakComponent.h>
#include "..\Engine\Engine\SoundManager\SoundManger.h"
#include "Game\Scene\TestCollision\CollisionTestScene.h"
#include "Game\Scene\TextScene.h"
#include "Game\Component\Shooting\ShootingComponent.h"
#include <Engine\PostMaster.h>
#include <Engine\Scene\SceneStack\PopSceneMessage.h>
#include <Engine\GenericGameMessages.h>

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
	myShouldBeRunning = true;

	SB::Engine::CreateInstance();
	RegisterGameComponents();

	myWindow = std::make_unique<SB::WindowsWindow>();
	myWindow->SetTitle("Game Engine");
	myWindow->SetSize(SB::Size<int>(1280, 720));
	myWindow->Open();
	
	myWindow->SetCursorConfined(true);
	myWindow->SetCursorHidden(true);

	SB::Engine::GetInstance().GetRenderer().Initialize(myWindow->GetHandle(), myWindow->GetSize().width, myWindow->GetSize().height, false);

	SB::Engine::GetInstance().AttachDebugger(std::make_shared<SB::Debugger>(myWindow->GetHandle()));

	Initialize();

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

		SB::Engine::GetDebugger().NewFrame();

		ProcessMessages();

		Update(deltaTime);
		
		Render();

		SB::PostMaster::Post(SB::EndOfFrameMessage());
	}

	// Destroy our world releasing it's resources allowing the engine to shut down
	mySceneManager = nullptr;

	SB::Engine::GetResourceManager().CleanUp();

	std::cin.get();

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
	mySceneManager = std::make_unique<SB::SceneManager>();
	
	mySceneManager->LoadJsonScene(SB::CommandLineParameters::GetInstance().GetFirstValue("level", "Assets/Data/tutorialLevel.json").c_str());

	
	// SB::ObjectPtr myEnemy = mySceneManager->GetCurrentScene()->CreateGameObject("Enemy ship");
	// myEnemy->CreateComponent<SB::CircleMovementComponent>();
	// //myEnemy->CreateComponent<ParticleComponent>()->SpawnParticles(1024);
	// myEnemy->CreateComponent<SB::StreakComponent>();
	// 
	// myEnemy->SetPosition(player->GetTransformation().GetPosition() + player->GetRotation().GetForward() * 3.f);
	// 
	// SB::ObjectPtr rotationRoot = mySceneManager->GetCurrentScene()->CreateGameObject("Rotation Root");
	// rotationRoot->SetParent(myEnemy);
	// 
	// 
	// 
	// myEnemy->Initialize();

	CreatePerspective();
}

void Game::Update(const SB::Time &aDeltaTime)
{
	SB::Engine::GetResourceManager().Update();
	SB::Engine::GetFileWatcher().PostChanges();
	SB::Engine::GetSoundManager().Update();	

	if (mySceneManager->GetCurrentScene() != nullptr)
	{
		mySceneManager->GetCurrentScene()->Update(aDeltaTime);
	}
}

void Game::Render()
{
	SB::Engine::GetInstance().GetRenderer().ClearFrame();

	if (mySceneManager->GetCurrentScene() != nullptr)
	{
		mySceneManager->GetCurrentScene()->Render();
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
