#pragma once
#include "Engine/Component/BaseComponent.h"

namespace SB
{
	struct TriggerCollisionEvent;
}

struct ExplosionData
{
	ExplosionData()
	{
		myLifeTime = 0.f;
		myExplosionDamage = 0.f;
		myMaxRadius = 0.f;
	}
	float myLifeTime;
	float myExplosionDamage;
	float myMaxRadius;
};

class ExplosionComponent : public SB::BaseComponent, public SB::EventSubscriber<SB::TriggerCollisionEvent>
{
public:
	ExplosionComponent();
	~ExplosionComponent();

	void LoadData(SB::DataNode aProperties) override;
	void ToJson() const override;

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Initialize() override;
	void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;
	void SetExplosionData(const ExplosionData & aExplosionData);

private:
	void GraphicExplosion(const SB::Vector3f & aPosition) const;

	SB::GrowingArray<const SB::GameObject*> myNearbyObjects;
	ExplosionData myExplosionData;
	float myCurrentLifeTime;
};

