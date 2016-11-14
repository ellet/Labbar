#include "stdafx.h"
#include "LevelSelectScene.h"
#include <Engine\GUI\GUILoader.h>
#include "Game\GenericGameMessages.h"
#include <Engine\GenericEngineMessages.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>

LevelSelectScene::LevelSelectScene(SB::PostMasterState & aPostMasterState)
	: Scene(aPostMasterState, "Level Select")
{
	BindGUIFunctions();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/LevelSelect.json");
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
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	SB::Engine::GetGUILoader().SetCurrentGUI("Assets/Data/Gui/LevelSelect.json");
}

void LevelSelectScene::StartLevel(unsigned short aLevelPath)
{
	std::cout << "Starting level " << aLevelPath << std::endl;
	SB::PostMaster::Post(SelectedLevelMessage(aLevelPath));
}

void LevelSelectScene::BackToMainMenu()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void LevelSelectScene::BindGUIFunctions()
{
	myBoundGUIFunctions["Start Level 1"] = std::bind(&LevelSelectScene::StartLevel, this, 0);
	myBoundGUIFunctions["Start Level 2"] = std::bind(&LevelSelectScene::StartLevel, this, 1);
	myBoundGUIFunctions["Start Level 3"] = std::bind(&LevelSelectScene::StartLevel, this, 2);
	myBoundGUIFunctions["Start Level 4"] = std::bind(&LevelSelectScene::StartLevel, this, 3);
	myBoundGUIFunctions["Back To MainMenu"] = std::bind(&LevelSelectScene::BackToMainMenu, this);
}

