#include "stdafx.h"
#include "TestMouseInteract.h"


TestMouseInteract::TestMouseInteract()
{
}


TestMouseInteract::~TestMouseInteract()
{
}

void TestMouseInteract::Init()
{
	myTestObject.LoadSprite("Sprites/palm.dds");
	myTestObject.SetPosition(Vector2f(0.5f, 0.5f));

}

void TestMouseInteract::Update(float aDeltaTime)
{
	

	myTestObject.Update(aDeltaTime);
}

void TestMouseInteract::Draw() const
{
	myTestObject.Draw();
}