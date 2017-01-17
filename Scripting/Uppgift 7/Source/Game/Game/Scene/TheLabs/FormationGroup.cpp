#include "stdafx.h"
#include "FormationGroup.h"
#include "..\Behaviours\SeekBehaviour.h"
#include "PollingStation.h"

FormationGroup::FormationGroup()
{
	myUnitCounter = 0;

	myTargetPosition = SB::Vector2f(400.f, 400.f);

	PollingStation::RegisterFormationGroup(*this);
}


FormationGroup::~FormationGroup()
{
}

void FormationGroup::RecieveEvent(const SetSeekTargetEvent & aSeekTargetEvent)
{
	myTargetPosition = aSeekTargetEvent.myTargetPosition;
}

void FormationGroup::SetOffset(const float aOffsetAmount)
{
	myGroupOffset = SB::Vector2f( aOffsetAmount, aOffsetAmount);
}

SB::Vector2f FormationGroup::GetPositionInFormation(const unsigned short aIndex)
{
	float castedGroupIndex = static_cast<float>(aIndex);

	SB::Vector2f targetFormationPosition;
	targetFormationPosition.x = -myGroupOffset.x + myTargetPosition.x + (myGroupOffset.x * (std::fmod(castedGroupIndex, 3.f)));
	targetFormationPosition.y = -myGroupOffset.y + myTargetPosition.y + (myGroupOffset.y * std::floor((castedGroupIndex / 3.f)));

	return targetFormationPosition;
}

unsigned short FormationGroup::AddUnitToGroup()
{
	return myUnitCounter++;
}
