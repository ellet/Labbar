#include "stdafx.h"
#include "MainMenuScene.h"
#include <Engine\GUI\GUILoader.h>
#include <Engine/Scene/Messages/CreateSceneMessage.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include "Game/GenericGameMessages.h"
#include <Engine/Component/ModelComponent.h>
#include <Engine/Sprite/SpriteEffect.h>
#include <Engine/Rendering/SpriteRenderer.h>
#include <Utilities/Randomizer/Randomizer.h>
#include <Engine/Component/Movement/RandomRotationComponent.h>
#include <Engine/GUI/ButtonGUIElement.h>


MainMenuScene::MainMenuScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "MainMenu")
{
	SB::Engine::GetSoundManager().SetSFXVolume(60);
	SB::Engine::GetSoundManager().SetAmbientVolume(100);
	SB::Engine::GetSoundManager().SetBGMVolume(100);

	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/MainMenu.json");
	BindGUIFunctions();

	SB::Engine::GetSoundManager().LoadBank("Audio/SoundBanks/level1.bnk");
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
}

void MainMenuScene::OnEnter()
{
	Scene::OnEnter();
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/MainMenu.json");
	SB::Engine::GetSoundManager().PostEvent("Play_MainTheme");
}

void MainMenuScene::OnExit()
{
	//throw std::logic_error("The method or operation is not implemented.");
}

void MainMenuScene::StartGame()
{
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/JsonScenes/firstArena.json", "Assets/Skyboxes/skybox1.dds"));
	SB::Engine::GetSoundManager().PostEvent("Stop_MainTheme");
}

void MainMenuScene::RunLevelSelect()
{
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eLevelSelect, SB::eSceneType::eMajor, nullptr));
}

void MainMenuScene::RunCredits()
{
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eCredits, SB::eSceneType::eMajor, nullptr));
}

void MainMenuScene::RunOptions()
{
	SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eOptions, SB::eSceneType::eMajor, nullptr));
}

void MainMenuScene::QuitGame()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	SB::Engine::GetSoundManager().PostEvent("Stop_MainTheme");
}

void MainMenuScene::BindGUIFunctions()
{
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Start Game")->BindClickFunction(std::bind(&MainMenuScene::StartGame, this));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Level Select")->BindClickFunction(std::bind(&MainMenuScene::RunLevelSelect, this));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Credits")->BindClickFunction(std::bind(&MainMenuScene::RunCredits, this));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Options")->BindClickFunction(std::bind(&MainMenuScene::RunOptions, this));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Quit Game")->BindClickFunction(std::bind(&MainMenuScene::QuitGame, this));
}
