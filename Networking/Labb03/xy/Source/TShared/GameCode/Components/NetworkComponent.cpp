#include "stdafx.h"
#include "NetworkComponent.h"
#include "Messages\NetworkCallback.h"
#include "ComponentIds.h"


unsigned int NetworkComponent::myID = EComponentIds::EComponentIds_CINetworkComponent;

NetworkComponent::NetworkComponent()
{
	myCallback = nullptr;
}


NetworkComponent::~NetworkComponent()
{
}

void NetworkComponent::SetCallback(NetworkCallback & aCallback)
{
	myCallback = &aCallback;
}

void NetworkComponent::OnMessage(CComponentMessageBase* aMessage)
{
	if (myCallback == nullptr)
	{
		Error("Callback is nullptr");
	}
	
	CComponentMessageOnInput* message = static_cast<CComponentMessageOnInput*>(aMessage);
	myCallback->TranslateComponentMessage(*message);
}


