#pragma once
#include "Engine/Component/BaseComponent.h"

namespace SB
{
	struct TriggerCollisionEvent;
}
struct ExplosionData;
struct ObjectOutOfHealthMessage;

class EnemyMineComponent :
	public SB::BaseComponent, public SB::EventSubscriber<SB::TriggerCollisionEvent>, public SB::EventSubscriber<ObjectOutOfHealthMessage>
{
public:
	EnemyMineComponent();
	~EnemyMineComponent();

	void Initialize() override;

	void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;
	void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;

	virtual void LoadData(SB::DataNode aProperties) override;
	void ToJson() const;

private:
	ExplosionData* myExplosionData;
};


