#pragma once
#include "FormationGroup.h"
#include "Unit.h"
#include "Utilities\Randomizer\Randomizer.h"


class LabbAIScene : public SB::Scene
{
public:
	LabbAIScene(SB::PostMasterState & aPostMasterState);
	~LabbAIScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;

private:

	void CollisionCheckAgainstVolume();
	bool CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle);

	void OnCollisionEnter(unsigned short aObjectID);
	void OnCollisionExit(unsigned short aObjectID);

	SB::GrowingArray<bool> myCollidedStates;

	SB::Sprite myVolumeSprite;


	SB::Randomizer myRandomizer;
	SB::Vector2f myMousePosition;

	FormationGroup myUnitGroup;

	SB::GrowingArray<Unit> myUnits;

	std::shared_ptr<SB::Subscription<SB::MouseMovedMessage>> myMouseListener;
	SB::InputListener myInputListener;
};

