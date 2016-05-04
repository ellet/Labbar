#pragma once
#include "../BaseGameStructure/GameObjects/Voxel.h"
#include "../BaseGameStructure/GameObjects/Dot.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "../CommonUtilities/Matriser/matrix33.h"
#include "../CommonUtilities/Vectors/vector2.h"
#include "../BaseGameStructure/Rendering/WorldSpace.h"

class ShapeContainer
{
public:
	ShapeContainer();
	ShapeContainer(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath);
	~ShapeContainer();

	void SetPosition(Vector3<float> aPosition);

	Vector3<float> GetPosition();

	void AddChild(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void AddChild(ShapeContainer &aChild);

	void Init(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void RotateX(float aRadian);
	void RotateY(float aRadian);
	void RotateZ(float aRadian);

	void AddVoxel(const Voxel& aVoxel);

	void AddVoxels(const CommonUtilities::GrowingArray<Voxel, unsigned int > &someVoxels);

	void AddVoxels(const CommonUtilities::GrowingArray<Vector3f>& someVoxels, float aSize = 1.f);

	void ShapeContainer::AddVoxels(const CommonUtilities::GrowingArray<VoxelData, unsigned int> &someVoxels, float aSize = 1.f);

	const WorldSpace * GetMySpace();

private:

	CommonUtilities::GrowingArray<Voxel, unsigned int> myVoxels;

	//DotGameObject myCenter;

	WorldSpace myLocalSpace;

	float testRotation;
};