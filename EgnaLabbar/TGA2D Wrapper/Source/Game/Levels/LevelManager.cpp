#include "stdafx.h"
#include "LevelManager.h"
#include "..\Settings\Settings.h"
#include "..\Levels\Level.h"
#include "../Inventory/Inventory.h"
#include "../Player/Player.h"
#include <../CommonUtilities/InputWrapper/InputWrapper.h>
#include "../JsonParser/JsonSaver.h"
#include "Editor.h"
#include <string>
#include <Utility\MouseInputResolutionAdaption.h>
#include "../SoundManager/SoundManager.h"

Level* LevelManager::ourCurrentLevel;
Player* LevelManager::ourPlayer;
Editor* LevelManager::ourEditor;
LevelManager *LevelManager::ourInstance;

CommonUtilities::GrowingArray<Level> LevelManager::myLevels;

void LevelManager::Init(Player *aPlayer, Inventory *aInventory)
{
	GetInstance().InitInternal(aPlayer, aInventory);
}

void LevelManager::InitInternal(Player *aPlayer, Inventory *aInventory)
{
	ourPlayer = aPlayer;
	ourEditor = new Editor();

	JsonParser::InitLevels(myLevels, aInventory, ourPlayer);

	for (unsigned short i = 0; i < myLevels.Size(); i++)
	{
		if (myLevels[i].GetIsCurrentLevel() == true)
		{
			ourCurrentLevel = &myLevels[i];
			ourPlayer->SetPlayerScaleValues(ourCurrentLevel->GetScaleSlope(), ourCurrentLevel->GetScaleConstant());
			ourPlayer->SetPosition(ourCurrentLevel->GetPlayerStartPosition());

			SoundManager::PlayLoadedSound(ourCurrentLevel->GetBackgroundSoundName(), true);
		}
	}
	ourPlayer->Init(ourCurrentLevel->GetBorderList());
}
//											  ||||||||||
//Will be put in separate Editor-class later  VVVVVVVVVV

void LevelManager::CheckForInput()
{
	GetInstance().CheckForInputInternal();
}

void LevelManager::CheckForInputInternal()
{
	if (CommonUtilities::InputWrapper::GetMouseButtonDown(CommonUtilities::enumMouseButtons::eRight) == true)
	{
		if (ourCurrentLevel->IsCurrentlyEditing() == false)
		{
			//ourPlayer->SetGotoPosition(MouseFix::GetFixedMousePosition());
		}
		else
		{
			ourCurrentLevel->EditNodes(MouseFix::GetFixedMousePosition());
		}
		//SetPlayerGotoPosition(MouseFix::GetFixedMousePosition());

	}
	if (CommonUtilities::InputWrapper::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eLeft) == true)
	{
		if (ourCurrentLevel->IsCurrentlyEditing() == true)
		{
			ourCurrentLevel->SplitNodes(MouseFix::GetFixedMousePosition());
		}
	}
	if (CommonUtilities::InputWrapper::GetKeyPressed(DIK_E))
	{
		ourCurrentLevel->SetEditMode();
		ourPlayer->UpdateBorders(ourCurrentLevel->GetBorderList());
	}
	if (CommonUtilities::InputWrapper::GetKeyPressed(DIK_S))
	{
		JsonSaver save;
		save.SaveToFile(ourCurrentLevel->GetBorderList(),ourCurrentLevel->GetMyLevelName());
	}
}


void LevelManager::Update(const float aDeltaTime)
{
	GetInstance().UpdateInternal(aDeltaTime);
}

void LevelManager::UpdateInternal(const float aDeltaTime)
{
	ourCurrentLevel->Update(aDeltaTime);
	CheckForInputInternal();
	ourPlayer->Update(aDeltaTime);
}


void LevelManager::Draw()
{
	GetInstance().DrawInternal();
}

void LevelManager::DrawInternal()
{
	ourCurrentLevel->Draw();
	ourPlayer->Draw();
	ourCurrentLevel->DrawPole();
}

void LevelManager::ChangeLevel(const std::string &aLevelName)
{
	GetInstance().ChangeLevelInternal(aLevelName);
}

void LevelManager::ChangeLevelInternal(const std::string &aLevelName)
{
	SoundManager::StopAllSounds();
	for (unsigned short i = 0; i < myLevels.Size(); i++)
	{
		if (myLevels[i].GetMyLevelName() == aLevelName)
		{
			
			ourCurrentLevel = &myLevels[i];
			ourPlayer->SetPlayerScaleValues(ourCurrentLevel->GetScaleSlope(), ourCurrentLevel->GetScaleConstant());

			//ourPlayer->SetPosition(ourCurrentLevel->GetPlayerStartPosition());

			ourPlayer->UpdateBorders(ourCurrentLevel->GetBorderList());
			SoundManager::PlayLoadedSound(ourCurrentLevel->GetBackgroundSoundName(), true);
			return;

		}
	}

	bool validation = false;
	DL_ASSERT(validation, ("Level was not found by this name: " + aLevelName).c_str());

}

void LevelManager::SetPlayerGotoPosition(Vector2f aPosition)
{
	if (ourCurrentLevel->IsCurrentlyEditing() == false)
	{
		ourPlayer->SetGotoPosition(aPosition);
	}
}
