#pragma once
#include "Engine/Component/BaseComponent.h"

namespace SB
{
	struct CollisionEvent;
}

struct ObjectOutOfHealthMessage;

class PlayerComponent :
	public SB::BaseComponent, public SB::EventSubscriber<SB::CollisionEvent>, public SB::EventSubscriber<ObjectOutOfHealthMessage>
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Initialize() override;

	void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;
	void RecieveEvent(const SB::CollisionEvent & aEvent) override;
};