#include "stdafx.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Scene\Scene.h"

namespace SB
{
	GameObject::GameObject(Scene & aScene, const std::string & aIdentifier, std::atomic<int> & aReferenceCounter)
	{
		myReferenceCounter = &aReferenceCounter;
		myScene = &aScene;
		myIsRemoved = false;
		myIsInitialized = false;
		myIdentifier = aIdentifier;
		myIndexInFactory = UINT16_MAX;

		myComponents.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
		myComponentRegistrationInfos.Resize(UniqeIdentifier<BaseComponent>::nextTypeIndex);
		myEventSubscribers.Resize(static_cast<unsigned short>(UniqeIdentifier<GenericEventSubsriber>::nextTypeIndex));

		myScale = Vector3f::One;
	}

	GameObject::GameObject(const GameObject &aOtherGameObject)
	{

	}

	GameObject::~GameObject()
	{

		if (myScene != nullptr)
		{
			PostMaster::AssertState(*myScene);
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

		PostMaster::AssertState(*myScene);

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
			for (unsigned short i = myChildren.Size(); i > 0; i--)
			{
				myChildren[i - 1]->Remove();
			}

			for (unsigned short iComponentTypes = 0; iComponentTypes < myComponents.Size(); ++iComponentTypes)
			{
				for (unsigned short iComponent = 0; iComponent < myComponents[iComponentTypes].Size(); ++iComponent)
				{
					BaseComponent * tempBaseComponent = myComponents[iComponentTypes][iComponent];
					tempBaseComponent->OnRemoved();
					tempBaseComponent->Disable();
				}
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
		if (aParent == myParent)
			return;

		if (myParent != nullptr)
		{
			myParent->myChildren.RemoveAtIndex(myParent->myChildren.Find(this));
		}

		myParent = aParent;

		if (myParent != nullptr)
		{
			myParent->myChildren.Add(this->AsPointer());
		}
	}

	const GrowingArray<ObjectPtr> GameObject::GetChildren() const
	{
		return myChildren;
	}

	void GameObject::AddEventSubscriber(const size_t aIndex, const unsigned short & aSubscriber)
	{
		if (myEventSubscribers.Size() <= static_cast<unsigned short>(aIndex))
		{
			myEventSubscribers.Resize(static_cast<unsigned short>(aIndex + 1));
		}

		myEventSubscribers[static_cast<unsigned short>(aIndex)].Add(aSubscriber);
	}

	void GameObject::SetIndexInFactory(unsigned short aIndex)
	{
		myIndexInFactory = aIndex;
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

	const ObjectPtr GameObject::AsPointer() const
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

	const Vector3f GameObject::AdjustOffset(const Vector3f & myOffset)
	{
		Vector3f newOffset;
		Quaternion worldRot = GetWorldRotation();

		newOffset += myOffset.x * worldRot.GetRight();
		newOffset += myOffset.y * worldRot.GetUpward();
		newOffset += myOffset.z * worldRot.GetForward();

		return newOffset;
	}

	void GameObject::ToJson(JsonSerializer &aSerializer) const 
{
		JsonSerializer &serializer = aSerializer;
		serializer.WriteNode("name", myIdentifier);
		serializer.WriteArray("components");
		for(unsigned short i = 0; i < myComponents.Size(); ++i)
		{
			for(unsigned short j = 0; j < myComponents[i].Size(); ++j)
			{
				if (myComponents[i][j]->GetShouldBeSaved() == true)
				{
					serializer.WriteObject();
					myComponents[i][j]->ToJson(aSerializer);
					serializer.StepOut();
				}
			}
		}
		serializer.WriteObject();
		serializer.WriteNode("localPosition", myPosition);
		serializer.WriteNode("localRotation", myRotation.GetXYZW());
		serializer.WriteNode("localScale", myScale);
		serializer.WriteNode("type", "Transform");
		serializer.StepOut();
		serializer.StepOut();

		serializer.WriteArray("children");
		for(unsigned short i = 0; i < myChildren.Size(); ++i)
		{
			if (myChildren[i]->GetShouldBeSaved() == true)
			{
				serializer.WriteObject();
				myChildren[i]->ToJson(aSerializer);
				serializer.StepOut();
			}
		}
		serializer.StepOut();
	}

	
	//Play 3D sound from object if it has a speaker component, otherwise print a warning to the console and play it in 2D
	void GameObject::Play3DSound(const std::string& aSoundEventName)
	{
		Play3DSound(aSoundEventName.c_str());
	}

	//Play 3D sound from object if it has a speaker component, otherwise print a warning to the console and play it in 2D
	void GameObject::Play3DSound(const char* aSoundEventName)
	{
		if (GetComponentCount<SB::SpeakerComponent>() > 0)
		{
			GetComponent<SB::SpeakerComponent>()->PostSoundEvent(aSoundEventName);
		}
		else
		{
			SB::Engine::GetSoundManager().PostEvent(aSoundEventName);
#ifndef PUBLISH
			std::cout << "WARNING: Object named " << myIdentifier << " is missing a Speaker Component and attempting to play " << aSoundEventName <<  " as a 3D sound! Please add a speaker component!" << std::endl;
#endif
		}
	}

}
