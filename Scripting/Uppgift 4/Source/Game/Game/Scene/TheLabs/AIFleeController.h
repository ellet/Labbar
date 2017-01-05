#pragma once
#include "Controller.h"
#include "CircleShape.h"

struct SetFleeFromPositionEvent
{
	SetFleeFromPositionEvent(const SB::Vector2f aPosition) : myFleeFromPosition(aPosition)
	{}

	SB::Vector2f myFleeFromPosition;
};

class AIFleeController : public Controller
{
public:
	AIFleeController(const Unit & aParentUnit);
	~AIFleeController();


	virtual SB::Vector2f GetDirection(const SB::Time & aDeltaTime) override;
	//virtual float GetSpeed() override;
	SB::CircleShape GetFleeArea() const;

	void RecieveEvent(const SetFleeFromPositionEvent & aFleeEvent);

	virtual void DebugRender(const SB::GuiRenderTarget & aRenderTarget) const override;

private:
	bool myShouldFlee;

	SB::Vector2f myFleeFromPosition;
	float myFleeRadius;
};