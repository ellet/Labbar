#include "stdafx.h"
#include "CreditsScene.h"
#include <Engine\GUI\GUILoader.h>
#include "Game\GenericGameMessages.h"
#include <Engine\GenericEngineMessages.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include <Engine/GUI/ButtonGUIElement.h>

CreditsScene::CreditsScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "CreditsScene")
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/Credits.json");
	myInputListener = std::make_shared<SB::InputListener>();
	BindGUIFunctions();
}


CreditsScene::~CreditsScene()
{
	myInputListener = nullptr;
}

void CreditsScene::Update(const SB::Time & aDeltaTime)
{
	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eEscape))
	{
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	}

	Scene::Update(aDeltaTime);
}

void CreditsScene::Render()
{
	Scene::Render();
}

void CreditsScene::OnEnter()
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/Credits.json");
}

void CreditsScene::BackToMainMenu()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void CreditsScene::BindGUIFunctions()
{
	myGUI->GetGUIElement<SB::ButtonGUIElement>("Back To MainMenu")->BindClickFunction(std::bind(&CreditsScene::BackToMainMenu, this));
}

