#include "stdafx.h"
#include "DialogManager.h"

#include <InputWrapper\InputWrapper.h>

#include <tga2d\sprite\sprite.h>
#include <tga2d\text\text.h>

#include <Input\MouseInput\MouseInput.h>

const unsigned short constMaxDialogs = 64;

DialogManager *DialogManager::ourInstance;

void DialogManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new DialogManager();
	}
}
void DialogManager::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void DialogManager::LoadSpeakerSprite(const std::string &aSpritePath, const std::string &aSpriteID)
{

	DX2D::CSprite *avatar = new DX2D::CSprite(aSpritePath.c_str());

	avatar->SetColor(DX2D::CColor(1.f, 1.f, 1.f, 1.f));
	avatar->SetSize(DX2D::Vector2f(1.f, 1.f));

	mySpriteMap[aSpriteID] = avatar;

}

void DialogManager::LoadFont(const std::string &aFontPath)
{
	myDialogRenderer.LoadFont(aFontPath);
}

void DialogManager::Draw() const
{
	if (GetIsShowing() == true)
	{
		myDialogRenderer.DrawDialog(*myDialogList[0], myDialogTextIndex);
	}
}

void DialogManager::AddDialog(const std::string &aText, const std::string &aSpriteID)
{

	MouseInput::SetMouseState(enumMouseStates::eTalkMode);

	Dialog &dialog = myDialogQueue.Allocate();
	dialog.SetText(aText);
	if (aSpriteID != "")
	{
		dialog.SetCharacterSprite(mySpriteMap.at(aSpriteID));
	}
	else
	{
		dialog.SetCharacterSprite(nullptr);
	}

	myDialogList.Add(&dialog);
	myShowInterface = true;

}
void DialogManager::ClearDialogs()
{
	myDialogQueue.Clear();
	myDialogList.RemoveAll();
	myShowInterface = false;
	MouseInput::SetMouseState(enumMouseStates::eNeutralMode);
}

void DialogManager::NextDialog()
{

	if (GetIsShowing() == false)
	{
		return;
	}

	myDialogTextIndex = myDialogRenderer.NextDialogIndex(*myDialogList[0], myDialogTextIndex);

	if (myDialogList[0]->GetText().size() <= myDialogTextIndex)
	{

		myDialogQueue.Deallocate(*myDialogList[0]);

		for (unsigned short i = 0; i < myDialogList.Size() - 1; ++i)
		{
			myDialogList[i] = myDialogList[i + 1];
		}

		myDialogList.RemoveCyclicAtIndex(myDialogList.Size() - 1);
		myDialogTextIndex = 0;

		if (myDialogList.Size() == 0)
		{
			ClearDialogs();
		}

	}

}

DialogManager::DialogManager()
	:myDialogQueue(constMaxDialogs), myDialogList(constMaxDialogs), myDialogTextIndex(0)
{
	myShowInterface = false;
}
DialogManager::~DialogManager()
{
	for (std::map<std::string, DX2D::CSprite*>::iterator iterator = mySpriteMap.begin(); iterator != mySpriteMap.end(); ++iterator)
	{
		delete iterator->second;
	}
}
