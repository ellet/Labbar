#pragma once
#include "../CommonUtilities/Matriser/matrix33.h"

template <typename T>
class Vector2;

class WorldSpace
{
public:
	WorldSpace();
	~WorldSpace();

	void SetParent(WorldSpace * const aWorldSpace);

	WorldSpace * GetParent();

	const Matrix33f & GetSpaceData();

	void SetSpaceData(const Matrix33f aMatrix);

	void SetWorldPosition(const Vector2<float> aPosition);

	void RotateWorldSpace(const float anAngle);

	void SetWorldRotation(const float anAngle);
	
	Vector2<float> GetWorldPosition();

private:
	Matrix33f myLocalWorldSpace;

	WorldSpace * myParent;
};

