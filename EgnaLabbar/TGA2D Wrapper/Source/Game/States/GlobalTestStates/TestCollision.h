#pragma once

#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseGameObject\BaseAnimatedObject\BaseAnimatedGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>

#include <CollisionManager/CollisionManager.h>
#include <CollisionManager/TriggerColliders/OnMouseClickTriggerCollider.h>
#include <CollisionManager/EventCollider.h>

#include <Intersection/Intersection2D.h>

#include "../../Object/TestCollisionObject.h"
#include "../../Object/TestMouseInput.h"

#include <CollisionManager/CollisionShapes/BoxShape.h>

#include "../Game/EventManager/Events/OnClickEvent.h"
#include "../Game/EventManager/Events/ChangeLevelEvent.h"

#include "../../Object/BalanceLine.h"

#include "../Game/Player/Player.h"
#include <GrowingArray/GrowingArray.h>




class TestCollision : public BaseState
{
public:
	TestCollision();
	~TestCollision();

	void Init();

	void Update(const float aDeltaTime) override final;

	void Draw() const;



private:
	//BalanceLine myBalanceLine;

	
};




//#include <BaseClasses\BaseGameObject\BaseGameObject.h>
//#include <BaseClasses\BaseGameObject\BaseAnimatedObject\BaseAnimatedGameObject.h>
//#include <BaseClasses\BaseState\BaseState.h>
//
//#include <CollisionManager/CollisionManager.h>
//#include <CollisionManager/TriggerColliders/OnMouseClickTriggerCollider.h>
//#include <CollisionManager/EventCollider.h>
//
//#include <Intersection/Intersection2D.h>
//
//#include "../../Object/TestCollisionObject.h"
//#include "../../Object/TestMouseInput.h"
//
//#include <CollisionManager/CollisionShapes/BoxShape.h>
//
//#include "../Game/EventManager/Events/OnClickEvent.h"
//#include "../Game/EventManager/Events/ChangeLevelEvent.h"
//
//#include "../Game/Player/Player.h"
//#include 


//class TestCollision : public BaseState
//{
//public:
//	TestCollision();
//	~TestCollision();
//
//	void Init();
//
//	void Update(const float aDeltaTime) override final;
//
//	void Draw() const;
//
//private:
//	TestCollisionObject myTestObject;
//	TestMouseInput myTestMouse;
//	Intersection2D::AABB2D testBox;
//
//	//Player myPlayer
//	ChangeLevelEvent * myEvent;
//
//	OnClickEvent myEvent1;
//	OnClickEvent myEvent2;
//	OnClickEvent myEvent3;
//
//	BoxShape myTestBox1;
//	BoxShape myTestBox2;
//	BoxShape myTestBox3;
//
//	BoxShape myTestBox4;
//	BoxShape myTestBox5;
//	BoxShape myTestBox6;
//
//	BaseTriggerCollider * myTriggerTest1;
//	BaseTriggerCollider * myTriggerTest2;
//	BaseTriggerCollider * myTriggerTest3;
//
//	EventCollider * myEventTest1;
//	EventCollider * myEventTest2;
//	EventCollider * myEventTest3;
//};
//
