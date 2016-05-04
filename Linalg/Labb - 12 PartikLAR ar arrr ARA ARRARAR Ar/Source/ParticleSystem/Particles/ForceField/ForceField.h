#pragma once
#include <Vectors/vector3.h>

struct ForceField
{
	inline ForceField();

	float myRadius;
	float myStrength;
	
	Vector3f myPosition;

};

ForceField::ForceField()
{
	myRadius = 0.f;
	myStrength = 0.f;
	myPosition = Vector3f::Zero;
}

