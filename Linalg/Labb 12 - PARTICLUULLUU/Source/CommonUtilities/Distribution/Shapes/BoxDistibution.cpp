#include "BoxDistibution.h"


BoxDistibution::BoxDistibution()
{
}


BoxDistibution::~BoxDistibution()
{
}

void BoxDistibution::SetBox(const Vector3f aPosition, const Vector3f aExtents)
{
	myBoxShape.myCenterPos = aPosition;
	myBoxShape.myExtents = aExtents;

	myBoxShape.myMaxPos = aPosition + aExtents;
	myBoxShape.myMinPos = aPosition - aExtents;
}

void BoxDistibution::SetBoxWithMinMax(const Vector3f aMinValue, const Vector3f aMaxValue)
{
	myBoxShape.myMaxPos = aMaxValue;
	myBoxShape.myMinPos = aMinValue;

	myBoxShape.myExtents = (aMaxValue - aMinValue) / 2;
	myBoxShape.myCenterPos = aMinValue + myBoxShape.myExtents;
}

Vector3f BoxDistibution::GetPositionInDistribution()
{
	const float X = myRandomizer.GetRandomValue(myBoxShape.myMinPos.x, myBoxShape.myMaxPos.x);
	const float Y = myRandomizer.GetRandomValue(myBoxShape.myMinPos.y, myBoxShape.myMaxPos.y);
	const float Z = myRandomizer.GetRandomValue(myBoxShape.myMinPos.z, myBoxShape.myMaxPos.z);

	return Vector3f(X,Y,Z);
}
