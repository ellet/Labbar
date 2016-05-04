#include "SingletonPostMaster.h"
#include "MessageReciever.h"
#include "Message.h"


SingletonPostMaster * SingletonPostMaster::ourInstance = nullptr;


void SingletonPostMaster::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SingletonPostMaster();
	}
}

void SingletonPostMaster::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}

void SingletonPostMaster::AddReciever(const RecieverTypes aTypeToRecieve, MessageReciever & aRecieverToAdd)
{
	for (int i = 0; i < GetInstance().myRecievers[static_cast<unsigned short>(aTypeToRecieve)].Size(); ++i)
	{
		if (GetInstance().myRecievers[static_cast<unsigned short>(aTypeToRecieve)][i] == &aRecieverToAdd)
		{
			return;
		}
	}

	GetInstance().myRecievers[static_cast<unsigned short>(aTypeToRecieve)].Add(&aRecieverToAdd);
}

void SingletonPostMaster::RemoveReciever(const RecieverTypes aTypeUnsubscribe, MessageReciever & aRecieverToRemove)
{
	GetInstance().myRecievers[static_cast<unsigned short>(aTypeUnsubscribe)].RemoveCyclic(&aRecieverToRemove);
}

void SingletonPostMaster::RemoveReciever(MessageReciever& aReceiver)
{
	if (ourInstance == nullptr)
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(RecieverTypes::enumlength); ++i)
	{
		RemoveReciever(static_cast<RecieverTypes>(i), aReceiver);
	}
}

bool SingletonPostMaster::CheckIfExists()
{
	return (ourInstance != nullptr);
}

void SingletonPostMaster::InternalPostMessage(const Message & aMessageToSend)
{
	for (unsigned short iReciever = 0; iReciever < myRecievers[static_cast<unsigned short>(aMessageToSend.myMessageType)].Size(); ++iReciever)
	{
		DL_ASSERT(myRecievers[static_cast<unsigned short>(aMessageToSend.myMessageType)].Size() > 0, "ERROR: No reciever to recieve message");
		MessageReciever* explainginReciever = myRecievers[static_cast<unsigned short>(aMessageToSend.myMessageType)][iReciever];
		explainginReciever->RecieveMessage(aMessageToSend);
	}
}




SingletonPostMaster::SingletonPostMaster()
{
	myRecievers.Init(static_cast<unsigned short>(RecieverTypes::enumlength));
	for (unsigned short iRecieverTypes = 0; iRecieverTypes < static_cast<unsigned short>(RecieverTypes::enumlength); ++iRecieverTypes)
	{
		myRecievers.Add(CU::GrowingArray<MessageReciever*>());
		myRecievers.GetLast().Init(5);
	}
}

SingletonPostMaster::~SingletonPostMaster()
{
}