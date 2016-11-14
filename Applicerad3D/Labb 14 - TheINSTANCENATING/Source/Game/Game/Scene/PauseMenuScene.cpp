#include "stdafx.h"
#include "PauseMenuScene.h"
#include <Engine\GUI\GUILoader.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include <Engine/Scene/Messages/CreateSceneMessage.h>
#include "Engine/SoundManager/SoundManager.h"

PauseMenuScene::PauseMenuScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "Pause Menu")
{
	BindGUIFunctions();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/PauseMenu.json");

	std::shared_ptr<SB::Texture> backgroundTexture;
	backgroundTexture = SB::Engine::GetInstance().GetResourceManager().Get<SB::Texture>("Assets/Gui/PauseMenu/pauseMenuBackground.dds");
	myBackgroundSprite = std::make_shared<SB::Sprite>();
	myBackgroundSprite->SetTexture(backgroundTexture);
	backgroundTexture = nullptr;

	myInputListener = std::make_shared<SB::InputListener>();
}

PauseMenuScene::~PauseMenuScene()
{
	myBackgroundSprite = nullptr;
}

void PauseMenuScene::OnEnter()
{
	SB::Scene::OnEnter();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	SB::Engine::GetGUILoader().SetCurrentGUI("Assets/Data/Gui/PauseMenu.json");
}

void PauseMenuScene::Render()
{
	myBackgroundSprite->Render();
}

void PauseMenuScene::Update(const SB::Time & aDeltaTime)
{
	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eEscape))
	{
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	}

	SB::Scene::Update(aDeltaTime);
}

void PauseMenuScene::ReturnToMainMenu()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eToFirst));
}

void PauseMenuScene::Resume()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void PauseMenuScene::RunOptions()
{
	SB::Engine::GetSoundManager().PostEvent("Play_PlayerHitEnemy");
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eOptions, SB::eSceneType::eMajor, nullptr));
}

void PauseMenuScene::BindGUIFunctions()
{
	myBoundGUIFunctions["Return To Main Menu"] = std::bind(&PauseMenuScene::ReturnToMainMenu, this);
	myBoundGUIFunctions["Resume"] = std::bind(&PauseMenuScene::Resume, this);
	myBoundGUIFunctions["Options"] = std::bind(&PauseMenuScene::RunOptions, this);
}
