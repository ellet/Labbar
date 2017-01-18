#pragma once
#include "Actors\Actor.h"
#include "..\..\Utilities\Utilities\Container\GrowingArray.h"


class TeamOverSeer
{
public:
	TeamOverSeer();
	~TeamOverSeer();

	void InitBase(const std::string & aFilePath, const SB::Vector2f & aPosition);

	void SetUnitSprite(const std::string & aFilePath);
	void SetUnitsTarget(const SB::Vector2f & aPosition);
	
	void Update(const float aDeltaTime);
	void Render() const;

private:
	void AddUnit();

	SB::GrowingArray<Actor *> myUnits;
	Actor myBase;
	std::string myUnitsSpritePath;
	std::string myBaseSpritePath;
	SB::Vector2f myCurrentTarget;

	float mySpawnTimer;
};

