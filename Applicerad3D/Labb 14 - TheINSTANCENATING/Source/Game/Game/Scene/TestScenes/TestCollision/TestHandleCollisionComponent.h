#pragma once
#include "Engine\Component\BaseComponent.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"

namespace SB
{
	struct CollisionEvent;
}

struct ObjectOutOfHealthMessage;

class TestHandleCollisionComponent :
	public SB::BaseComponent, public SB::EventSubscriber<SB::CollisionEvent>, public SB::EventSubscriber<ObjectOutOfHealthMessage>
{
public:
	TestHandleCollisionComponent();
	~TestHandleCollisionComponent();

	void Initialize() override;
	
	bool HasCollided();

	void RecieveEvent(const SB::CollisionEvent & aEvent) override;
	void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;

	void ToJson() const override;
	

private:
	bool myHasCollided;
};

