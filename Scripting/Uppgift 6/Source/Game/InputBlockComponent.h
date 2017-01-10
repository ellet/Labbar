#pragma once
#include "Engine\Component\BaseComponent.h"

namespace SB
{
	struct RawMouseMoveMessage;
}

class InputBlockComponent :
	public SB::BaseComponent, public SB::Subscriber<SB::RawMouseMoveMessage>
{
public:
	InputBlockComponent();
	~InputBlockComponent();

	SB::ReceiveResult Receive(const SB::RawMouseMoveMessage& aMessage) override;

private:
};

