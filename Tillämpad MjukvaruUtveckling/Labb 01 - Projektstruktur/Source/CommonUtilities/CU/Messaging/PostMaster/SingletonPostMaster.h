#pragma once

#include <CU/Messaging/PostMaster/ReceiverTypes.h>
#include "CU/Messaging/PostMaster/MessageReceiver.h"


/*

NOT FUNCTIONAL


*/

class MessageReceiver;

//struct Receiver
//{
//	Receiver()
//	{
//		myReceiver = nullptr;
//		myOrder = ReceiverOrder::eDefault;
//	}
//	Receiver(MessageReceiver & aReceiver, ReceiverOrder aPriority = ReceiverOrder::eDefault)
//	{
//		myReceiver = &aReceiver;
//		myOrder = aPriority;
//	}
//
//	bool operator == (const Receiver & aRight) const
//	{
//		return myReceiver == aRight.myReceiver;
//	}
//
//	MessageReceiver * myReceiver;
//	ReceiverOrder myOrder;
//};

class SingletonPostMaster
{
public:
	static void Create();
	static void Destroy();
	static void AddReceiver(const ReceiverTypes aTypeToRecieve, MessageReceiver & aReceiverToAdd, const ReceiverOrder aPriority = ReceiverOrder::eDefault);
	static void RemoveReceiver(const ReceiverTypes aTypeUnsubscribe, MessageReceiver & aReceiverToRemove);
	static void RemoveReceiver(MessageReceiver &aReceiver);
	static bool CheckIfExists();
	
	template <typename MessageType>
	static inline void PostMessage(const MessageType & aMessageToSend);
private:
	SingletonPostMaster();
	~SingletonPostMaster();

	template <typename MessageType>
	void InternalPostMessage(const MessageType & aMessageToSend);

	static SingletonPostMaster * ourInstance;

	static inline SingletonPostMaster & GetInstance();

	CU::GrowingArray<CU::GrowingArray<Receiver>> myReceivers;
};

template <typename MessageType>
void SingletonPostMaster::PostMessage(const MessageType & aMessageToSend)
{
	GetInstance().InternalPostMessage(aMessageToSend);
}

template <typename MessageType>
void SingletonPostMaster::InternalPostMessage(const MessageType & aMessageToSend)
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

inline SingletonPostMaster & SingletonPostMaster::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "PostMaster pointer is being used but it is nullptr");
	return *ourInstance;
}

//#define SendPostMessage(message) SingletonPostMaster::PostMessage((message));
