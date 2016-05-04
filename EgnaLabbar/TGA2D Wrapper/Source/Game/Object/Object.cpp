#include "stdafx.h"
#include "Object.h"
#include <CollisionManager\CollisionManager.h>
#include <tga2d\sprite\sprite.h>
#include <CollisionManager\CollisionShapes\BoxShape.h>
#include "../EventManager/Events/AllEvents.h"
#include <DLDebug/DL_Debug.h>

#include <CollisionManager/EventCollider.h>
#include "../EventManager/Events/PlayDialogEvent.h"

Object::Object()
{
	myFireEvents.Init(5);
	myWaterEvents.Init(5);
	myWindEvents.Init(5);
	myEarthEvents.Init(5);
	myEventCollider = nullptr;
	myExamineEvent = nullptr;
}



Object::~Object()
{
}

void Object::Init(std::string &aName)
{
	myName = aName;
}


const std::string &Object::GetName() const
{
	return myName;
}

void Object::SetName(const std::string aString)
{
	myName = aString;
}

void Object::SetEventCollider(EventCollider* aEventColliider)
{
	myEventCollider = aEventColliider;
}

void Object::Update(const float aDeltaTime)
{
	BaseAnimatedGameObject::Update(aDeltaTime);
	if (myIsActive == true && myEventCollider != nullptr)
	{
		CollisionManager::AddAEventCollider(*myEventCollider);
		myEventCollider->DrawCollisionBox();
	}
}

void Object::SetPositionAndCollider(const Vector2f & aPosition)
{
	SetPosition(aPosition);
	myEventCollider->ChangePosition(aPosition);
}

void Object::AddElementEvent(eElementType aElementType, Event *aEvent)
{
	switch (aElementType)
	{
	case eElementType::eFire:
		myFireEvents.Add(aEvent);
		break;
	case eElementType::eWind:
		myWindEvents.Add(aEvent);
		break;
	case eElementType::eWater:
		myWaterEvents.Add(aEvent);
		break;
	case eElementType::eEarth:
		myEarthEvents.Add(aEvent);
		break;
	default:
		bool f = false;
		DL_ASSERT(f, "That element type is not supported!");
		break;
	}
}

void Object::SetExamineEvent(PlayDialogEvent * const aDialogueEvent)
{
	myExamineEvent = aDialogueEvent;
}

void Object::TriggerElementEvent(eElementType aElementType)
{
	switch (aElementType) 
	{
	case eElementType::eFire:
		for (unsigned short i = 0; i < myFireEvents.Size(); i++)
		{
			myFireEvents[i]->OneShotEvent();
		}
		break;
	case eElementType::eWind:
		for (unsigned short i = 0; i < myWindEvents.Size(); i++)
		{
			myWindEvents[i]->OneShotEvent();
		}
		break;
	case eElementType::eWater:
		for (unsigned short i = 0; i < myWaterEvents.Size(); i++)
		{
			myWaterEvents[i]->OneShotEvent();
		}
		break;
	case eElementType::eEarth:
		for (unsigned short i = 0; i < myEarthEvents.Size(); i++)
		{
			myEarthEvents[i]->OneShotEvent();
		}
		break;
	default:
		break;
	}
}

void Object::TriggerOnUse()
{
	if (myEventCollider != nullptr)
	{
		myEventCollider->myEvent->OnMouseClickEvent();
	}
}

void Object::TriggerOnExamine()
{
	if (myExamineEvent != nullptr)
	{
		myExamineEvent->OneShotEvent();
	}
}
