#include "stdafx.h"
#include "WorldSpace.h"


WorldSpace::WorldSpace()
{
	myParent = nullptr;
}


WorldSpace::~WorldSpace()
{
}

WorldSpace * WorldSpace::GetParent()
{
	return myParent;
}

void WorldSpace::SetParent(WorldSpace * const aWorldSpace)
{
	myParent = aWorldSpace;
}

const Matrix33f & WorldSpace::GetSpaceData()
{
	return myLocalWorldSpace;
}

void WorldSpace::SetSpaceData(const Matrix33f aMatrix)
{
	myLocalWorldSpace = aMatrix;
}

void WorldSpace::SetWorldPosition(const Vector2<float> aPosition)
{
	myLocalWorldSpace.SetPosition(aPosition);
}

Vector2<float> WorldSpace::GetWorldPosition()
{
	return myLocalWorldSpace.GetPosition();
}

void WorldSpace::SetWorldRotation(const float anAngle)
{
	myLocalWorldSpace.Set2DRotation(anAngle);
}

void WorldSpace::RotateWorldSpace(const float anAngle)
{
	myLocalWorldSpace.Rotate2D(anAngle);
}