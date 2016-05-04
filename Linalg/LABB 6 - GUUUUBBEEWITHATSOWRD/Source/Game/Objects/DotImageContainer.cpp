#include "stdafx.h"
#include "DotImageContainer.h"




DotImageContainer::DotImageContainer()
{
}

DotImageContainer::DotImageContainer(Vector2<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	Init(aPosition, aWorldspace, aFilePath);
}

void DotImageContainer::Init(Vector2<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	myChildren.Init(50);
	myLocalSpace.SetWorldPosition(aPosition);
	myLocalSpace.SetParent(aWorldspace);
	testRotation = 0;
	myCenter.Init(Vector2<float>(0.f, 0.f), &myLocalSpace, aFilePath);


}

DotImageContainer::~DotImageContainer()
{
}


void DotImageContainer::SetPosition(Vector2<float> aPosition)
{
	myLocalSpace.SetWorldPosition(aPosition);
	myCenter.SetPosition(aPosition);
}

Vector2<float> DotImageContainer::GetPosition()
{
	return myCenter.GetPosition();
}

void DotImageContainer::AddChild(Vector2<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	myChildren.Add(new DotImageContainer(aPosition, aWorldspace, aFilePath));
}

void DotImageContainer::AddChild(DotImageContainer &aChild)
{
	myChildren.Add(&aChild);
}

void DotImageContainer::Rotate(float aRotation)
{
	myLocalSpace.RotateWorldSpace(aRotation);

	//testRotation += aRotation;
	//myLocalSpace.SetWorldRotation(testRotation);
}

CommonUtilities::GrowingArray<const DotImageContainer*> & DotImageContainer::GetMyChildren()
{
	return myChildren;
}

const WorldSpace * DotImageContainer::GetMySpace()
{
	return &myLocalSpace;
}