#pragma once
//#include <BaseClasses/BaseGameObject/BaseGameObject.h>
#include "OnOffWeigth.h"
#include <Matriser/matrix33.h>

struct WeightData
{
	std::string mySpritePath;
	Vector2f myOffset;
	float myAngleWeight;
	Vector2f myBoxShapeSize;
};

struct VictoryAngleData
{
	std::string mySpritePath;
	float myAngle;
	
	CU::GrowingArray<Event*> myEvents;
};

struct BeamData
{
	std::string mySpritePath;
	Vector2f myMainPoint;
	Vector2f myLeftSideOffset;
	Vector2f myRightSideOffset;

	float VictoryPointDistanceFromLine;

	CU::GrowingArray<WeightData*> myLeftSideWeights;
	CU::GrowingArray<WeightData*> myRightSideWeights;
	CU::GrowingArray<VictoryAngleData*> myVictoryAngles;
};


struct VictoryAngle : public Object
{
	VictoryAngle(const VictoryAngleData & aVictoryAngleData, const Vector2f aPosition)
	{
		LoadSprite(aVictoryAngleData.mySpritePath.c_str());
		SetPivot(Vector2f(0.5f, 0.5f));

		const Vector2f tempPosition = aPosition - (VictoryAngleDistanceOffset * Matrix33f::CreateRotateAroundZ(aVictoryAngleData.myAngle));

		SetPosition(tempPosition);
		SetRotation(aVictoryAngleData.myAngle - DEGRESS_TO_RADIANSF(-90.f));
		myIhaveBeenAchieved = false;
		myAngleThatNeedsToBeAchieved = aVictoryAngleData.myAngle;
	}

	virtual void Update(const float aDeltaTime) override
	{
		(aDeltaTime);
		if (myIhaveBeenAchieved == false)
		{
			SetColor(Vector4f::One);
		}
		else
		{
			SetColor(Vector4f(0.f, 0.f, 0.f, 1.f));
		}
	}

	virtual void Draw() const override
	{
		BaseGameObject::Draw();
	}

	
	
	static Vector2f VictoryAngleDistanceOffset;
	bool myIhaveBeenAchieved;
	float myAngleThatNeedsToBeAchieved;	
};

class BalanceLine : public Object
{
public:
	BalanceLine(const BeamData & aBeamData);
	//BalanceLine();
	~BalanceLine();

	virtual void Update(const float aDeltaTime) override;

	virtual void Draw() const override;

private:
	float myCurrentAngle;
	float myBalanceSpeed;

	Vector2f myLeftSideOffset;
	Vector2f myRightSideOffset;

	CU::GrowingArray<OnOffWeigth*> myLeftWeights;
	CU::GrowingArray<OnOffWeigth*> myRightWeights;
	CU::GrowingArray<VictoryAngle*> myVictoryAngles;
};