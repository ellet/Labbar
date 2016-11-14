#include "stdafx.h"
#include "CreditScene.h"
#include <Engine\GUI\GUILoader.h>
#include "Game\GenericGameMessages.h"
#include <Engine\GenericEngineMessages.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>

CreditScene::CreditScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "CreditScene")
{
	BindGUIFunctions();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/Credit.json");
	myInputListener = std::make_shared<SB::InputListener>();
}


CreditScene::~CreditScene()
{
	myInputListener = nullptr;
}

void CreditScene::Update(const SB::Time & aDeltaTime)
{
	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eEscape))
	{
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	}

	Scene::Update(aDeltaTime);
}

void CreditScene::Render()
{
	Scene::Render();
}

void CreditScene::OnEnter()
{
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	SB::Engine::GetGUILoader().SetCurrentGUI("Assets/Data/Gui/Credit.json");
}

void CreditScene::BackToMainMenu()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void CreditScene::BindGUIFunctions()
{
	myBoundGUIFunctions["Back To MainMenu"] = std::bind(&CreditScene::BackToMainMenu, this);
}

