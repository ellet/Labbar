#pragma once
#include "Controller.h"
#include "..\Behaviours\SeekBehaviour.h"
#include "..\Behaviours\WanderBehaviour.h"
#include "..\Behaviours\EvadeBehaviour.h"
#include "CircleShape.h"



class BlendBehaviourController : public Controller
{
public:
	BlendBehaviourController(const Unit & aParentUnit);
	~BlendBehaviourController();

	virtual SB::Vector2f GetDirection(const SB::Time & aDeltaTime) override;

	void RecieveEvent(const SetSeekTargetEvent & aSeekTargetEvent);
	void RecieveEvent(const PointToEvadeEvent & aEvadeEvent);

	SB::CircleShape GetEvadeArea();

	SB::Vector2f GetFuturePosition(const float aTimeDelta);

private:
	SeekBehaviour mySeekBehaviour;
	WanderBehaviour myWanderBehaviour;
	EvadeBehaviour myEvadeBehaviour;
};

