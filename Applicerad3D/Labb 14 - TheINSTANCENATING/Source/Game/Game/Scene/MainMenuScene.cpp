#include "stdafx.h"
#include "MainMenuScene.h"
#include <Engine\GUI\GUILoader.h>
#include <Engine/Scene/Messages/CreateSceneMessage.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include "Engine/SoundManager/SoundManager.h"
#include "Game/GenericGameMessages.h"
#include <Engine/Component/ModelComponent.h>
#include <Engine/Sprite/SpriteEffect.h>
#include <Engine/Rendering/SpriteRenderer.h>


MainMenuScene::MainMenuScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "MainMenu")
{
	BindGUIFunctions();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/MainMenu.json");
	SB::Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");

	SB::ObjectPtr myCockpit = CreateAndAddModel("Cockpit", "Assets/Models/Player/Cockpit/cockpit.fbx", SB::Vector3f(0.f, 0.f, 0.f), SB::Vector3f::One);
	myCockpit->GetComponent<SB::ModelComponent>()->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * SB::Matrix44f::CreateRotateAroundY(Pi));
	SB::ComponentPtr<SB::ModelComponent> mc = myCockpit->CreateComponent<SB::ModelComponent>();
	mc->SetModel("Assets/Models/Player/CockpitFrame/cockpitFrame.fbx");
	mc->SetMatrix(SB::Matrix44f::CreateScale(0.01f, 0.01f, 0.01f) * SB::Matrix44f::CreateRotateAroundY(Pi));
	myCockpit->Initialize();

	myNoiseTexture = SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Textures/noise2.dds");
	myWarpdriveExitEffect = std::make_shared<SB::SpriteEffect>("shaders/warpdrive/warpdrive.fx", "PShaderExiting");
	myWarpdriveEnterEffect = std::make_shared<SB::SpriteEffect>("shaders/warpdrive/warpdrive.fx", "PShaderEntering");
	myWarpDriveCBuffer = std::make_shared<SB::ConstantBuffer<WarpDriveData>>();
}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Update(const SB::Time & aDeltaTime)
{
	myWarpDriveTimer += aDeltaTime;


	Scene::Update(aDeltaTime);
}

void MainMenuScene::Render()
{
	
	Scene::Render();

	if (myWarpDriveTimer > 0.f)
	{
		myWarpDriveCBuffer->UpdateData(WarpDriveData
		{
			SB::Engine::GetRenderer().GetRenderTargetResolution(),
			myWarpDriveTimer.InSeconds(),
			0.f
		});
		myWarpDriveCBuffer->BindToPS(1);

		SB::Engine::GetRenderer().GetSpriteRenderer().RenderFullscreenQuad(myNoiseTexture, myWarpdriveExitEffect);
	}
}

void MainMenuScene::OnEnter()
{
	Scene::OnEnter();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	SB::Engine::GetGUILoader().SetCurrentGUI("Assets/Data/Gui/MainMenu.json");
}

void MainMenuScene::OnExit()
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void MainMenuScene::StartGame()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eParticleEditor, SB::eSceneType::eMajor, nullptr));
	SB::PostMaster::Post(SelectedLevelMessage(0));
	//SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/tutorialLevel.json"));
}

void MainMenuScene::RunLevelSelect()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eLevelSelect, SB::eSceneType::eMajor, nullptr));
}

void MainMenuScene::RunCredits()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eCredit, SB::eSceneType::eMajor, nullptr));
}

void MainMenuScene::RunOptions()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eOptions, SB::eSceneType::eMajor, nullptr));
}

void MainMenuScene::QuitGame()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void MainMenuScene::PlayHoverOverButtonSound()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
}

void MainMenuScene::BindGUIFunctions()
{
	myBoundGUIFunctions["Start Game"] = std::bind(&MainMenuScene::StartGame, this);
	myBoundGUIFunctions["Level Select"] = std::bind(&MainMenuScene::RunLevelSelect, this);
	myBoundGUIFunctions["Credits"] = std::bind(&MainMenuScene::RunCredits, this);
	myBoundGUIFunctions["Options"] = std::bind(&MainMenuScene::RunOptions, this);
	myBoundGUIFunctions["Quit Game"] = std::bind(&MainMenuScene::QuitGame, this);
	myBoundGUIFunctions["Button Hover Sound"] = std::bind(&MainMenuScene::PlayHoverOverButtonSound, this);
}
