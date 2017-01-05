#pragma once

namespace SB
{
	template<typename TMessageType>
	class Subscriber;

	enum class ReceiveResult
	{
		eContinue,
		eStop
	};

	template <typename TMessageType>
	struct SubscriptionContainer
	{
		Subscriber<TMessageType> * subscriber;
		int priority;
		bool isRemoved;
	};

	template <typename TMessageType>
	class MessageCollection
	{
	public:
		static void AddSubscriber(Subscriber<TMessageType> & aSubscriber, int aPriority);
		static void RemoveSubscriber(const Subscriber<TMessageType> & aSubscriber);

		static void Distribute(const TMessageType & aMessageType);

	private:
		static std::vector<SubscriptionContainer<TMessageType>> & GetCurrentCollection();
		static std::vector<SubscriptionContainer<TMessageType>> & GetGlobalCollection();

		static GrowingArray<std::vector<SubscriptionContainer<TMessageType>>*> ourSubscribers;
		static size_t ourEnumerationCounter;
	};

	template <typename TMessageType>
	GrowingArray<std::vector<SubscriptionContainer<TMessageType>>*> MessageCollection<TMessageType>::ourSubscribers;

	template <typename TMessageType>
	size_t MessageCollection<TMessageType>::ourEnumerationCounter = 0;

	template <typename TMessageType>
	void MessageCollection<TMessageType>::AddSubscriber(Subscriber<TMessageType> & aSubscriber, int aPriority)
	{
		std::vector<SubscriptionContainer<TMessageType>> & subscriptions = GetCurrentCollection();

		SubscriptionContainer<TMessageType> container;
		container.isRemoved = false;
		container.priority = aPriority;
		container.subscriber = &aSubscriber;

		// Insert subscriber before first element that has the same or greater priority than it resulting in it being called last
		auto it = std::lower_bound(subscriptions.begin(), subscriptions.end(), container, [](const SubscriptionContainer<TMessageType> & aLeft, const SubscriptionContainer<TMessageType> & aRight) -> bool
		{
			return aLeft.priority < aRight.priority;
		});

		subscriptions.insert(it, container);
	}

	template <typename TMessageType>
	void MessageCollection<TMessageType>::RemoveSubscriber(const Subscriber<TMessageType>& aSubscriber)
	{
		std::vector<SubscriptionContainer<TMessageType>> & subscriptions = GetCurrentCollection();

		// Find first element with the same priority as the one to remove
		SubscriptionContainer<TMessageType> referenceContainer;
		referenceContainer.priority = aSubscriber.GetPriority();

		auto it = std::lower_bound(subscriptions.begin(), subscriptions.end(), referenceContainer, [](const SubscriptionContainer<TMessageType> & aLeft, const SubscriptionContainer<TMessageType> & aRight) -> bool
		{
			return aLeft.priority < aRight.priority;
		});

		while (true)
		{
			if (it == subscriptions.end() || it->priority != aSubscriber.GetPriority())
			{
				Error("Tried to remove a subscriber that could not be found.");
			}

			if (it->subscriber == &aSubscriber)
			{
				// Mark us as removed for later removal
				it->isRemoved = true;
				break;
			}

			++it;
		}
	}

	template <typename TMessageType>
	void MessageCollection<TMessageType>::Distribute(const TMessageType& aMessageType)
	{
		ourEnumerationCounter++;

		if (&GetCurrentCollection() != &GetGlobalCollection())
		{
			std::vector<SubscriptionContainer<TMessageType>> & subscriptions = GetCurrentCollection();

			for (int i = static_cast<int>(subscriptions.size()) - 1; i >= 0; i--)
			{
				if (subscriptions[i].isRemoved == true)
				{
					// We can only safely remove components when we know we're the only function iterating
					if (ourEnumerationCounter == 1)
					{
						subscriptions.erase(subscriptions.begin() + i);
					}
					continue;
				}

				ReceiveResult result = subscriptions[i].subscriber->Receive(aMessageType);

				if (result == ReceiveResult::eStop)
				{
					break;
				}
			}
		}

		{
			std::vector<SubscriptionContainer<TMessageType>> & subscriptions = GetGlobalCollection();

			for (int i = static_cast<int>(subscriptions.size()) - 1; i >= 0; i--)
			{
				if (subscriptions[i].isRemoved == true)
				{
					// We can only safely remove components when we know we're the only function iterating
					if (ourEnumerationCounter == 1)
					{
						subscriptions.erase(subscriptions.begin() + i);
					}
					continue;
				}

				ReceiveResult result = subscriptions[i].subscriber->Receive(aMessageType);

				if (result == ReceiveResult::eStop)
				{
					break;
				}
			}
		}

		ourEnumerationCounter--;
	}

	template<typename TMessageType = void>
	class Subscriber
	{
	public:
		virtual ~Subscriber();

		int GetPriority() const;

		virtual ReceiveResult Receive(const TMessageType & aMessage) = 0;

	protected:
		Subscriber(int aPriority = 0);

	private:
		int myPriority;
		unsigned short mySubscribeTo;
	};
	
	template <typename TMessageType>
	Subscriber<TMessageType>::Subscriber(int aPriority)
	{
		myPriority = aPriority;
		mySubscribeTo = PostMaster::GetCurrentState().myStateIndex;
		MessageCollection<TMessageType>::AddSubscriber(*this, aPriority);
	}

	template <typename TMessageType>
	Subscriber<TMessageType>::~Subscriber()
	{
		if (PostMaster::GetCurrentState().myStateIndex != mySubscribeTo)
		{
			Error("Tried to remove the subscription from a different state than it was subscribed to!");
		}
		MessageCollection<TMessageType>::RemoveSubscriber(*this);
	}

