#pragma once
#include "Controller.h"


struct SetArriveTargetEvent
{
	SetArriveTargetEvent(const SB::Vector2f aPosition) : myTargetPosition(aPosition)
	{}

	SB::Vector2f myTargetPosition;
};

class AIArriveController : public Controller
{
public:
	AIArriveController(const Unit & aParentUnit);
	~AIArriveController();

	void RecieveEvent(const SetArriveTargetEvent & aEvent);

	virtual SB::Vector2f GetDirection(const SB::Time & aDeltaTime) override;
	//virtual float GetSpeed() override;

	virtual void DebugRender(const SB::GuiRenderTarget & aRenderTarget) const override;

private:
	bool myStillNeedToMove;

	SB::Vector2f myTargetPosition;
	float myTargetRadius;
};

