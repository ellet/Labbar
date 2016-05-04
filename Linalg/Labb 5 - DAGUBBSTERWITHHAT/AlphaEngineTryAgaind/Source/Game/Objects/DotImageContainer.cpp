#include "stdafx.h"
#include "DotImageContainer.h"




DotImageContainer::DotImageContainer()
{
	myDots.Init(50);
	myLocalSpace.SetWorldPosition(Vector2<float>(0.5f, 0.5f));
	testRotation = 0;
}


DotImageContainer::~DotImageContainer()
{
}

void DotImageContainer::AddDot(Vector2<float> aPosition)
{
	myDots.Add(DotGameObject());
	myDots.GetLast().Init(aPosition, &myLocalSpace);
}

void DotImageContainer::Rotate(float aRotation)
{
	myLocalSpace.RotateWorldSpace(aRotation);

	//testRotation += aRotation;
	//myLocalSpace.SetWorldRotation(testRotation);
}

CommonUtilities::GrowingArray<DotGameObject> & DotImageContainer::GetMyDots()
{
	return myDots;
}