#include "stdafx.h"
#include "TestEndState.h"
#include <BaseClasses\FactoryGameObject\FactoryGameObject.h>
#include <Input/MouseInput/MouseInput.h>
#include <CollisionManager/CollisionManager.h>
#include <tga2d\sprite\sprite.h>
#include <CollisionManager/EventCollider.h>
#include "../Game/EventManager/Events/OnClickEvent.h"
#include "../Game/EventManager/Events/ActivateMagicElementEvent.h"
#include "../Game/EventManager/Events/ChangeLevelEvent.h"
#include "../Game/EventManager/Events/SetActiveEvent.h"
#include "../Game/Levels/LevelManager.h"

#include <iostream>

TestEndState::TestEndState()
{	
	
	myBackground1 = FactoryGameObject::CreateObject<Object>();
	myBackground1->LoadSprite("Sprites/Backgrounds/EndScene/gux_village_whole.dds");
	myBackground1->SetPivot(Vector2f(0.f, 0.f));
	myBackground1->SetPosition(Vector2f(0.f, 0.f));
	
	//LevelManager::ChangeLevel(std::string("EndScene"));

	//myUpperLeftHouse = FactoryGameObject::CreateObject<Object>();
	//myUpperLeftHouse->LoadSprite("Sprites/Backgrounds/EndScene/upper_left_house.dds");
	//myUpperLeftHouse->SetPivot(Vector2f(0.f, 0.f));
	//myUpperLeftHouse->SetPosition(Vector2f(163.f, 236.f));
	//myUpperLeftHouse->SetName("UpperLeftHouse");

	//myUpperLeftHouseFIRE = FactoryGameObject::CreateObject<Object>();
	//myUpperLeftHouseFIRE->LoadSprite("Sprites/Backgrounds/EndScene/upper_left_house_FIRE.dds");
	//myUpperLeftHouseFIRE->SetPivot(Vector2f(0.f, 0.f));
	//myUpperLeftHouseFIRE->SetPosition(Vector2f(163.f, 236.f));
	//myUpperLeftHouseFIRE->SetIsActive(false);

}

void TestEndState::Update(const float aDeltaTime)
{
	MouseInput::Update();
	CollisionManager::Update();
	LevelManager::Update(aDeltaTime);

	//ConvertToBoxShape(myUpperLeftHouse); 
	//ConvertToBoxShape(myBackground1);
	myBackground1->Update(aDeltaTime);

}

//void TestEndState::CheckEvent(Object* aObject)
//{
//	Event * tempEvent = new OnClickEvent();
//	OnClickEvent * tempClickOnEvent = new OnClickEvent(aObject, &MouseInput::GetInventoryPointer());
//
//	tempClickOnEvent->AddEvent(tempEvent);
//
//

//	aObject->SetEventCollider(tempEventCollider);
//}
void TestEndState::ConvertToBoxShape(Object* /*aObject*/)
{


	//
	//	//EventCollider * tempEventCollider = new EventCollider(tempBoxShape, tempClickOnEvent, aObject);
	//	aObject->SetEventCollider(tempEventCollider);


	//	//SAFE_DELETE(tempBoxShape);
}
void TestEndState::Draw() const
{
	myBackground1->BaseGameObject::Draw();
	MouseInput::Draw();
}

TestEndState::~TestEndState()
{

}
