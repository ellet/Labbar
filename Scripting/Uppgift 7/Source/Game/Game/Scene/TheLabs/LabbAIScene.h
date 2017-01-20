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

	void RemoveUnit(const unsigned short aIndexToRemove);
	unsigned short SpawnUnit(const std::string & aFilePath, const SB::Vector2f & aPosition);
	void AddToObjectPosition(const unsigned short aObjectID, const SB::Vector2f & aDeltaMovement);
	bool CheckIfUnitsCollide(const unsigned short aObjectID, const unsigned short aOtherObject);

	const SB::Vector2f GetObjectsPosition(const unsigned short aObjectID);
	void SetPositionOnObject(const unsigned short aObjectID, const SB::Vector2f & aPosition);
	void ClearUnits();

private:
	static LabbAIScene * ourScene;

	void CollisionCheckUnits();
	bool CollisionCheck(const SB::CircleShape & aFirstCircle, const SB::CircleShape & aSecondCircle);

	SB::Randomizer myRandomizer;
	SB::Vector2f myMousePosition;

	FormationGroup myUnitGroup;

	SB::Stack<unsigned short> myFreeIndexes;
	SB::GrowingArray<Unit> myUnits;
	SB::GrowingArray<Unit> myEnemyUnits;

	std::shared_ptr<SB::Subscription<SB::MouseMovedMessage>> myMouseListener;
	SB::InputListener myInputListener;
};

