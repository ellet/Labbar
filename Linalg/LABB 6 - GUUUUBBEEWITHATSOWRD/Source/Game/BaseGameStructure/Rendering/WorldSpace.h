#pragma once
#include "../CommonUtilities/Matriser/matrix33.h"

template <typename T>
class Vector2;

class WorldSpace
{
public:
	WorldSpace();
	~WorldSpace();

	void SetParent(const WorldSpace * const aWorldSpace);

	const WorldSpace * GetParent() const;

	const Matrix33f & GetSpaceData() const;

	void SetSpaceData(const Matrix33f aMatrix);

	void SetWorldPosition(const Vector2<float> aPosition);

	void RotateWorldSpace(const float anAngle);

	void SetWorldRotation(const float anAngle);
	
	Vector2<float> GetWorldPosition();

private:
	Matrix33f myLocalWorldSpace;

	const WorldSpace * myParent;
};

