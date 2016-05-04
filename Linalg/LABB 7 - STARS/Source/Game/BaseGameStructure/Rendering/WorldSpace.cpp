#include "stdafx.h"
#include "WorldSpace.h"


WorldSpace::WorldSpace()
{
	myParent = nullptr;
}


WorldSpace::~WorldSpace()
{
}

const WorldSpace * WorldSpace::GetParent() const
{
	return myParent;
}

void WorldSpace::SetParent(const WorldSpace * const aWorldSpace)
{
	myParent = aWorldSpace;
}

const Matrix44f & WorldSpace::GetSpaceData() const
{
	return myLocalWorldSpace;
}

void WorldSpace::SetSpaceData(const Matrix44f aMatrix)
{
	myLocalWorldSpace = aMatrix;
}

void WorldSpace::SetWorldPosition(const Vector3<float> aPosition)
{
	myLocalWorldSpace.SetPosition(aPosition);
}

Vector3<float> WorldSpace::GetWorldPosition()
{
	return myLocalWorldSpace.GetPosition();
}

void WorldSpace::SetWorldRotation(const float anAngle)
{
	//myLocalWorldSpace.Set2DRotation(anAngle);
}

void WorldSpace::RotateWorldSpace(const float anAngle)
{
	//myLocalWorldSpace.Rotate2D(anAngle);
}