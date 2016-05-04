#include "stdafx.h"
#include "TestGameState.h"

#include <BaseClasses\FactoryGameObject\FactoryGameObject.h>

TestGameState::TestGameState()
{

	SetActiveDraw(true);
	SetActiveUpdate(true);

	myBaseGameObject = FactoryGameObject::CreateObject<BaseGameObject>();

	myBaseGameObject->LoadSprite("Sprites/car_1.dds");
	myBaseGameObject->SetPosition(Vector2f(.5f, .5f));
	myBaseGameObject->SetSize(Vector2f(2.f, 2.f));
	myBaseGameObject->SetPivot(Vector2f(.5f, .5f));
	myBaseGameObject->SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));
	myBaseGameObject->SetRotation(0.f);

	//myBaseAnimationGameObject = FactoryGameObject::CreateObject<BaseAnimatedGameObject>();

	//myBaseAnimationGameObject->LoadSprite("Sprites/car_1.dds");
	//myBaseAnimationGameObject->SetPosition(Vector2f(.2f, .8f));
	//myBaseAnimationGameObject->SetSize(Vector2f(2.f, 2.f));
	//myBaseAnimationGameObject->SetPivot(Vector2f(.5f, .5f));
	//myBaseAnimationGameObject->SetColor(Vector4f(1.f, 1.f, 1.f, 1.f));
	//myBaseAnimationGameObject->SetRotation(0.f);
	
	//myBaseAnimationGameObject->SetColumns(2);
	//myBaseAnimationGameObject->SetRows(2);

	//myBaseAnimationGameObject->AddAnimation(Animation(0, 4, 0.25f));

}
TestGameState::~TestGameState()
{
}

void TestGameState::Update(const float aDeltaTime)
{
	
	(aDeltaTime);

	//myBaseAnimationGameObject->Update(aDeltaTime);

}
void TestGameState::Draw() const
{

	myBaseGameObject->Draw();
	//myBaseAnimationGameObject->Draw();

}
