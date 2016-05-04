#include "stdafx.h"
#include "DotImageContainer.h"




DotImageContainer::DotImageContainer()
{
}

DotImageContainer::DotImageContainer(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	Init(aPosition, aWorldspace, aFilePath);
}

void DotImageContainer::Init(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	myChildren.Init(50);
	myLocalSpace.SetWorldPosition(aPosition);
	myLocalSpace.SetParent(aWorldspace);
	testRotation = 0;
	myCenter.Init(Vector3<float>(0.f, 0.f, 1.f), &myLocalSpace, aFilePath);


}

DotImageContainer::~DotImageContainer()
{
}


void DotImageContainer::SetPosition(Vector3<float> aPosition)
{
	myLocalSpace.SetWorldPosition(aPosition);
	myCenter.SetPosition(aPosition);
}

Vector3<float> DotImageContainer::GetPosition()
{
	return myCenter.GetPosition();
}

void DotImageContainer::AddChild(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
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

CommonUtilities::GrowingArray<const DotImageContainer*, unsigned int> & DotImageContainer::GetMyChildren()
{
	return myChildren;
}

const WorldSpace * DotImageContainer::GetMySpace()
{
	return &myLocalSpace;
}