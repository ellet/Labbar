#include "stdafx.h"
#include "PostMaster.h"


void PostMaster::AddReceiver(const ReceiverTypes aTypeToRecieve, MessageReceiver & aReceiverToAdd, const ReceiverOrder aPriority /*= ReceiverOrder::eDefault*/)
{
	Receiver tempReciver(aReceiverToAdd, aPriority);
	if (aReceiverToAdd.myReceiverOrder != ReceiverOrder::eDefault)
	{
		tempReciver = Receiver(aReceiverToAdd, aReceiverToAdd.myReceiverOrder);
	}

	if (myReceivers[USHORTCAST(aTypeToRecieve)].Find(tempReciver) != myReceivers.FoundNone)
	{
		return;
	}

	for (unsigned short iReceiver = 0; iReceiver < myReceivers[USHORTCAST(aTypeToRecieve)].Size(); ++iReceiver)
	{
		if (tempReciver.myOrder < myReceivers[USHORTCAST(aTypeToRecieve)][iReceiver].myOrder)
		{
			myReceivers[USHORTCAST(aTypeToRecieve)].Insert(iReceiver, tempReciver);
			return;
		}
	}

	myReceivers[USHORTCAST(aTypeToRecieve)].Add(tempReciver);
}

void PostMaster::RemoveReceiver(const ReceiverTypes aTypeUnsubscribe, MessageReceiver & aReceiverToRemove)
{
	Receiver tempReceiver(aReceiverToRemove);

	for (unsigned short iReceiver = 0; iReceiver < myReceivers[USHORTCAST(aTypeUnsubscribe)].Size(); ++iReceiver)
	{
		if (tempReceiver == myReceivers[USHORTCAST(aTypeUnsubscribe)][iReceiver])
		{
			myReceivers[USHORTCAST(aTypeUnsubscribe)].RemoveAtIndex(iReceiver);
		}
	}
}

void PostMaster::RemoveReceiver(MessageReceiver& aReceiver)
{
	for (int i = 0; i < static_cast<int>(ReceiverTypes::enumlength); ++i)
	{
		RemoveReceiver(static_cast<ReceiverTypes>(i), aReceiver);
	}
}


PostMaster::PostMaster()
{
	myReceivers.Init(static_cast<unsigned short>(ReceiverTypes::enumlength));
	for (unsigned short iReceiverTypes = 0; iReceiverTypes < static_cast<unsigned short>(ReceiverTypes::enumlength); ++iReceiverTypes)
	{
		myReceivers.Add(CU::GrowingArray<Receiver>());
		myReceivers.GetLast().Init(5);
	}
}

PostMaster::~PostMaster()
{
}