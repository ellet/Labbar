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
#include "Game\Scene\EnemyTestScene.h"
#include "Game\Scene\SprintReviewScene.h"
#include "Game\Scene\PbrTestScene.h"
#include "Game\Scene\PlayerTestScene.h"
#include "Game\Scene\CollisionTestScene.h"
#include "Game\Component\Shooting\PlayerShootComponent.h"
#include "Game\Scene\ParticleTestScene.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Start()
{
	SB::Engine::CreateInstance();

	myWindow = std::make_unique<SB::WindowsWindow>();
	myWindow->SetTitle("Game Engine");
	myWindow->SetSize(SB::Size<int>(1280, 720));
	myWindow->Open();
	
	myWindow->SetCursorLocked(true);

	SB::Engine::GetInstance().GetRenderer().Initialize(myWindow->GetHandle(), myWindow->GetSize().width, myWindow->GetSize().height, false);

	SB::Engine::GetInstance().AttachDebugger(std::make_shared<SB::Debugger>(myWindow->GetHandle()));

	Initialize();

	SB::Stopwatch watch;

	while (myWindow->IsOpen())
	{
		SB::Time deltaTime = watch.GetElapsedTime();
		watch.Restart();

		SB::Engine::GetDebugger().NewFrame();

		ProcessMessages();

		Update(deltaTime);
		
		Render();
	}

	// Destroy our world releasing it's resources allowing the engine to shut down
	mySceneManager = nullptr;

	SB::Engine::DestroyInstance();
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

	/*mySceneManager->LoadJsonScene("Assets/Data/testscene.json");
	auto player = mySceneManager->GetCurrentScene()->CreateGameObject();
	player->SetIdentifier("Player");
	auto && shootComponent = mySceneManager->GetCurrentScene()->GetComponentFactory<PlayerShootComponent>()->CreateComponent();
	player->AddComponent(shootComponent);*/
	
	mySceneManager->LoadScene<ParticleTestScene>();

	CreatePerspective();
}

void Game::Update(const SB::Time &aDeltaTime)
{
	SB::Engine::GetResourceManager().Update();
	SB::Engine::GetFileWatcher().PostChanges();

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
		mySceneManager->GetCurrentScene()->UpdatePerspective(60.f, static_cast<float>(myWindow->GetSize().width), static_cast<float>(myWindow->GetSize().height), 10000000.f, 0.1f);
	}
}
