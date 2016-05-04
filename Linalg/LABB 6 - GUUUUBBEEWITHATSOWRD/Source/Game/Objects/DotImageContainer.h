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
	DotImageContainer(Vector2<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath);
	~DotImageContainer();

	void SetPosition(Vector2<float> aPosition);

	Vector2<float> GetPosition();

	void AddChild(Vector2<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void AddChild(DotImageContainer &aChild);

	void Init(Vector2<float> aPosition, const WorldSpace * aWorldspace, const char * aFilePath = "sprites/DotFORGUBBEWITHHAT.png");

	void Rotate(float aRotation);

	CommonUtilities::GrowingArray<const DotImageContainer*> & GetMyChildren();

	const WorldSpace * GetMySpace();

private:

	CommonUtilities::GrowingArray<const DotImageContainer*> myChildren;

	DotGameObject myCenter;

	WorldSpace myLocalSpace;

	float testRotation;
};