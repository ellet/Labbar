#include "stdafx.h"
#include "LevelSelectScene.h"
#include <Engine\GUI\GUILoader.h>
#include "Game\GenericGameMessages.h"
#include <Engine\GenericEngineMessages.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include <Engine/GUI/ButtonGUIElement.h>
#include <Engine/Scene/Messages/CreateSceneMessage.h>

LevelSelectScene::LevelSelectScene(SB::PostMasterState & aPostMasterState)
	: Scene(aPostMasterState, "Level Select")
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/LevelSelect.json");
	BindGUIFunctions();
	myInputListener = std::make_shared<SB::InputListener>();
}


LevelSelectScene::~LevelSelectScene()
{
	myInputListener = nullptr;
}

void LevelSelectScene::Update(const SB::Time & aDeltaTime)
{
	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eEscape))
	{
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	}

	Scene::Update(aDeltaTime);
}

void LevelSelectScene::Render()
{
	Scene::Render();
}

void LevelSelectScene::OnEnter()
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/LevelSelect.json");
}

void LevelSelectScene::StartLevel(unsigned short aLevelPath)
{
#ifndef Publish
	std::cout << "Starting level " << aLevelPath << std::endl;
#endif
	switch (aLevelPath)
	{
	case 1:
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/JsonScenes/firstArena.json", "Assets/Skyboxes/skybox1.dds"));
		break;
	case 2:
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/JsonScenes/firstArena.json", "Assets/Skyboxes/skybox1.dds"));
		break;
	case 3:
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/JsonScenes/firstArena.json", "Assets/Skyboxes/skybox1.dds"));
		break;
	case 4:
		SB::PostMaster::Post(SB::CreateSceneMessage(SB::eSceneClass::eJSON, SB::eSceneType::eMajor, nullptr, "Assets/Data/JsonScenes/firstArena.json", "Assets/Skyboxes/skybox1.dds"));
		break;
	default:
		Error("Level number not supported, consider life choices etc.");
		break;
	}
	SB::Engine::GetSoundManager().PostEvent("Stop_MainTheme");
}

void LevelSelectScene::BackToMainMenu()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void LevelSelectScene::BindGUIFunctions()
{
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Level 1")->BindClickFunction(std::bind(&LevelSelectScene::StartLevel, this, 0));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Level 2")->BindClickFunction(std::bind(&LevelSelectScene::StartLevel, this, 1));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Level 3")->BindClickFunction(std::bind(&LevelSelectScene::StartLevel, this, 2));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Level 4")->BindClickFunction(std::bind(&LevelSelectScene::StartLevel, this, 3));
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Back To MainMenu")->BindClickFunction(std::bind(&LevelSelectScene::BackToMainMenu, this));
}

