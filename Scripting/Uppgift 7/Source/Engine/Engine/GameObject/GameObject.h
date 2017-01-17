#pragma once

namespace SB
{
	class Scene;
	class BaseComponent;

	class GameObject : public JsonObject
	{
	public:
		GameObject(Scene & aScene, const std::string & aIdentifier, std::atomic<int> & aReferenceCounter);

		GameObject(const GameObject &aOtherGameObject);
		~GameObject();

		void Initialize();
		bool IsInitialized() const;

		void AddPosition(const Vector3f& aPositionOffset);
		void SetPosition(const Vector3f & aPosition);
		void SetRotation(const Quaternion & aRotation);
		void RotateAlongAxis(const Vector3f & anAxis, const float aRotation);
		void SetScale(const Vector3f & aScale);

		template<typename TComponentType>
		unsigned short GetComponentIndex(const TComponentType & aComponent);

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

		inline Quaternion GameObject::GetWorldRotation() const
		{
			if (myParent != nullptr)
			{
				return myParent->GetWorldRotation() * myRotation;
			}
			return myRotation;
		}

		inline Vector3f GetWorldPosition() const
		{
			return GetTransformation().GetPosition();
		}

		inline Matrix44f GetParentTransformation() const 
		{
			if (myParent == nullptr)
			{
				return Matrix44f::Identity;
			}
			return myParent->GetTransformation();
		}

		inline Quaternion GetParentLocalRotation() const
		{
			if (myParent == nullptr)
			{
				return Quaternion();
			}
			return myParent->GetRotation();
		}

		inline Quaternion GetParentWorldRotation() const
		{
			if (myParent == nullptr)
			{
				return Quaternion();
			}
			return myParent->GetWorldRotation();
		}

		inline Matrix44f GetTransformationWithoutLocalRotation() const 
		{
			Matrix44f ourTransformation = Matrix44f::CreateTranslation(myPosition);

			if (myParent == nullptr)
			{
				return ourTransformation;
			}
			return ourTransformation * myParent->GetTransformation();
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
		const ComponentPtr<const TComponentType> GetComponent(const unsigned short & anIndex = 0) const;

		template <typename TComponentType>
		bool TryGetComponent(ComponentPtr<TComponentType> & aComponentPtr, const unsigned short & anIndex = 0);

		template <typename TComponentType>
		bool TryGetComponent(ComponentPtr<TComponentType> & aComponentPtr, const unsigned short & anIndex = 0) const;

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

		const GrowingArray<ObjectPtr> GetChildren() const;


		template <typename TEvent>
		void TriggerEvent(const TEvent & aEvent) const;

		void AddEventSubscriber(const size_t aIndex, const unsigned short & aSubscriber);

		void SetIndexInFactory(unsigned short aIndex);
		unsigned short GetIndexInFactory() const;

		ObjectPtr AsPointer();
		const ObjectPtr AsPointer() const;
		unsigned short GetReferenceCount() const;

		std::atomic<int> * GetReferenceCounter();
		const Vector3f AdjustOffset(const Vector3f & myOffset);

		virtual void ToJson(JsonSerializer &aSerializer)const override;

		template <typename TCallback>
		void WithEachChild(const TCallback & aCallback, const bool aRecursive = true, const bool aIncludeThis = false);

		void Play3DSound(const char* aSoundEventName);
		void Play3DSound(const std::string& aSoundEventName);

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

		GrowingArray<ObjectPtr> myChildren;
	};

	template<typename TComponentType>
	unsigned short GameObject::GetComponentIndex(const TComponentType & aComponent)
	{
		const unsigned short TypeID = UniqeIdentifier<BaseComponent>::GetID<TComponentType>();

		if (TypeID < myComponents.Size())
		{
			const BaseComponent * tempComponent = &aComponent;
			unsigned short tempIndex = myComponents[TypeID].Find(tempComponent);

			//TODO:: Warn if index dont exist
			return tempIndex;
		}
		Error("trying to get index of componeny type that gameobject does not have");
	}

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
	bool GameObject::TryGetComponent(ComponentPtr<TComponentType>& aComponentPtr, const unsigned short& anIndex)
	{
		aComponentPtr = GetComponent<TComponentType>(anIndex);
		return aComponentPtr != nullptr;
	}

	template <typename TComponentType>
	bool GameObject::TryGetComponent(ComponentPtr<TComponentType>& aComponentPtr, const unsigned short& anIndex) const
	{
		aComponentPtr = GetComponent<TComponentType>(anIndex);
		return aComponentPtr != nullptr;
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
		if (IsRemoved())
		{
			return;
		}

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

	template <typename TCallback>
	void GameObject::WithEachChild(const TCallback& aCallback, const bool aRecursive/* = true*/, const bool aIncludeThis/* = false*/)
	{
		if (aIncludeThis)
		{
			aCallback(*this);
		}

		for (unsigned short i=0; i<myChildren.Size(); i++)
		{
			aCallback(*&*myChildren[i]);
		}

		if (aRecursive)
		{
			for (unsigned short i = 0; i<myChildren.Size(); i++)
			{
				myChildren[i]->WithEachChild(aCallback, aRecursive, false);
			}
		}
	}
}
