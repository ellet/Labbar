#include "stdafx.h"
#include "MessageQueue.h"
#include "MessageReceiver.h"

namespace SB
{
	MessageQueue::MessageQueue()
	{
	}

	void MessageQueue::DispatchMessages()
	{
		std::lock_guard<std::mutex> lock(myReceiverMutex);

		MakeReceiverChanges();

		const size_t bulkSize = 10;
		MessageData messages[bulkSize];
		size_t count;

		do
		{
			count = myScheduledMessages.try_dequeue_bulk(messages, bulkSize);

			for (size_t iMessage = 0; iMessage<count; ++iMessage)
			{
				MessageData & message = messages[iMessage];

				if (message.identifier < myMessageReceivers.size())
				{
					std::vector<GenericMessageReceiver*> & receiverList = myMessageReceivers[message.identifier];

					for (size_t aReceiver=0; aReceiver<receiverList.size(); aReceiver++)
					{
						if (receiverList[aReceiver]->Receive(message.data) == StopMessage::eYes)
						{
							break;
						}
					}
				}
			}

		} while (count > 0);
	}

	void MessageQueue::AddReceiver(GenericMessageReceiver& aReceiver)
	{
		myNewReceivers.enqueue(&aReceiver);
	}

	void MessageQueue::RemoveReceiver(GenericMessageReceiver& aReceiver, const uint16_t aIdentifier)
	{
		std::lock_guard<std::mutex> lock(myReceiverMutex);

		// Register all new receivers, we may not be in the existing receiver list yet.
		MakeReceiverChanges();

		if (aIdentifier >= myMessageReceivers.size() || myMessageReceivers[aIdentifier].size() == 0)
		{
			std::cout << "Could not find receiver to remove (no receivers in list)" << std::endl;
			abort();
		}

		std::vector<GenericMessageReceiver*> & receiverList = myMessageReceivers[aIdentifier];
	
		auto && it = std::lower_bound(receiverList.begin(), receiverList.end(), &aReceiver);
		if (it == receiverList.end())
		{
			std::cout << "Could not find receiver to remove (no matching receiver)" << std::endl;
			abort();
		}

		receiverList.erase(it);
	}

	void MessageQueue::MakeReceiverChanges()
	{
		const size_t bulkSize = 10;
		GenericMessageReceiver * receivers[bulkSize];
		size_t count;

		do
		{
			count = myNewReceivers.try_dequeue_bulk(receivers, bulkSize);

			for (size_t i=0; i<count; ++i)
			{
				GenericMessageReceiver & receiver = *receivers[i];
				uint16_t identifier = receiver.GetMessageIdentifier();

				if (identifier >= myMessageReceivers.size())
				{
					myMessageReceivers.resize(max(1, identifier * 2));
				}

				std::vector<GenericMessageReceiver*> & receiverList = myMessageReceivers[identifier];

				// Insert ordered by memory address
				receiverList.insert(std::lower_bound(receiverList.begin(), receiverList.end(), &receiver), &receiver);
			}

		} while (count > 0);
	}
}
