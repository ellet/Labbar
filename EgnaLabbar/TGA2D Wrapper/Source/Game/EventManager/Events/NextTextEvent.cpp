#include "stdafx.h"
#include "NextTextEvent.h"

#include "../../Interface/Dialog/DialogManager.h"

NextTextEvent::NextTextEvent()
{
}


NextTextEvent::~NextTextEvent()
{
}

void NextTextEvent::OneShotEvent()
{
	DialogManager::GetInstance()->NextDialog();
}
