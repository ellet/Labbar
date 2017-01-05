#pragma once
#include "BaseBehaviour.h"

struct PointToEvadeEvent
{
	PointToEvadeEvent(const SB::Vector2f & aPointToEvade) : myPointToEvade(aPointToEvade)
	{}

	SB::Vector2f myPointToEvade;
};

class EvadeBehaviour : public BaseBehaviour
{
public:
	EvadeBehaviour(const Unit & aParentUnit);
	~EvadeBehaviour();

	virtual Steering GetSteering(const SB::Time & aDeltaTime) override;

	void AddAvoidPosition(const SB::Vector2f & aPositionToEvade);

	float GetEvadeRadius();

	static float ourMaxWeight;
	static float ourEvadeWeight;

private:
	SB::GrowingArray<SB::Vector2f> myPointsToEvade;

	SB::Stopwatch myUpdateTimer;
	
	Steering mySteering;

	void HandleWalls(Steering & aSterringToSet);
	void HandleEvadePoint(const SB::Vector2f & aPointToEvade, Steering & aSterringToSet);
};
