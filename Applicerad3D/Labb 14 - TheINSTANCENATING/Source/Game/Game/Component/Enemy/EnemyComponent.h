#pragma once
#include "Engine\Component\BaseComponent.h"

namespace SB
{
	struct TriggerCollisionEvent;
}

struct ObjectOutOfHealthMessage;

class EnemyComponent :
	public SB::BaseComponent, public SB::EventSubscriber<SB::TriggerCollisionEvent>, public SB::EventSubscriber<ObjectOutOfHealthMessage>
{
public:
	EnemyComponent();
	~EnemyComponent();

	void Initialize() override;

	void TakeDamage(const float aDamageAmount);

	void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;
	void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;


	virtual void ToJson() const override;

private:
	void GraphicExplosion(const SB::Vector3f & aPosition) const;
};