#pragma once
#include <cstdint>

namespace SB
{
	class MessageQueue;

	enum class StopMessage
	{
		eYes,
		eNo
	};

	class GenericMessageReceiver
	{
	public:
		GenericMessageReceiver();
		virtual void Initialize(MessageQueue & aMessageQueue) = 0;
		virtual ~GenericMessageReceiver();
		virtual uint16_t GetMessageIdentifier() const = 0;

	private:
		friend class MessageQueue;
		template <typename TMessageType>
		friend class MessageReceiver;

		virtual StopMessage Receive(const void * aMessageData) = 0;
		MessageQueue * myMessageQueue;
	};

	template <typename TMessageType>
	class MessageReceiver : public GenericMessageReceiver
	{
	public:
		~MessageReceiver();

		void Initialize(MessageQueue& aMessageQueue) override;

		virtual StopMessage Receive(const TMessageType & aMessage) = 0;
	
		uint16_t GetMessageIdentifier() const final override;

	private:
		StopMessage Receive(const void* aMessageData) final override;
	};

	template <typename TMessageType>
	void MessageReceiver<TMessageType>::Initialize(MessageQueue& aMessageQueue)
	{
		myMessageQueue = &aMessageQueue;
		aMessageQueue.AddReceiver(*this);
	}

	template <typename TMessageType>
	MessageReceiver<TMessageType>::~MessageReceiver()
	{
		if (myMessageQueue != nullptr)
		{
			myMessageQueue->RemoveReceiver(*this, GetMessageIdentifier());
			myMessageQueue = nullptr;
		}
		else
		{
			std::cout << "No Message Queue was attached to this MessageReceiver!" << std::endl;
			abort();
		}
	}

	template <typename TMessageType>
	uint16_t MessageReceiver<TMessageType>::GetMessageIdentifier() const
	{
		return UniqueIdentifier<MessageQueue>::GetID<TMessageType>();
	}

	template <typename TMessageType>
	StopMessage MessageReceiver<TMessageType>::Receive(const void* aMessageData)
	{
		return Receive(*reinterpret_cast<const TMessageType*>(aMessageData));
	}
}
