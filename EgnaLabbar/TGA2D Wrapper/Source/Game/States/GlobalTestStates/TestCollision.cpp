#include "stdafx.h"
#include "TestCollision.h"
#include "../Game/Levels/LevelManager.h"
#include <input/MouseInput/MouseInput.h>
#include <InputWrapper/InputWrapper.h>
#include <Macros/Macros.h>




TestCollision::TestCollision()
{
	
}


TestCollision::~TestCollision()
{
}

void TestCollision::Init()
{	

}

void TestCollision::Update(float aDeltaTime)
{
	(aDeltaTime);
	LevelManager::Update(aDeltaTime);
	MouseInput::Update();
	//myBalanceLine.Update(aDeltaTime);

	CollisionManager::Update();

	/*if (CU::InputWrapper::GetKeyPressed(DIK_1))
	{
	myWeights[0].myImActive = !myWeights[0].myImActive;
	}

	if (CU::InputWrapper::GetKeyPressed(DIK_2))
	{
	myWeights[1].myImActive = !myWeights[1].myImActive;
	}

	if (CU::InputWrapper::GetKeyPressed(DIK_3))
	{
	myWeights[2].myImActive = !myWeights[2].myImActive;
	}

	if (CU::InputWrapper::GetKeyPressed(DIK_4))
	{
	myWeights[3].myImActive = !myWeights[3].myImActive;
	}

	if (CU::InputWrapper::GetKeyPressed(DIK_5))
	{
	myWeights[4].myImActive = !myWeights[4].myImActive;
	}

	if (CU::InputWrapper::GetKeyPressed(DIK_6))
	{
	myWeights[5].myImActive = !myWeights[5].myImActive;
	}*/

	
}

void TestCollision::Draw() const
{
	LevelManager::Draw();
	MouseInput::Draw();
	//myBalanceLine.Draw();
} 










//TestCollision::TestCollision()
//{
//	/*myTestBox1 = BoxShape(Vector2f(0.0f, -0.f), Vector2f(49.f, 2.f));
//	myTestBox2 = BoxShape(Vector2f(23.3f, 89.f), Vector2f(0.f, 4.f));
//	myTestBox3 = BoxShape(Vector2f(665.123f, 3.f), Vector2f(20.f, 4.f));
//	myTestBox4 = BoxShape(Vector2f(0.f, 0.f), Vector2f(2.f, 69.f));
//	myTestBox5 = BoxShape(Vector2f(10.3f, 47.f), Vector2f(47.f, 1.f));
//	myTestBox6 = BoxShape(Vector2f(20.3f, -2.f), Vector2f(2.f, 4.f));
//
//	myEvent = new ChangeLevelEvent(*new std::string("RandomName"), *new Player());
//	myEvent1.AddEvent(myEvent);
//
//	myEventTest1 = new EventCollider(&myTestBox1, &myEvent1);
//	myEventTest2 = new EventCollider(&myTestBox2, &myEvent2);
//	myEventTest3 = new EventCollider(&myTestBox3, &myEvent3);
//
//	myTriggerTest1 = new OnMouseClickTriggerCollider(myTestBox4);
//	myTriggerTest2 = new OnMouseClickTriggerCollider(myTestBox5);
//	myTriggerTest3 = new OnMouseClickTriggerCollider(myTestBox6);
//
//	CollisionManager::AddAEventCollider(*myEventTest1);
//	CollisionManager::AddAEventCollider(*myEventTest2);
//	CollisionManager::AddAEventCollider(*myEventTest3);*/
//
//	/*myCollisionManager.AddATriggerCollider(*myTriggerTest1);
//	myCollisionManager.AddATriggerCollider(*myTriggerTest2);
//	myCollisionManager.AddATriggerCollider(*myTriggerTest3);*/
//}
//
//
//TestCollision::~TestCollision()
//{
//}
//
//void TestCollision::Init()
//{
//	/*myTestObject.LoadSprite("Sprites/palm.dds");
//	myTestObject.SetPosition(Vector2f(400.f, 300.f));
//
//	myTestObject.Inut();
//
//	myTestMouse.LoadSprite("Sprites/redBush.png");
//	myTestMouse.SetPosition(Vector2f(1.f, 300.f));
//
//	testBox = Intersection2D::AABB2D(Vector2f(3.f, 2.5f), Vector2f(3.f, 2.f));*/
//}
//
//void TestCollision::Update(float aDeltaTime)
//{
//	//LevelManager::Update(aDeltaTime);
//
//	//myTestObject.CollisionReset();
//
//	//CollisionManager::Update();
//
//	//myTestObject.Update(aDeltaTime);
//	//myTestMouse.Update(aDeltaTime);
//
//	//testBox.SetPosition(myTestMouse.GetPosition());
//
//	//if (CU::InputWrapper::GetMouseButtonPressed(CU::enumMouseButtons::eRight))
//	//{
//	//	//CollisionManager::AddATriggerCollider(*myTriggerTest1);
//	//}
//
//	//MouseInput::Update();
//
//
//	/*if (Intersection2D::AABBVsAABB2D(myTestObject.GetCollisionBox(), testBox) == true)
//	{
//	myTestObject.Collided();
//	}*/
//}
//
//void TestCollision::Draw() const
//{
//	//LevelManager::Draw();
//	//myTestObject.Draw();
//	//MouseInput::Draw();
//	//myTestMouse.Draw();
//}