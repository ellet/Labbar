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
	~DotImageContainer();

	void AddDot(Vector2<float> aPosition);

	void Rotate(float aRotation);

	CommonUtilities::GrowingArray<DotGameObject> & GetMyDots();

private:

	CommonUtilities::GrowingArray<DotGameObject> myDots;

	WorldSpace myLocalSpace;

	float testRotation;
};