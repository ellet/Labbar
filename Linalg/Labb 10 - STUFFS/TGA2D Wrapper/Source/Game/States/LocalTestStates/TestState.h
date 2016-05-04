#pragma once
#include <BaseClasses/BaseState/BaseState.h>
#include "../../Object/TestObject.h"
#include "../../Object/StudsiStudsiLinje.h"
#include <Utility/Randomizer/Randomizer.h>
#include <Timer/Alarm.h>
#include <tga2d/text/text.h>

class TestState : public BaseState
{
public:
	TestState();
	~TestState();

	virtual void Init() override;

	virtual void Update(const float aDeltaTime) override;

	virtual void Draw() const override;

	virtual void DoOnChangeFrom() override;

	virtual void DoOnChangeTo() override;

	void SpawnBall();

private:
	CU::GrowingArray<StudsiStudsiLinje*> myLines;
	CU::GrowingArray<TestObject*> myBallz;

	Randomizer myRandomizerPosX;
	Randomizer myRandomizerPosY;
	Randomizer myRandomizerSpeed;

	size_t myBallCount;
	DX2D::CText * myText;

	CU::Alarm mySpawnTimer;
};

