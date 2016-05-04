#pragma once
#include "Event.h"


class OnOffWeigth;

class LiftAndReleaseWeight : public Event
{
public:
	LiftAndReleaseWeight(OnOffWeigth * aOnOffWeight);
	~LiftAndReleaseWeight();

	virtual void OneShotEvent() override;

private:
	OnOffWeigth * myOnOffWeight;
};