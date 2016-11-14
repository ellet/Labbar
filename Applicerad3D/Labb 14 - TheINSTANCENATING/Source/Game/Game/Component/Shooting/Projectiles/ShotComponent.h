#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Engine/GameObject/ObjectEventSystem/EventSubscriber.h>

namespace SB
{
	struct TriggerCollisionEvent;
	struct EndOfFrameMessage;
}

class ShotComponent : public SB::BaseComponent, public SB::EventSubscriber<SB::TriggerCollisionEvent>, public SB::EventSubscriber<SB::EndOfFrameMessage>
{
public:
	ShotComponent();
	~ShotComponent();
	virtual void Initialize() override;
	void OnRemoved() override;

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;
	virtual void RecieveEvent(const SB::EndOfFrameMessage & aEvent) override;

	void SetSpeed(const SB::Vector3f & aSpeed);
	inline float GetDamage() const
	{
		return myDamage;
	}
	inline void SetDamage(const float aValue)
	{
		myDamage = aValue;
	}
	inline SB::Time GetLifeTime() const
	{
		return myLifeTime;
	}

	void SetParentShooter(const SB::ObjectPtr aShooter);
	const SB::ObjectPtr GetParentShooter() const;


protected:
	void CreateImpactParticles(const SB::Vector3f & aPosition);

	SB::ObjectPtr myShooterParent;
	SB::Vector3f mySpeed;
	SB::Time myAge;
	SB::Time myLifeTime;
	float myDamage;
	bool myHasHit;
};

