#include "stdafx.h"
#include "ShapeContainer.h"




ShapeContainer::ShapeContainer()
{
}

ShapeContainer::ShapeContainer(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	Init(aPosition, aWorldspace, aFilePath);
}

void ShapeContainer::Init(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath)
{
	myVoxels.Init(50);
	myLocalSpace.SetWorldPosition(aPosition);
	myLocalSpace.SetParent(aWorldspace);
	//myCenter.Init(Vector3<float>(0.f, 0.f, 0.f), &myLocalSpace, aFilePath);
}

ShapeContainer::~ShapeContainer()
{
}


void ShapeContainer::SetPosition(Vector3<float> aPosition)
{
	myLocalSpace.SetWorldPosition(aPosition);
	//myCenter.SetPosition(aPosition);
}

Vector3<float> ShapeContainer::GetPosition()
{
	return myLocalSpace.GetWorldPosition();
}

void ShapeContainer::RotateX(float aRadian)
{
	myLocalSpace.RotateX(aRadian);
}

void ShapeContainer::RotateY(float aRadian)
{
	myLocalSpace.RotateY(aRadian);
}

void ShapeContainer::RotateZ(float aRadian)
{
	myLocalSpace.RotateZ(aRadian);
}

const WorldSpace * ShapeContainer::GetMySpace()
{
	return &myLocalSpace;
}

void ShapeContainer::AddVoxel(const Voxel& aVoxel)
{
	myVoxels.Add(aVoxel);
}

void ShapeContainer::AddVoxels(const CommonUtilities::GrowingArray<Voxel>& someVoxels)
{
	myVoxels = someVoxels;
}

void ShapeContainer::AddVoxels(const CommonUtilities::GrowingArray<Vector3f>& someVoxels, float aSize)
{
	Vector3f offset(0.5f, 0.5f, 0.5f);
	for (unsigned int i = 0; i < someVoxels.Size(); ++i)
	{
		Voxel temp;
		temp.Init((someVoxels[i]), aSize, GetMySpace());
		myVoxels.Add(temp);
	}
}