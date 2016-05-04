#pragma once
#include "../BaseGameStructure/GameObjects/Dot.h"
#include "../CommonUtilities/GrowingArray/GrowingArray.h"
#include "../CommonUtilities/Matriser/matrix33.h"
#include "../CommonUtilities/Vectors/vector2.h"
#include "../BaseGameStructure/Rendering/WorldSpace.h"

class DotImageContainer
{
public:
	DotImageContainer();
	DotImageContainer(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath);
	~DotImageContainer();

	void SetPosition(Vector3<float> aPosition);

	Vector3<float> GetPosition();

	void AddChild(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void AddChild(DotImageContainer &aChild);

	void Init(Vector3<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void Rotate(float aRotation);

	CommonUtilities::GrowingArray<const DotImageContainer*, unsigned int> & GetMyChildren();

	const WorldSpace * GetMySpace();

private:

	CommonUtilities::GrowingArray<const DotImageContainer*, unsigned int> myChildren;

	DotGameObject myCenter;

	WorldSpace myLocalSpace;

	float testRotation;
};