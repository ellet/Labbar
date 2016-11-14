#include "stdafx.h"
#include "InputBlockComponent.h"


InputBlockComponent::InputBlockComponent() : SB::Subscriber<SB::RawMouseMoveMessage>(1000000)
{
}


InputBlockComponent::~InputBlockComponent()
{
}

SB::ReceiveResult InputBlockComponent::Receive(const SB::RawMouseMoveMessage& aMessage)
{
	return SB::ReceiveResult::eStop;
}
