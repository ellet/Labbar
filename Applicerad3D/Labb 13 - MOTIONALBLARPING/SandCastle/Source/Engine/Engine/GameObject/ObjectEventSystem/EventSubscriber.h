#pragma once
#include "Engine/Component/BaseComponent.h"


namespace ENGINE_NAMESPACE
{	
	class GenericSubscriber;

	template<typename TEvent>
	class EventSubscriber
	{
	public:
		EventSubscriber()
		{
			myIndex = 0;
			AddSubscriber();
		}
		virtual ~EventSubscriber()
		{
			RemoveSubscriber();
		}

		size_t GetTypeIndex()
		{
			return UniqeIdentifier<GenericSubscriber>::GetID<TEvent>();
		}

		unsigned short GetInstanceIndex()
		{
			return myIndex;
		}

		virtual void RecieveEvent(const TEvent & aEvent) = 0;

		static void TriggerEvent(const unsigned short aIndex, const TEvent & aEvent)
		{
			ourSubscribers[static_cast<unsigned short>(aIndex)]->RecieveEvent(aEvent);
		}

	private:
		void AddSubscriber()
		{
			if (ourFreeIndexes.Size() <= 0)
			{
				unsigned short tempGrowSize = ourSubscribers.Size();
				unsigned short tempEndPoint = tempGrowSize;

				if (tempGrowSize < 1)
				{
					tempGrowSize = 2;
				}

				ourSubscribers.Resize(tempGrowSize * 2);

				for (unsigned short iFreeIndex = ourSubscribers.Size() -1; iFreeIndex >= tempEndPoint; --iFreeIndex)
				{
					ourFreeIndexes.Push(iFreeIndex);
					
					if (iFreeIndex == 0)
					{
						break;
					}
				}
			}

			myIndex = ourFreeIndexes.Pop();
			ourSubscribers[myIndex] = this;
		}

		void RemoveSubscriber()
		{
			ourFreeIndexes.Push(myIndex);
		}

		static Stack<unsigned short> ourFreeIndexes;
		static GrowingArray<EventSubscriber<TEvent> *> ourSubscribers;
		unsigned short myIndex;
	};

	template<typename TEvent>
	GrowingArray<EventSubscriber<TEvent> *> EventSubscriber<TEvent>::ourSubscribers;

	template<typename TEvent>
	Stack<unsigned short> EventSubscriber<TEvent>::ourFreeIndexes;

	//template <typename TEvent>
	//void ENGINE_NAMESPACE::EventSubscriber::RecieveEvent(const TEvent & aEvent)
	//{
	//	//ASSERT SHOULD NOT BE HERE
	//}


}