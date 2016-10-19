#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"
#include "..\Scene\Scene.h"

namespace ENGINE_NAMESPACE
{
	GameObject::GameObject(Scene & aScene, const std::string & aIdentifier, std::atomic<int> & aReferenceCounter, const unsigned short aIndexInFactory)
	{
		myReferenceCounter = &aReferenceCounter;
		myScene = &aScene;
		myIsRemoved = false;
		myIsInitialized = false;
		myIdentifier = aIdentifier;
		myIndexInFactory = aIndexInFactory;

		myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
		myComponentRegistrationInfos.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
		myEventSubscribers.Resize(static_cast<unsigned short>(UniqeIdentifier<GenericEventSubsriber>::nextTypeIndex));

		myScale = Vector3f::One;
	}

	GameObject::~GameObject()
	{
		if (myIsInitialized == false)
		{
			Error("Object was never initialized and therefore destroyed! Did you forget to call Initialize?");
		}

		for (unsigned short iComponentTypes = 0; iComponentTypes < myComponents.Size(); ++iComponentTypes)
		{
			BaseComponentFactory * factory = myComponentRegistrationInfos[iComponentTypes].factory;

			for (unsigned short iComponent = 0; iComponent < myComponents[iComponentTypes].Size(); ++iComponent)
			{
				factory->ReturnMemory(myComponentRegistrationInfos[iComponentTypes].indexInFactory[iComponent]);
			}

			myComponentRegistrationInfos[iComponentTypes].factory = nullptr;
			myComponentRegistrationInfos[iComponentTypes].indexInFactory.RemoveAll();
			myComponents[iComponentTypes].RemoveAll();
		}
		myComponents.RemoveAll();

		delete myReferenceCounter;
		myReferenceCounter = nullptr;
	}

	void GameObject::Initialize()
	{
		if (myIsInitialized)
		{
			Error("Tried to initialize object twice!");
		}

		for (unsigned short iComponentTypes = 0; iComponentTypes < myComponents.Size(); ++iComponentTypes)
		{
			for (unsigned short iComponent = 0; iComponent < myComponents[iComponentTypes].Size(); ++iComponent)
			{
				BaseComponent * tempBaseComponent = myComponents[iComponentTypes][iComponent];
				tempBaseComponent->Initialize();
			}
		}

		myReferenceCounter->fetch_add(1);
		myIsInitialized = true;

 		myScene->NotifyObjectInitialization(ObjectPtr(this, myReferenceCounter));
	}

	bool GameObject::IsInitialized() const
	{
		return myIsInitialized;
	}

	void GameObject::AddPosition(const Vector3f& aPositionOffset)
	{
		myPosition += aPositionOffset;
	}

	void GameObject::SetPosition(const Vector3f & aPosition)
	{
		myPosition = aPosition;
	}

	void GameObject::SetRotation(const Quaternion & aRotation)
	{
		myRotation = aRotation;
		myRotation.Normalize();
	}

	void GameObject::RotateAlongAxis(const Vector3f & anAxis, const float aRotation)
	{
		myRotation.RotateAlongAxis(anAxis, aRotation);
	}

	void GameObject::SetScale(const Vector3f & aScale)
	{
		myScale = aScale;
	}

	Matrix44f GameObject::GetTransformation() const
	{
		Matrix44f aRotation = myRotation.GenerateMatrix();
		Matrix44f ourTransformation = Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * aRotation * Matrix44f::CreateTranslation(myPosition);

		if (myParent == nullptr)
		{
			return ourTransformation;
		}
		return ourTransformation * myParent->GetTransformation();
	}

	void GameObject::Remove()
	{
		if (myIsRemoved == false)
		{
			for (unsigned short i=0; i<myChildren.Size(); i++)
			{
				myChildren[i]->Remove();
			}

			if (myParent != nullptr)
			{
				myParent->myChildren.RemoveAtIndex(myParent->myChildren.Find(this));
				myParent = ObjectPtr();
			}

			myScene->IncrementRemovalCounter();
			myIsRemoved = true;
		}
	}
	
	void GameObject::SetParent(const ObjectPtr & aParent)
	{
		if (myParent != nullptr)
		{
			myParent->myChildren.RemoveAtIndex(myParent->myChildren.Find(this));
		}

		myParent = aParent;

		if (myParent != nullptr)
		{
			myParent->myChildren.Add(this);
		}
	}

	const GrowingArray<GameObject*> GameObject::GetChildren() const
	{
		return myChildren;
	}

	void GameObject::AddEventSubscriber(const size_t aIndex, const unsigned short & aSubscriber)
	{
		if (myEventSubscribers.Size() <= static_cast<unsigned short>(aIndex))
		{
			myEventSubscribers.Resize(static_cast<unsigned short>(aIndex+1));
		}

		myEventSubscribers[static_cast<unsigned short>(aIndex)].Add(aSubscriber);
	}

	unsigned short GameObject::GetIndexInFactory() const
	{
		return myIndexInFactory;
	}

	ObjectPtr GameObject::AsPointer()
	{
		myReferenceCounter->fetch_add(1);
		return ObjectPtr(this, myReferenceCounter);
	}

	unsigned short GameObject::GetReferenceCount() const
	{
		return static_cast<unsigned short>(myReferenceCounter->load());
	}

	std::atomic<int> * GameObject::GetReferenceCounter()
	{
		return myReferenceCounter;
	}

	ENGINE_NAMESPACE::Quaternion GameObject::GetWorldRotation() const
	{
		if (myParent != nullptr)
		{
			return myParent->GetRotation() * myRotation;
		}
		return myRotation;
	}

}
