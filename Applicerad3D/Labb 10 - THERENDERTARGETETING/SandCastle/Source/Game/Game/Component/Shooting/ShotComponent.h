#pragma once
#include "Engine\Component\BaseComponent.h"
#include <Engine/GameObject/ObjectEventSystem/EventSubscriber.h>

namespace SB
{
	struct CollisionEvent;
}

class ShotComponent : public SB::BaseComponent, public SB::EventSubscriber<SB::CollisionEvent>
{
public:
	ShotComponent();

	void SetSpeed(const SB::Vector3f & aSpeed);

	~ShotComponent();

	virtual void RecieveEvent(const SB::CollisionEvent & aEvent) override;

	virtual void Update(const SB::Time & aDeltaTime) override;

	inline float GetDamage() const
	{
		return myDamage;
	}
	inline void SetDamage(const float aValue)
	{
		myDamage = aValue;
	}

	bool myHasHit;


	virtual void Initialize() override;

private:
	void CreateInpactParticles(const SB::Vector3f & aPosition);

	SB::Vector3f mySpeed;
	SB::Time myAge;
	float myDamage;
};

