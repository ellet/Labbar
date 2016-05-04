#pragma once
#include "../CommonUtilities/Vectors/Vector.h"
#include "../Game/BaseGameStructure/Rendering/WorldSpace.h"


class BaseGameObject;

class Voxel
{
public:
	Voxel();
	~Voxel();

	void Init(Vector3<float> aPosition, float aSize = 1.f, const WorldSpace * aWorldSpace = nullptr, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	Vector3<float> GetPosition();

	void SetPosition(Vector3<float> aPosition);

	void VoxelShouldRender();

private:
	BaseGameObject & GetMyBaseGameObject();
	size_t myBaseGameObjectIndex;
};