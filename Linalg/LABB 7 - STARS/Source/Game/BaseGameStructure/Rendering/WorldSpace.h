#pragma once
#include "../CommonUtilities/Matriser/matrix44.h"

template <typename T>
class Vector2;

class WorldSpace
{
public:
	WorldSpace();
	~WorldSpace();

	void SetParent(const WorldSpace * const aWorldSpace);

	const WorldSpace * GetParent() const;

	const Matrix44f & GetSpaceData() const;

	void SetSpaceData(const Matrix44f aMatrix);

	void SetWorldPosition(const Vector3<float> aPosition);

	void RotateWorldSpace(const float anAngle);

	void SetWorldRotation(const float anAngle);
	
	Vector3<float> GetWorldPosition();

private:
	Matrix44f myLocalWorldSpace;

	const WorldSpace * myParent;
};

