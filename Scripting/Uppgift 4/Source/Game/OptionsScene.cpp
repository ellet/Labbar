#include "stdafx.h"
#include "OptionsScene.h"
#include <Engine\GUI\GUILoader.h>
#include "Game\GenericGameMessages.h"
#include <Engine\GenericEngineMessages.h>
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include <Engine/Rendering/DXRenderer.h>

OptionsScene::OptionsScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "OptionsScene")
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/Options.json");
	BindGUIFunctions();
	myInputListener = std::make_shared<SB::InputListener>();

	SetInitialCheckedStates();
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

	////Update fullscreen state in GUI to match current configuration (in case the player alt-enters)
	//if (SB::Engine::GetRenderer().IsFullscreen() == true)
	//{
	//	myGUI->GetGUIElement("ToggleFullscreen")->SetSprite("Assets/Gui/Options/fullscreen.dds");
	//}
	//else
	//{
	//	myGUI->GetGUIElement("ToggleFullscreen")->SetSprite("Assets/Gui/Options/fullscreenUnchecked.dds");
	//}

	Scene::Update(aDeltaTime);
}

void OptionsScene::Render()
{
	Scene::Render();
}

void OptionsScene::OnEnter()
{
	myGUI = SB::Engine::GetGUILoader().LoadGUI("Assets/Data/Gui/Options.json");
}

void OptionsScene::Return()
{
	SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
}

void OptionsScene::ToggleBloom()
{/*
	if (myBloomToggle == false)
	{
		myGUI->GetGUIElement("ToggleBloom")->SetSprite("Assets/Gui/Options/bloom.dds");
	}
	else
	{
		myGUI->GetGUIElement("ToggleBloom")->SetSprite("Assets/Gui/Options/bloomUnchecked.dds");
	}*/
	SB::Engine::GetEngineSettings().ToggleBloom();
	myBloomToggle = !myBloomToggle;
}

void OptionsScene::ToggleMotionBlur()
{/*
	if (myMotionBlurToggle == false)
	{
		myGUI->GetGUIElement("ToggleMotionBlur")->SetSprite("Assets/Gui/Options/motionBlur.dds");
	}
	else
	{
		myGUI->GetGUIElement("ToggleMotionBlur")->SetSprite("Assets/Gui/Options/motionBlurUnchecked.dds");
	}*/
	SB::Engine::GetEngineSettings().ToggleMotionBlur();
	myMotionBlurToggle = !myMotionBlurToggle;
}

void OptionsScene::ToggleFullscreen()
{/*
	if (SB::Engine::GetRenderer().IsFullscreen() == true)
	{
		myGUI->GetGUIElement("ToggleFullscreen")->SetSprite("Assets/Gui/Options/fullscreenUnchecked.dds");
		SB::Engine::GetRenderer().SetFullscreen(false);
	}
	else
	{
		myGUI->GetGUIElement("ToggleFullscreen")->SetSprite("Assets/Gui/Options/fullscreen.dds");
		SB::Engine::GetRenderer().SetFullscreen(true);
	}*/
}

void OptionsScene::SetInitialCheckedStates()
{
//	//Init fullscreen state in GUI to match current configuration
//	if (SB::Engine::GetRenderer().IsFullscreen() == true)
//	{
//		myGUI->GetGUIElement("ToggleFullscreen")->SetSprite("Assets/Gui/Options/fullscreen.dds");
//	}
//	else
//	{
//		myGUI->GetGUIElement("ToggleFullscreen")->SetSprite("Assets/Gui/Options/fullscreenUnchecked.dds");
//	}
//
//
//	//Init bloom & motion blur states
//	myBloomToggle = SB::Engine::GetEngineSettings().GetUseBloom();
//	myMotionBlurToggle = SB::Engine::GetEngineSettings().GetUseMotionBlur();
//
//	if (myBloomToggle == true)
//		myGUI->GetGUIElement("ToggleBloom")->SetSprite("Assets/Gui/Options/bloom.dds");
//	else
//		myGUI->GetGUIElement("ToggleBloom")->SetSprite("Assets/Gui/Options/bloomUnchecked.dds");
//
//	if (myMotionBlurToggle == true)
//		myGUI->GetGUIElement("ToggleMotionBlur")->SetSprite("Assets/Gui/Options/motionBlur.dds");
//	else
//		myGUI->GetGUIElement("ToggleMotionBlur")->SetSprite("Assets/Gui/Options/motionBlurUnchecked.dds");
//
//
//	//Init audio channel states
//	unsigned short ambienceVolume = SB::Engine::GetSoundManager().GetAmbientVolume();
//	unsigned short sfxVolume = SB::Engine::GetSoundManager().GetSFXVolume();
//	unsigned short bgmVolume = SB::Engine::GetSoundManager().GetBGMVolume();
//
//	if (ambienceVolume > 0)
//		myGUI->GetGUIElement("ToggleAmbient")->SetSprite("Assets/Gui/Options/ambience.dds");
//	else
//		myGUI->GetGUIElement("ToggleAmbient")->SetSprite("Assets/Gui/Options/ambienceUnchecked.dds");
//
//	if (sfxVolume > 0)
//		myGUI->GetGUIElement("ToggleSFX")->SetSprite("Assets/Gui/Options/sfx.dds");
//	else
//		myGUI->GetGUIElement("ToggleSFX")->SetSprite("Assets/Gui/Options/sfxUnchecked.dds");
//
//	if (bgmVolume > 0)
//		myGUI->GetGUIElement("ToggleBGM")->SetSprite("Assets/Gui/Options/bgm.dds");
//	else
//		myGUI->GetGUIElement("ToggleBGM")->SetSprite("Assets/Gui/Options/bgmUnchecked.dds");
//
}

