#pragma once

class Unit;

struct Steering
{
	Steering()
	{
		Direction = SB::Vector2f::Zero;
		SpeedPercentage = 0.f;
	}

	Steering &operator +=(const Steering &aRight)
	{
		Direction += aRight.Direction;
		SpeedPercentage += aRight.SpeedPercentage;

		if (SpeedPercentage > 1.f)
		{
			SpeedPercentage = 1.f;
		}

		return *this;
	}

	SB::Vector2f Direction;
	float SpeedPercentage;
};

class BaseBehaviour
{
public:
	BaseBehaviour(const Unit& aParentUnit);
	virtual ~BaseBehaviour();

	void SetWeight(const float aWeight);

	virtual Steering GetSteering(const SB::Time & aDeltaTime) = 0;

protected:
	const Unit * myParentUnit;
	float myWeight;
};

