#include "stdafx.h"
#include "PlayDialogEvent.h"
#include "../../Interface/Dialog/DialogManager.h"

PlayDialogEvent::PlayDialogEvent(std::string &aAvatarID, std::string &aText)
{
	myAvatarID = aAvatarID;
	myText = aText;
}

PlayDialogEvent::~PlayDialogEvent()
{
}

void PlayDialogEvent::OneShotEvent()
{
	DialogManager::GetInstance()->AddDialog(myText, myAvatarID);
}
