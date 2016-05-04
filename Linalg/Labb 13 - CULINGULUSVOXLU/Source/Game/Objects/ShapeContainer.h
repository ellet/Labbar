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

	void Update();

	void SetPosition(Vector3<float> aPosition);
	
	void SetParent(const WorldSpace * aParentWorldSpace);
	const WorldSpace * GetWorldSpace();

	Vector3<float> GetPosition();

	void AddChild(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void AddChild(ShapeContainer &aChild);

	void Init(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void RotateX(float aRadian);
	void RotateY(float aRadian);
	void RotateZ(float aRadian);

	void AddVoxel(const Voxel& aVoxel);

	void AddVoxels(const CommonUtilities::GrowingArray<Voxel>& someVoxels);

	void AddVoxels(const CommonUtilities::GrowingArray<Vector3f>& someVoxels, float aSize = 1.f);

	const WorldSpace * GetMySpace();

	static int ourNumberOfObjectsThatShouldRender;

private:

	CommonUtilities::GrowingArray<Voxel> myVoxels;

	float myRadius;

	//DotGameObject myCenter;

	WorldSpace myLocalSpace;

	float testRotation;
};