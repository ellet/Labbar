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

	const SB::Vector2f & GetVolumePosition(const unsigned short aVolumeIndex);

	static LabbAIScene & GetScene();

	void SetActiveObject(const unsigned short aObjectID);
	unsigned short GetActiveObject() const;

	void AssignNewTargetVolume(const unsigned short aObjectID);

private:
	static LabbAIScene * ourScene;

	void CollisionCheckAgainstVolume();
	bool CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle);
	void CollisionCheckMouse();

	void OnCollisionEnter(const unsigned short aObjectID, const unsigned short aVolumeID);

	unsigned short myCurrentActiveObject;

	unsigned short myMouseCurrentIndex;

	SB::GrowingArray<bool> myCollidedStates;

	SB::GrowingArray<SB::Sprite> myVolumeSprites;
	SB::GrowingArray<unsigned short> myOccupiedIndexes;

	SB::Randomizer myRandomizer;
	SB::Vector2f myMousePosition;

	FormationGroup myUnitGroup;

	SB::GrowingArray<Unit> myUnits;

	std::shared_ptr<SB::Subscription<SB::MouseMovedMessage>> myMouseListener;
	SB::InputListener myInputListener;
};

