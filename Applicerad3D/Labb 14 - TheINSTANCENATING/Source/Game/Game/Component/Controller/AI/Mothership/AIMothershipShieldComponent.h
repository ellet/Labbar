#pragma once
#include "..\AIControllerComponent.h"
namespace SB
{
	class PhysicsComponent;
}

struct ObjectOutOfHealthMessage;
class AIMothershipComponent;

class AIMothershipShieldComponent : public AIControllerComponent, public SB::EventSubscriber<ObjectOutOfHealthMessage>
{
public:
	AIMothershipShieldComponent();
	~AIMothershipShieldComponent();

	void SetPositionAndRotation(const SB::Vector3f & aPosition, const SB::Quaternion & aRotation);
	_inline void SetMothership(AIMothershipComponent* aMothership, unsigned short aShieldNumber)
	{
		myMothership = aMothership;
		myShieldNumber = aShieldNumber;
	}

	virtual void Initialize() override;
	virtual void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;

private:
	AIMothershipComponent* myMothership;
	SB::PhysicsComponent* myPhysicsComponent;
	unsigned short myShieldNumber;
};

