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

	static LabbAIScene & GetScene();

	void AssignNewTargetVolume(const unsigned short aObjectID);

private:
	static LabbAIScene * ourScene;

	void CollisionCheckUnits();
	bool CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle);

	void OnCollisionEnter(const unsigned short aObjectID, const unsigned short aVolumeID);
	void OnCollisionExit(const unsigned short aObjectID, const unsigned short aVolumeID);

	SB::Randomizer myRandomizer;
	SB::Vector2f myMousePosition;

	FormationGroup myUnitGroup;

	SB::GrowingArray<Unit> myUnits;
	SB::GrowingArray<Unit> myEnemyUnits;

	std::shared_ptr<SB::Subscription<SB::MouseMovedMessage>> myMouseListener;
	SB::InputListener myInputListener;
};