	template <typename TMessageType>
	int Subscriber<TMessageType>::GetPriority() const
	{
		return myPriority;
	}

	class GenericSubscription
	{
	public:
		virtual ~GenericSubscription();
	};

	template <typename TMessageType>
	class Subscription : public Subscriber<TMessageType>
	{
	public:
		template<typename TReceiveFunction, typename = std::enable_if<std::is_same<ReceiveResult, std::result_of<TReceiveFunction>>::value>::type>
		Subscription(const TReceiveFunction & aReceiveFunction, int aPriority = 0)
			: Subscriber<TMessageType>(aPriority)
		{
			myReceiver = std::function<ReceiveResult(const TMessageType & aMessage)>(aReceiveFunction);
		}

		template<typename TReceiveFunction, typename = std::enable_if<!std::is_same<ReceiveResult, std::result_of<TReceiveFunction>>::value>::type>
		Subscription(const TReceiveFunction & aReceiveFunction, int aPriority = 0, ReceiveResult aReturnValue = ReceiveResult::eContinue)
			: Subscriber<TMessageType>(aPriority)
		{
			TReceiveFunction receiverCopy = aReceiveFunction;
			myReceiver = std::function<ReceiveResult(const TMessageType & aMessage)>([=](const TMessageType &aMessage) -> ReceiveResult
			{
				receiverCopy(aMessage);
				return aReturnValue;
			});
		}

		ReceiveResult Receive(const TMessageType & aMessage) override;

	private:
		std::function<ReceiveResult(const TMessageType & aMessage)> myReceiver;
	};

	template <typename TMessageType>
	ReceiveResult Subscription<TMessageType>::Receive(const TMessageType& aMessage)
	{
		if (myReceiver)
		{
			return myReceiver(aMessage);
		}
		return ReceiveResult::eContinue;
	}

	class PostMasterState
	{
	public:
		PostMasterState();
		~PostMasterState();

		void AddRemover(const std::function<void()> & aRemover);

	private:
		friend class PostMaster;
		template <typename TMessageType>
		friend class MessageCollection;
		template <typename TMessageType>
		friend class Subscriber;

		GrowingArray<std::function<void()>*> myRemovers;
		unsigned short myStateIndex;
	};
	
	class PostMasterStateBinding
	{
	public:
		PostMasterStateBinding()
		{
			myWasMoved = false;
		}
		PostMasterStateBinding(PostMasterStateBinding & aOther)
		{
			myWasMoved = false;
			aOther.myWasMoved = true;
		}
		PostMasterStateBinding(PostMasterStateBinding && aOther)
		{
			myWasMoved = false;
			aOther.myWasMoved = true;
		}
		~PostMasterStateBinding();

	private:
		bool myWasMoved;
	};
	
	class PostMaster
	{
	public:
		static void Initialize();
		static void Shutdown();

		template <typename TMessageType>
		static void Post(const TMessageType & aMessage);

		static PostMasterStateBinding Push(PostMasterState & aState);
		static void Pop();

		static PostMasterState & GetCurrentState();
		static void AssertState(const PostMasterState & aState);
		static PostMasterState& GetGlobalState();

		static bool IsInitialized();

	private:
		static Stack<PostMasterState*> ourStateStack;
		static std::atomic<unsigned short> ourNextStateIndex;
		static std::unique_ptr<PostMasterStateBinding> ourGlobalStateBinding;
		static PostMasterState * ourGlobalState;
		static bool ourIsInitialized;
	};
	
	template <typename TMessageType>
	std::vector<SubscriptionContainer<TMessageType>> & MessageCollection<TMessageType>::GetCurrentCollection()
	{
		PostMasterState & currentState = PostMaster::GetCurrentState();
		unsigned short currentIndex = currentState.myStateIndex;

		if (currentIndex + 1 >= ourSubscribers.Size())
		{
			ourSubscribers.Resize(currentIndex + 1, nullptr);
		}

		if (ourSubscribers[currentIndex] == nullptr)
		{
			ourSubscribers[currentIndex] = new std::vector<SubscriptionContainer<TMessageType>>();
			GrowingArray<std::vector<SubscriptionContainer<TMessageType>>*> * subscribers = &ourSubscribers;

			currentState.AddRemover(std::function<void()>([currentIndex, subscribers]() -> void
			{
				delete (*subscribers)[currentIndex];
				(*subscribers)[currentIndex] = nullptr;
			}));
		}

		return *ourSubscribers[currentIndex];
	}

	template <typename TMessageType>
	std::vector<SubscriptionContainer<TMessageType>> & MessageCollection<TMessageType>::GetGlobalCollection()
	{
		PostMasterState & currentState = PostMaster::GetGlobalState();
		unsigned short currentIndex = currentState.myStateIndex;

		if (currentIndex + 1 >= ourSubscribers.Size())
		{
			ourSubscribers.Resize(currentIndex + 1, nullptr);
		}

		if (ourSubscribers[currentIndex] == nullptr)
		{
			ourSubscribers[currentIndex] = new std::vector<SubscriptionContainer<TMessageType>>();
			GrowingArray<std::vector<SubscriptionContainer<TMessageType>>*> * subscribers = &ourSubscribers;

			currentState.AddRemover(std::function<void()>([currentIndex, subscribers]() -> void
			{
				delete (*subscribers)[currentIndex];
				(*subscribers)[currentIndex] = nullptr;
			}));
		}

		return *ourSubscribers[currentIndex];
	}

	template <typename TMessageType>
	void PostMaster::Post(const TMessageType& aMessage)
	{
		MessageCollection<TMessageType>::Distribute(aMessage);
	}

	inline PostMasterStateBinding::~PostMasterStateBinding()
	{
		if (myWasMoved == false)
		{
			PostMaster::Pop();
		}
	}
}
