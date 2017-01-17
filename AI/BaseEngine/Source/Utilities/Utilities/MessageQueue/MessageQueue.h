#pragma once
#include "MessageData.h"

namespace SB
{
	class GenericMessageReceiver;

	// A thread safe Message Queue where posting messages and registering new receivers are lock-free.
	class MessageQueue
	{
	public:
		MessageQueue();

		template <typename TMessageType>
		void QueueMessage(const TMessageType & aMessage);
	
		void DispatchMessages();

		void AddReceiver(GenericMessageReceiver & aReceiver);
		void RemoveReceiver(GenericMessageReceiver & aReceiver, const uint16_t aIdentifier);

	private:
		void MakeReceiverChanges();

		std::vector<std::vector<GenericMessageReceiver*>> myMessageReceivers;
		ConcurrentQueue<GenericMessageReceiver*> myNewReceivers;
		ConcurrentQueue<MessageData> myScheduledMessages;

		std::mutex myReceiverMutex;
	};

	template <typename TType>
	void TypeCopyConstructor(void * aNewMemory, const void * aOldMemory)
	{
		new (reinterpret_cast<TType*>(aNewMemory)) TType(*reinterpret_cast<const TType*>(aOldMemory));
	}

	template <typename TType>
	void TypeDestructer(void * aMemory)
	{
		reinterpret_cast<TType*>(aMemory)->~TType();
	}

	template <typename TMessageType>
	void MessageQueue::QueueMessage(const TMessageType& aMessage)
	{
		static_assert(sizeof(TMessageType) <= sizeof(MessageData::data), "This message exceeds the size of MessageData::data, decrease message size or increase the size of MessageData::data!");
	
		MessageData data;
		new (reinterpret_cast<TMessageType*>(data.data)) TMessageType(aMessage);
		//TypeCopyConstructor<TMessageType>(data.data + data.paddingAmount, &aMessage);
		data.copyConstructor = &TypeCopyConstructor<TMessageType>;
		data.destructer = &TypeDestructer<TMessageType>;
		data.identifier = UniqueIdentifier<MessageQueue>::GetID<TMessageType>();
		myScheduledMessages.enqueue(data);
	}
}
