#include "stdafx.h"
#include "ChangeAnimationEvent.h"

#include "../../Object/Object.h"

ChangeAnimationEvent::ChangeAnimationEvent(const std::string & aAnimationToChangeTo, Object * const aObjectToChangeAnimationOn)
{
	myObjectToChangeAnimationOn = aObjectToChangeAnimationOn;
	myAnimationToChangeTo = aAnimationToChangeTo;
}


ChangeAnimationEvent::~ChangeAnimationEvent()
{
}

void ChangeAnimationEvent::OneShotEvent()
{
	myObjectToChangeAnimationOn->PlayAnimtaion(myAnimationToChangeTo);
}
