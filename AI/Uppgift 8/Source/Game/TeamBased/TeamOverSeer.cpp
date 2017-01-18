#include "stdafx.h"
#include "TeamOverSeer.h"
#include "Controllers\TeamBasedGameController.h"

const float TimerStartAmount = 2.f;

TeamOverSeer::TeamOverSeer()
{
	mySpawnTimer = TimerStartAmount;
}


TeamOverSeer::~TeamOverSeer()
{
}

void TeamOverSeer::InitBase(const std::string & aFilePath, const SB::Vector2f & aPosition)
{
	myBase.SetSprite(aFilePath);
	myBase.SetPosition(aPosition);
}

void TeamOverSeer::SetUnitSprite(const std::string & aFilePath)
{
	myUnitsSpritePath = aFilePath;
}

void TeamOverSeer::SetUnitsTarget(const SB::Vector2f & aPosition)
{
	myCurrentTarget = aPosition;
}

void TeamOverSeer::Update(const float aDeltaTime)
{
	mySpawnTimer -= aDeltaTime;
	if (mySpawnTimer <= 0.f)
	{
		mySpawnTimer = TimerStartAmount;
		AddUnit();
	}


	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit]->Update(aDeltaTime);
	}
}

void TeamOverSeer::Render() const
{
	for (unsigned short iUnit = 0; iUnit < myUnits.Size(); ++iUnit)
	{
		myUnits[iUnit]->Render();
	}

	myBase.Render();
}

void TeamOverSeer::AddUnit()
{
	myUnits.Add(new Actor());
	Actor & newUnit = *myUnits.GetLast();

	newUnit.SetSprite(myUnitsSpritePath);
	newUnit.SetPosition(myBase.GetPosition());
	newUnit.SetController<TeamBasedGameController>().SetTargetPosition(myCurrentTarget);
}
