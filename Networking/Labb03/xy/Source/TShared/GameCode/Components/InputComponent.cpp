#include "stdafx.h"
#include "InputComponent.h"
#include <GameCode/Components/ComponentIds.h>

#include <iostream>
#include "..\CommonUtilites\InputWrapper.h"
#include <GameCode\GameObject\GameObject.h>
unsigned int CInputComponent::myID = EComponentIds::EComponentIds_CInputComponent;

CInputComponent::CInputComponent()
	:myInputWrapper(nullptr)
{
}


CInputComponent::~CInputComponent()
{
}

void CInputComponent::Init(Input::InputWrapper* aInputWrapper)
{
	myInputWrapper = aInputWrapper;
}

void CInputComponent::OnMessage(CComponentMessageBase* /*aMessage*/)
{
}



void CInputComponent::Update(float /*aTimeDelta*/)
{
	if (!myInputWrapper)
	{
		return;
	}
	if (myInputWrapper->GetKeyDown(DIK_UPARROW) == true)
	{
		CComponentMessageOnInput inputMessage;
		inputMessage.myMovement = CComponentMessageOnInput::MOVE_UP;
		BroadcastMessage(&inputMessage);
		//MoveUp(aTimeDelta);
	}
	else if (myInputWrapper->GetKeyDown(DIK_DOWNARROW) == true)
	{
		CComponentMessageOnInput inputMessage;
		inputMessage.myMovement = CComponentMessageOnInput::MOVE_DOWN;
		BroadcastMessage(&inputMessage);
		//MoveDown(aTimeDelta);
	}

/*
	std::cout << "Inputcomponent: Sending a nice message to all!" << std::endl;
	CComponentMessageOnInput inputMessage;
	inputMessage.myData = 666;
	SendMessage(&inputMessage);*/

}

/*
unsigned int CInputComponent::GetId()
{
	return reinterpret_cast<int>(&GetId);
}*/
