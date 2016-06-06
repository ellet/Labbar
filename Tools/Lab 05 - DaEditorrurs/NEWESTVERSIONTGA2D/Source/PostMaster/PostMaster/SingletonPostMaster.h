#pragma once
#include <CU/DLDebug/DL_Debug.h>
#include <Message/RecieverTypes.h>
#include <CU/NameSpaceAliases.h>
#include <CU/GrowingArray/GrowingArray.h>
#include "PostMaster/MessageReceiver.h"


class MessageReciever;

struct Reciever
{
	Reciever()
	{
		myReciever = nullptr;
		myOrder = RecieverOrder::eDefault;
	}
	Reciever(MessageReciever & aReciever, RecieverOrder aPriority = RecieverOrder::eDefault)
	{
		myReciever = &aReciever;
		myOrder = aPriority;
	}

	bool operator == (const Reciever & aRight) const
	{
		return myReciever == aRight.myReciever;
	}

	MessageReciever * myReciever;
	RecieverOrder myOrder;
};

class SingletonPostMaster
{
public:
	static void Create();
	static void Destroy();

	static void AddReciever(const RecieverTypes aTypeToRecieve, MessageReciever & aRecieverToAdd, const RecieverOrder aPriority = RecieverOrder::eDefault);
	static void RemoveReciever(const RecieverTypes aTypeUnsubscribe, MessageReciever & aRecieverToRemove);

	static void RemoveReciever(MessageReciever &aReceiver);
	
	static bool CheckIfExists();
	
	template <typename MessageType>
	static inline void SendPostMessage(const MessageType & aMessageToSend);
private:
	SingletonPostMaster();
	~SingletonPostMaster();

	template <typename MessageType>
	void InternalPostMessage(const MessageType & aMessageToSend);

	static SingletonPostMaster * ourInstance;

	static inline SingletonPostMaster & GetInstance();

	CU::GrowingArray<CU::GrowingArray<Reciever>> myRecievers;
};

template <typename MessageType>
void SingletonPostMaster::SendPostMessage(const MessageType & aMessageToSend)
{
	GetInstance().InternalPostMessage(aMessageToSend);
}

template <typename MessageType>
void SingletonPostMaster::InternalPostMessage(const MessageType & aMessageToSend)
{
	for (unsigned short iReciever = 0; iReciever < myRecievers[static_cast<unsigned short>(aMessageToSend.myType)].Size(); ++iReciever)
	{
		DL_ASSERT(myRecievers[static_cast<unsigned short>(aMessageToSend.myType)].Size() > 0, "ERROR: No reciever to recieve message");
		MessageReciever* explainginReciever = myRecievers[static_cast<unsigned short>(aMessageToSend.myType)][iReciever].myReciever;
		
		if (explainginReciever->RecieveMessage(aMessageToSend) == false)
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

#define SendAPostMessage(message) SingletonPostMaster::SendPostMessage((message));
