#pragma once
#include "CU/Messaging/PostMaster/ReceiverTypes.h"

struct BaseMessage;


class MessageReceiver
{
public:
	virtual ~MessageReceiver()
	{}

	virtual bool ReceiveMessage(const BaseMessage & aMessage);

	ReceiverOrder myReceiverOrder;
protected:
	MessageReceiver()
	{
		myReceiverOrder = ReceiverOrder::eDefault;
	}
};