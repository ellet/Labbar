#include "stdafx.h"
#include "RandomRotationComponent.h"
#include <Utilities\Randomizer\Randomizer.h>

namespace SB
{
	unsigned short RandomRotationComponent::myRandomSeed = 0;

	RandomRotationComponent::RandomRotationComponent()
	{
		myRandomValue = 5.f;
	}

	RandomRotationComponent::~RandomRotationComponent()
	{
	}

	void RandomRotationComponent::Update(const Time & aDeltaTime)
	{
		myObject->GetRotation().RotateAroundLocalX(myRotationDelta.x * aDeltaTime.InSeconds());
		myObject->GetRotation().RotateAroundLocalY(myRotationDelta.y * aDeltaTime.InSeconds());
		myObject->GetRotation().RotateAroundLocalZ(myRotationDelta.z * aDeltaTime.InSeconds());
	}

	void RandomRotationComponent::Initialize()
	{
		Randomizer random;
		myRandomSeed++;
		random.SetSeed(myRandomSeed);
		random.SetMinMax(DEGREES_TO_RADIANSF(-myRandomValue), DEGREES_TO_RADIANSF(myRandomValue));

		myRotationDelta.x = random.GetRandomValue();
		myRotationDelta.y = random.GetRandomValue();
		myRotationDelta.z = random.GetRandomValue();
	}

	void RandomRotationComponent::ToJson(JsonSerializer &aSerializer) const
	{
		SB::JsonSerializer& serializer = aSerializer;
		serializer.WriteObject("properties");

		serializer.WriteNode("rotationRange", myRandomValue);

		serializer.StepOut();
		serializer.WriteNode("type", "RandomRotationComponent");
	}

	void RandomRotationComponent::LoadData(DataNode aProperties)
	{
		myRandomValue = aProperties["rotationRange"].GetFloat();
	}

	void RandomRotationComponent::LoadData(float aRandomValue)
	{
		myRandomValue = aRandomValue;
	}
}
