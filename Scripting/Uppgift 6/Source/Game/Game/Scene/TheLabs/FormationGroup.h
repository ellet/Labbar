#pragma once

struct SetSeekTargetEvent;

class FormationGroup
{
public:
	FormationGroup();
	~FormationGroup();

	void RecieveEvent(const SetSeekTargetEvent & aSeekTargetEvent);
	void SetOffset(const float aOffsetAmount);

	SB::Vector2f GetPositionInFormation(const unsigned short aIndex);

	unsigned short AddUnitToGroup();

private:
	unsigned short myUnitCounter;

	SB::Vector2f myGroupOffset;

	SB::Vector2f myTargetPosition;
};

