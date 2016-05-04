#include "stdafx.h"
#include "OnOffWeigth.h"
#include <Matriser/matrix33.h>
#include "BalanceLine.h"

OnOffWeigth::OnOffWeigth(const WeightData * const WeightData, const Vector2f aPosition)
{
	myIsLifted = false;
	myAngleWeight = WeightData->myAngleWeight;
	myOffset = WeightData->myOffset;
	LoadSprite(WeightData->mySpritePath.c_str());
	SetPosition(aPosition + myOffset);

	Event * tempEvent = new LiftAndReleaseWeight(this);
	OnClickEvent * tempClickOnEvent = new OnClickEvent(static_cast<Object*>(this), &MouseInput::GetInventoryPointer());


	tempClickOnEvent->AddEvent(tempEvent);


	AddElementEvent(eElementType::eWind, tempEvent);

	BoxShape * tempBox = new BoxShape(GetPosition(), WeightData->myBoxShapeSize);
	EventCollider * tempEventCollider = new EventCollider(tempBox, tempClickOnEvent, this);
	SetEventCollider(tempEventCollider);
}

void OnOffWeigth::Update(const float aDeltaTime, const Vector2f aPosition, const float aAngle)
{
	(aDeltaTime);
	SetPositionAndCollider(aPosition + (myOffset * Matrix33f::CreateRotateAroundZ(aAngle)));

	if (myIsLifted == true)
	{
		SetColor(Vector4f(0.5f, 0.5f, 0.5f, 1.f));
	}
	else
	{
		SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));
	}

	Object::Update(aDeltaTime);
}

void OnOffWeigth::Draw() const
{
	
	BaseGameObject::Draw();
}
