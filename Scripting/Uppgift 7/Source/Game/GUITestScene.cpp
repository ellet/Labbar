#include "stdafx.h"
#include "GUITestScene.h"
#include <Engine\GUI\GUILoader.h>
#include <Engine/GUI/ButtonGUIElement.h>


GUITestScene::GUITestScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "CreditScene")
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/MainMenu.json");
	BindGUIFunctions();
}


GUITestScene::~GUITestScene()
{
	
}

void GUITestScene::Update(const SB::Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void GUITestScene::Render()
{
	Scene::Render();
}

void GUITestScene::OnEnter()
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/MainMenu.json");
}

void GUITestScene::TestClickFunction()
{
	std::cout << "CLICK" << std::endl;
}

void GUITestScene::TestHoverFunction()
{
	std::cout << "HOVER" << std::endl;
}

void GUITestScene::TestKeyFunction()
{
	myGUI->GetGUIElement<SB::GUIElement>("1024")->SetActive(!myGUI->GetGUIElement<SB::GUIElement>("1024")->GetActive());
}

void GUITestScene::BindGUIFunctions()
{
	myGUI->GetGUIElement<SB::ButtonGUIElement>("1024")->BindClickFunction(std::bind(&GUITestScene::TestClickFunction, this));
	myGUI->GetGUIElement<SB::GUIElement>("root")->BindKeyBindFunction(std::bind(&GUITestScene::TestKeyFunction, this), SB::KeyboardKey::eC);
	myGUI->GetGUIElement<SB::GUIElement>("512")->BindHoverFunction(std::bind(&GUITestScene::TestHoverFunction, this));
}
