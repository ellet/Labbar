#include "stdafx.h"
#include "BaseComponent.h"
#include "Utilities\UniqeIdentifier.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"
#include "Engine\GameObject\GameObject.h"

namespace ENGINE_NAMESPACE
{
	BaseComponent::BaseComponent()
	{
		myIsEnabled = true;
	}

	BaseComponent::~BaseComponent()
	{
	}

	bool BaseComponent::Prepare(bool aLoadAsynchronously)
	{
		return true;
	}

	void BaseComponent::Update(const Time & aDeltaTime)
	{
	}

	void BaseComponent::Render() const
	{
	}

	void BaseComponent::Initialize()
	{
	}

	void BaseComponent::OnRemoved()
	{
	}

	void BaseComponent::LoadData(DataNode aProperties)
	{
	}

	void BaseComponent::DebugUpdate(const Time & aDeltaTime)
	{
	}

	void BaseComponent::DebugRender() const
	{
	}

	GameObject & BaseComponent::GetGameObject() const
	{
		return *myObject;
	}

	void BaseComponent::SetGameObject(GameObject & anObject)
	{
		myObject = &anObject;
	}

	void BaseComponent::Disable()
	{
		myIsEnabled = false;
	}
}
