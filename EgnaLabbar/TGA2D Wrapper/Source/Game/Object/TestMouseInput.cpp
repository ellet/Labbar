#include "stdafx.h"
#include "TestMouseInput.h"
#include <tga2d\engine.h>
#include <InputWrapper\InputWrapper.h>
#include <Utility/MouseInputResolutionAdaption.h>
#include <CollisionManager/CollisionManager.h>

TestMouseInput::TestMouseInput()
{
	myTriggerCollider = new OnMouseClickTriggerCollider(myPointShape);
}


TestMouseInput::~TestMouseInput()
{
}

void TestMouseInput::Inut()
{
}

void TestMouseInput::Update(const float aDeltaTime)
{
	(aDeltaTime);
	Vector2f testPosition = MouseFix::GetFixedMousePosition();

	

	if (CU::InputWrapper::GetMouseButtonPressed(CU::enumMouseButtons::eRight) == true)
	{
		myPointShape = PointShape(testPosition);
		myTriggerCollider->SetCollisionShape(myPointShape);

		//CollisionManager::AddATriggerCollider(*myTriggerCollider);
	}

	SetPosition(testPosition);
}