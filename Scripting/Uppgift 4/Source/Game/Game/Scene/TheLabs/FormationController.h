#pragma once
#include "Controller.h"
#include "..\Behaviours\SeekBehaviour.h"
#include "..\Behaviours\EvadeBehaviour.h"
#include "CircleShape.h"

class FormationGroup;

class FormationController : public Controller
{
public:
	FormationController(const Unit & aParentUnit, FormationGroup & aGroup);
	~FormationController();


	virtual SB::Vector2f GetDirection(const SB::Time & aDeltaTime) override;
	void RecieveEvent(const PointToEvadeEvent & aEvadeEvent);

	SB::CircleShape GetEvadeArea();

	virtual void DebugRender(const SB::GuiRenderTarget & aRenderTarget) const override;

private:
	unsigned short myFormationIndex;
	FormationGroup * myGroup;
	SeekBehaviour mySeekBehaviour;
	EvadeBehaviour myEvadeBehaviour;
};

