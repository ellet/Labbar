#include "stdafx.h"
#include "OptionsScene.h"
#include <Engine\GUI\GUILoader.h>
#include "Game\GenericGameMessages.h"
#include <Engine\GenericEngineMessages.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>

OptionsScene::OptionsScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "OptionsScene")
{
	BindGUIFunctions();
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/Options.json");
	myInputListener = std::make_shared<SB::InputListener>();
	myBloomToggle = SB::Engine::GetRenderer().HasBloom();
}


OptionsScene::~OptionsScene()
{
	myInputListener = nullptr;
}

void OptionsScene::Update(const SB::Time & aDeltaTime)
{
	if (myInputListener->GetPressedThisFrame(SB::KeyboardKey::eEscape))
	{
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
	}

	Scene::Update(aDeltaTime);
}

void OptionsScene::Render()
{
	Scene::Render();
}

void OptionsScene::OnEnter()
{
	SB::Engine::GetGUILoader().SetFunctions(myBoundGUIFunctions);
	SB::Engine::GetGUILoader().SetCurrentGUI("Assets/Data/Gui/Options.json");
}

void OptionsScene::Return()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void OptionsScene::Derpy()
{
	if (myBloomToggle == true)
	{
		myGUI->GetGUIElement("ToggleBloom")->SetSprite("Assets/Gui/Options/bloom.dds");
	}
	else
	{
		myGUI->GetGUIElement("ToggleBloom")->SetSprite("Assets/Gui/Options/bloomUnchecked.dds");
	}
	SB::Engine::GetRenderer().ToggleBloom();
	myBloomToggle = !myBloomToggle;
}

void OptionsScene::BindGUIFunctions()
{
	myBoundGUIFunctions["Return"] = std::bind(&OptionsScene::Return, this);
	myBoundGUIFunctions["ToggleBloom"] = std::bind(&OptionsScene::Derpy, this);
}