void OptionsScene::BindGUIFunctions()
{
	/*myBoundGUIFunctions["Return"] = std::bind(&OptionsScene::Return, this);
	myBoundGUIFunctions["ToggleBloom"] = std::bind(&OptionsScene::ToggleBloom, this);
	myBoundGUIFunctions["ToggleMotionBlur"] = std::bind(&OptionsScene::ToggleMotionBlur, this);
	myBoundGUIFunctions["ToggleFullscreen"] = std::bind(&OptionsScene::ToggleFullscreen, this);

	myBoundGUIFunctions["ToggleSFX"] = std::bind(&OptionsScene::ToggleSFX, this);
	myBoundGUIFunctions["ToggleBGM"] = std::bind(&OptionsScene::ToggleBGM, this);
	myBoundGUIFunctions["ToggleAmbient"] = std::bind(&OptionsScene::ToggleAmbient, this);
*/
}


void OptionsScene::ToggleAmbient()const
{/*
	unsigned short volume = static_cast<unsigned short> (abs(static_cast<short> (SB::Engine::GetSoundManager().GetAmbientVolume()) - 100));
	SB::Engine::GetSoundManager().SetAmbientVolume(volume);
	if (volume > 0)
	{
		myGUI->GetGUIElement("ToggleAmbient")->SetSprite("Assets/Gui/Options/ambience.dds");
	}
	else
	{
		myGUI->GetGUIElement("ToggleAmbient")->SetSprite("Assets/Gui/Options/ambienceUnchecked.dds");
	}*/
}

void OptionsScene::ToggleSFX()const
{/*
	unsigned short currentVolume = SB::Engine::GetSoundManager().GetSFXVolume();
	unsigned short newVolume;
	if (currentVolume > 0)
		newVolume = 0;
	else
		newVolume = 60;

	SB::Engine::GetSoundManager().SetSFXVolume(newVolume);

	if (newVolume > 0)
	{
		myGUI->GetGUIElement("ToggleSFX")->SetSprite("Assets/Gui/Options/sfx.dds");
	}
	else
	{
		myGUI->GetGUIElement("ToggleSFX")->SetSprite("Assets/Gui/Options/sfxUnchecked.dds");
	}*/
}

void OptionsScene::ToggleBGM() const
{/*
	unsigned short volume = static_cast<unsigned short> (abs(static_cast<short> (SB::Engine::GetSoundManager().GetBGMVolume()) - 100));
	SB::Engine::GetSoundManager().SetBGMVolume(volume);
	if (volume > 0)
	{
		myGUI->GetGUIElement("ToggleBGM")->SetSprite("Assets/Gui/Options/bgm.dds");
	}
	else
	{
		myGUI->GetGUIElement("ToggleBGM")->SetSprite("Assets/Gui/Options/bgmUnchecked.dds");
	}*/
}

void OptionsScene::ToggleDialog() const
{
	unsigned short volume = static_cast<unsigned short> (abs(static_cast<short> (SB::Engine::GetSoundManager().GetDialogVolume()) - 100));
	SB::Engine::GetSoundManager().SetDialogVolume(volume);
}
