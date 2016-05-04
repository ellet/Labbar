#include "stdafx.h"
#include "ShapeContainer.h"
#include "../BaseGameStructure/GameObjectsManager.h"
#include <Intersection/Intersections3D.h>


ShapeContainer::ShapeContainer()
{
	myRadius = 0.f;
	ourNumberOfObjectsThatShouldRender = 0;
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


void ShapeContainer::Update()
{
	Vector3f temp = myLocalSpace.GetWorldPosition();

	const WorldSpace * tempParent = myLocalSpace.GetParent();

	while (tempParent != nullptr)
	{
		temp = temp * tempParent->GetSpaceData();
		tempParent = tempParent->GetParent();
	}

	temp = temp * GameObjectsManager::GetCameraInverse();

	if (Intersection3D::SphereVsFrustum(Intersection3D::Sphere(temp, myRadius), GameObjectsManager::GetCameraFrustum()) == true)
	{
		++ourNumberOfObjectsThatShouldRender;
		for (unsigned int iVoxel = 0; iVoxel < myVoxels.Size(); ++iVoxel)
		{
			myVoxels[iVoxel].VoxelShouldRender();
		}
	}
}

void ShapeContainer::SetPosition(Vector3<float> aPosition)
{
	myLocalSpace.SetWorldPosition(aPosition);
	//myCenter.SetPosition(aPosition);
}

void ShapeContainer::SetParent(const WorldSpace * aParentWorldSpace)
{
	myLocalSpace.SetParent(aParentWorldSpace);
}

const WorldSpace * ShapeContainer::GetWorldSpace()
{
	return &myLocalSpace;
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

int ShapeContainer::ourNumberOfObjectsThatShouldRender;

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
		float distanceFromCenter = (myLocalSpace.GetWorldPosition() - temp.GetPosition()).Length();

		if (distanceFromCenter > myRadius)
		{
			myRadius = distanceFromCenter;
		}

		myVoxels.Add(temp);
	}
}