#pragma once
#include "Object.h"
#include <CollisionManager/CollisionShapes/BoxShape.h>
#include <CollisionManager/EventCollider.h>
#include "../EventManager/Events/LiftAndReleaseWeight.h"
#include "../EventManager/Events/OnClickEvent.h"
#include <Input/MouseInput/MouseInput.h>

class Inventory;
struct WeightData;

class OnOffWeigth : public Object
{
public:
	/*OnOffWeigth()
	{
		myIsLifted = false;
		myAngleWeight = 0.f;
		LoadSprite("Sprites/TestSprites/BalanceBeamWeight.dds");
		SetPosition(Vector2f::Zero);
		
		Event * tempEvent = new LiftAndReleaseWeight(this);
		OnClickEvent * tempClickOnEvent = new OnClickEvent(this, &MouseInput::GetInventoryPointer());

		tempClickOnEvent->AddEvent(tempEvent);

		AddElementEvent(eElementType::eWind, tempEvent);
		BoxShape * tempBox = new BoxShape(GetPosition(), Vector2f(50.f, 50.f));
		EventCollider * tempEventCollider = new EventCollider(tempBox, tempClickOnEvent, this);
		SetEventCollider(tempEventCollider);
	};*/

	OnOffWeigth(const WeightData * const aWeightData, const Vector2f aPosition);


	/*OnOffWeigth(const float aWeight, const Vector2f aPosition, const Vector2f aOffsetVector)
	{
		myIsLifted = false;
		myAngleWeight = aWeight;
		myOffset = aOffsetVector;
		LoadSprite("Sprites/TestSprites/BalanceBeamWeight.dds");
		SetPosition(aPosition + myOffset);

		Event * tempEvent = new LiftAndReleaseWeight(this);
		OnClickEvent * tempClickOnEvent = new OnClickEvent(static_cast<Object*>(this), &MouseInput::GetInventoryPointer());

		tempClickOnEvent->AddEvent(tempEvent);

		
		AddElementEvent(eElementType::eWind, tempEvent);
		
		BoxShape * tempBox = new BoxShape(GetPosition(), Vector2f(50.f, 50.f));
		EventCollider * tempEventCollider = new EventCollider(tempBox, tempClickOnEvent, this);
		SetEventCollider(tempEventCollider);
	};*/

	void SetLifted()
	{
		myIsLifted = true;
	}

	void SetDropped()
	{
		myIsLifted = false;
	}

	bool GetLiftedState()
	{
		return myIsLifted;
	}

	void SetAngleWeight(const float aWeightInAngles)
	{
		myAngleWeight = aWeightInAngles;
	}

	float GetAngleWeight() const
	{
		return myAngleWeight;
	}

	virtual void Update(const float aDeltaTime, const Vector2f aPosition, const float aAngle);

	virtual void Draw() const override;



private:
	bool myIsLifted;
	float myAngleWeight;
	Vector2f myOffset;
};

