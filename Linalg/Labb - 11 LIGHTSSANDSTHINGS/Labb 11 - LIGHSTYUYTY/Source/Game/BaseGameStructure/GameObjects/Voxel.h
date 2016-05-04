#pragma once
#include "../CommonUtilities/Vectors/Vector.h"
#include "../Game/BaseGameStructure/Rendering/WorldSpace.h"


class BaseGameObject;
struct VoxelData;

class Voxel
{
public:
	Voxel();
	~Voxel();

	void Init(Vector3<float> aPosition, 
		Vector3<float> aColour,
		Vector3<float> aNormal,
		float aSize = 1.f, 
		const WorldSpace * aWorldSpace = nullptr, 
		const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.dds");

	void Init(const VoxelData& aVoxel, float aSize = 1.f,
		const WorldSpace * aWorldSpace = nullptr,
		const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.dds");

	Vector3<float> GetPosition();

	void SetPosition(Vector3<float> aPosition);


private:
	BaseGameObject & GetMyBaseGameObject();
	size_t myBaseGameObjectIndex;
};