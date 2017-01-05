#include "stdafx.h"
#include "BaseComponent.h"
#include "Utilities\UniqeIdentifier.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"
#include "Engine\GameObject\GameObject.h"

namespace SB
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

	void BaseComponent::BeginUpdate(const Time & aDeltaTime)
	{
	}

	void BaseComponent::Update(const Time & aDeltaTime)
	{
	}

	void BaseComponent::EndUpdate(const Time & aDeltaTime)
	{
	}

	void BaseComponent::Render(const Camera & aCamera) const
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

	void BaseComponent::DebugRender(const Camera & aCamera) const
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
