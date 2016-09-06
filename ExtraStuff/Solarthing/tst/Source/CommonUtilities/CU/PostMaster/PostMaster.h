#pragma once

#include <CU/PostMaster/ReceiverTypes.h>
#include "CU/PostMaster/MessageReceiver.h"

class MessageReceiver;

struct Receiver
{
	Receiver()
	{
		myReceiver = nullptr;
		myOrder = ReceiverOrder::eDefault;
	}
	Receiver(MessageReceiver & aReceiver, ReceiverOrder aPriority = ReceiverOrder::eDefault)
	{
		myReceiver = &aReceiver;
		myOrder = aPriority;
	}

	bool operator == (const Receiver & aRight) const
	{
		return myReceiver == aRight.myReceiver;
	}

	MessageReceiver * myReceiver;
	ReceiverOrder myOrder;
};


class PostMaster
{
public:
	PostMaster();
	~PostMaster();
	void AddReceiver(const ReceiverTypes aTypeToRecieve, MessageReceiver & aReceiverToAdd, const ReceiverOrder aPriority = ReceiverOrder::eDefault);
	void RemoveReceiver(const ReceiverTypes aTypeUnsubscribe, MessageReceiver & aReceiverToRemove);
	void RemoveReceiver(MessageReceiver &aReceiver);

	template <typename MessageType>
	void PostMessage(const MessageType & aMessageToSend);

private:
	CU::GrowingArray<CU::GrowingArray<Receiver>> myReceivers;
};


template <typename MessageType>
void PostMaster::PostMessage(const MessageType & aMessageToSend)
{
	for (unsigned short iReceiver = 0; iReceiver < myReceivers[static_cast<unsigned short>(aMessageToSend.myType)].Size(); ++iReceiver)
	{
		DL_ASSERT(myReceivers[static_cast<unsigned short>(aMessageToSend.myType)].Size() > 0, "ERROR: No Receiver to recieve message");
		MessageReceiver* explainginReceiver = myReceivers[static_cast<unsigned short>(aMessageToSend.myType)][iReceiver].myReceiver;

		if (explainginReceiver->RecieveMessage(aMessageToSend) == false)
		{
			break;
		}
	}
}