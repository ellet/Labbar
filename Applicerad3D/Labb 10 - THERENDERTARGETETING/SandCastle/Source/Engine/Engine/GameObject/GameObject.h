#pragma once

namespace ENGINE_NAMESPACE
{
	class Scene;
	class BaseComponent;

	class GameObject
	{
	public:
		GameObject(Scene & aScene, const std::string & aIdentifier, std::atomic<int> & aReferenceCounter, const unsigned short aIndexInFactory);
		~GameObject();

		void Initialize();
		bool IsInitialized() const;

		void AddPosition(const Vector3f& aPositionOffset);
		void SetPosition(const Vector3f & aPosition);
		void SetRotation(const Quaternion & aRotation);
		void RotateAlongAxis(const Vector3f & anAxis, const float aRotation);
		void SetScale(const Vector3f & aScale);

		inline const Vector3f& GetPosition() const
		{
			return myPosition;
		}
		inline Quaternion& GetRotation()
		{
			return myRotation;
		}
		inline const Quaternion& GetRotation() const
		{
			return myRotation;
		}
		inline const Vector3f&  GetScale() const
		{
			return myScale;
		}

		Matrix44f GetTransformation() const;

		Scene & GetScene();
		const Scene & GetScene() const;

		template <typename TStateType>
		TStateType & GetState();

		template <typename TStateType>
		const TStateType & GetState() const;

		template <typename TComponentType>
		ComponentPtr<TComponentType> CreateComponent();

		template <typename TComponentType>
		ComponentPtr<TComponentType> GetComponent(const unsigned short & anIndex = 0);

		template <typename TComponentType>
		const ComponentPtr<const TComponentType> GetComponent(const unsigned short & anIndex = 0)const;

		template <typename TComponentType>
		unsigned short GetComponentCount() const;

		void Remove();
		bool IsRemoved() const;

		inline const std::string& GetIdentifier() const
		{
			return myIdentifier;
		}
		inline void SetIdentifier(const std::string& aValue)
		{
			myIdentifier = aValue;
		}

		void SetParent(const ObjectPtr & aParent);
		const ObjectPtr & GetParent() const;

		const GrowingArray<GameObject*> GetChildren() const;


		template <typename TEvent>
		void TriggerEvent(const TEvent & aEvent) const;

		void AddEventSubscriber(const size_t aIndex, const unsigned short & aSubscriber);

		unsigned short GetIndexInFactory() const;
		ObjectPtr AsPointer();
		unsigned short GetReferenceCount() const;

		std::atomic<int> * GetReferenceCounter();

	private:
		struct ComponentRegistrationInfo
		{
			BaseComponentFactory * factory;
			GrowingArray<unsigned short> indexInFactory;
		};

		GrowingArray<GrowingArray<BaseComponent*>> myComponents;
		GrowingArray<ComponentRegistrationInfo> myComponentRegistrationInfos;
		std::string myIdentifier;
		Vector3f myPosition;
		Vector3f myScale;
		Quaternion myRotation;
		Scene * myScene;
		bool myIsRemoved;
		bool myIsInitialized;
		ObjectPtr myParent;

		GrowingArray<GrowingArray<unsigned short>>  myEventSubscribers;
		std::atomic<int>* myReferenceCounter;
		
		unsigned short myIndexInFactory;

		GrowingArray<GameObject*> myChildren;
public:
	Quaternion GetWorldRotation() const;
	};

	inline Scene & GameObject::GetScene()
	{
		return *myScene;
	}

	inline const Scene & GameObject::GetScene() const
	{
		return *myScene;
	}

	template <typename TStateType>
	TStateType & GameObject::GetState()
	{

	}

	template <typename TStateType>
	const TStateType & GameObject::GetState() const
	{

	}

	template <typename TComponentType>
	ComponentPtr<TComponentType> GameObject::CreateComponent()
	{
		if (myIsInitialized)
		{
			Error("Can only add components to uninitialized objects!");
		}

		unsigned short id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
		unsigned short nextID = UniqeIdentifier<BaseComponent>::nextTypeIndex;
		if (myComponents.Size() < nextID)
		{
			myComponents.Resize(nextID);
			myComponentRegistrationInfos.Resize(nextID);
		}

		unsigned short newIndex;
		std::shared_ptr<ComponentFactory<TComponentType>> factory = myScene->GetComponentFactory<TComponentType>();
		TComponentType & newComponent = factory->CreateComponent(&newIndex);
		myComponents[id].Add(&newComponent);
		myComponents[id].GetLast()->SetGameObject(*this);
		
		myComponentRegistrationInfos[id].factory = &*factory;
		myComponentRegistrationInfos[id].indexInFactory.Add(newIndex);

		myReferenceCounter->fetch_add(1);
		return ComponentPtr<TComponentType>(&newComponent, myReferenceCounter);
	}

	template <typename TComponentType>
	ComponentPtr<TComponentType>
		GameObject::GetComponent(const unsigned short & anIndex/* = 0*/)
	{
		unsigned short id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
		if (myComponents.Size() <= id || myComponents[id].Size() <= anIndex)
		{
			return ComponentPtr<TComponentType>();
		}
		myReferenceCounter->fetch_add(1);
		return ComponentPtr<TComponentType>(static_cast<TComponentType*>(myComponents[id][anIndex]), myReferenceCounter);
	}

	template <typename TComponentType>
	const ComponentPtr<const TComponentType>
		GameObject::GetComponent(const unsigned short & anIndex/* = 0*/) const
	{
		unsigned short id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();
		if (myComponents.Size() <= id || myComponents[id].Size() <= anIndex)
		{
			return ComponentPtr<const TComponentType>();
		}
		myReferenceCounter->fetch_add(1);
		return ComponentPtr<const TComponentType>(static_cast<TComponentType*>(myComponents[id][anIndex]), myReferenceCounter);
	}

	template <typename TComponentType>
	unsigned short GameObject::GetComponentCount() const
	{
		unsigned short id = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();

		if (id < myComponents.Size())
		{
			return myComponents[id].Size();
		}
		else
		{
			return 0;
		}
	}

	inline bool GameObject::IsRemoved() const
	{
		return myIsRemoved;
	}

	inline const ObjectPtr & GameObject::GetParent() const
	{
		return myParent;
	}

	template <typename TEvent>
	void GameObject::TriggerEvent(const TEvent & aEvent) const
	{
		const size_t EventID = UniqeIdentifier<GenericSubscriber>::GetID<TEvent>();

		if (EventID < myEventSubscribers.Size())
		{
			for (unsigned short iSubscriber = 0; iSubscriber < myEventSubscribers[static_cast<unsigned short>(EventID)].Size(); ++iSubscriber)
			{
				const unsigned short tempSubscriberIndex = myEventSubscribers[static_cast<unsigned short>(EventID)][iSubscriber];
				EventSubscriber<TEvent>::TriggerEvent(tempSubscriberIndex, aEvent);
			}
		}
	}

}