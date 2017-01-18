#pragma once

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
		if (aRight.SpeedPercentage > SpeedPercentage)
		{
			SpeedPercentage = aRight.SpeedPercentage;
		}

		return *this;
	}

	SB::Vector2f Direction;
	float SpeedPercentage;
};
