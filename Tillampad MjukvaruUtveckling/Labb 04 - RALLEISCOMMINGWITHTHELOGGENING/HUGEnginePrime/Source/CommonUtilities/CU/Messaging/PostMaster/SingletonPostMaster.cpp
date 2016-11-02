#include "stdafx.h"
#include "SingletonPostMaster.h"



//SingletonPostMaster * SingletonPostMaster::ourInstance = nullptr;
//
//
//void SingletonPostMaster::Create()
//{
//	if (ourInstance == nullptr)
//	{
//		ourInstance = new SingletonPostMaster();
//	}
//}
//
//void SingletonPostMaster::Destroy()
//{
//	if (ourInstance != nullptr)
//	{
//		delete ourInstance;
//		ourInstance = nullptr;
//	}
//}
//
//void SingletonPostMaster::AddReceiver(const ReceiverTypes aTypeToRecieve, MessageReceiver & aReceiverToAdd, const ReceiverOrder aPriority /*= ReceiverOrder::eDefault*/)
//{
//	Receiver tempReciver(aReceiverToAdd, aPriority);
//	if (aReceiverToAdd.myReceiverOrder != ReceiverOrder::eDefault)
//	{
//		tempReciver = Receiver(aReceiverToAdd, aReceiverToAdd.myReceiverOrder);
//	}
//	
//	if (GetInstance().myReceivers[USHORTCAST(aTypeToRecieve)].Find(tempReciver) != GetInstance().myReceivers.FoundNone)
//	{
//		return;
//	}
//
//	for (unsigned short iReceiver = 0; iReceiver < GetInstance().myReceivers[USHORTCAST(aTypeToRecieve)].Size(); ++iReceiver)
//	{
//		if (tempReciver.myOrder < GetInstance().myReceivers[USHORTCAST(aTypeToRecieve)][iReceiver].myOrder)
//		{
//			GetInstance().myReceivers[USHORTCAST(aTypeToRecieve)].Insert(iReceiver, tempReciver);
//			return;
//		}
//	}
//
//	GetInstance().myReceivers[USHORTCAST(aTypeToRecieve)].Add(tempReciver);
//}
//
//void SingletonPostMaster::RemoveReceiver(const ReceiverTypes aTypeUnsubscribe, MessageReceiver & aReceiverToRemove)
//{
//	Receiver tempReceiver(aReceiverToRemove);
//
//	for (unsigned short iReceiver = 0; iReceiver < GetInstance().myReceivers[USHORTCAST(aTypeUnsubscribe)].Size(); ++iReceiver)
//	{
//		if (tempReceiver == GetInstance().myReceivers[USHORTCAST(aTypeUnsubscribe)][iReceiver])
//		{
//			GetInstance().myReceivers[USHORTCAST(aTypeUnsubscribe)].RemoveAtIndex(iReceiver);
//			//break;
//		}
//	}
//}
//
//void SingletonPostMaster::RemoveReceiver(MessageReceiver& aReceiver)
//{
//	if (ourInstance == nullptr)
//	{
//		return;
//	}
//
//	for (int i = 0; i < static_cast<int>(ReceiverTypes::enumlength); ++i)
//	{
//		RemoveReceiver(static_cast<ReceiverTypes>(i), aReceiver);
//	}
//}
//
//bool SingletonPostMaster::CheckIfExists()
//{
//	return (ourInstance != nullptr);
//}
//
//
//SingletonPostMaster::SingletonPostMaster()
//{
//	myReceivers.Init(static_cast<unsigned short>(ReceiverTypes::enumlength));
//	for (unsigned short iReceiverTypes = 0; iReceiverTypes < static_cast<unsigned short>(ReceiverTypes::enumlength); ++iReceiverTypes)
//	{
//		myReceivers.Add(CU::GrowingArray<Receiver>());
//		myReceivers.GetLast().Init(5);
//	}
//}
//
//SingletonPostMaster::~SingletonPostMaster()
//{
//}