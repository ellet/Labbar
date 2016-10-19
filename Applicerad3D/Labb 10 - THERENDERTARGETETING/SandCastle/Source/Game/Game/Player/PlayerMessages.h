#pragma once

struct PlayerHealthChangedMessage
{
	PlayerHealthChangedMessage(float aValue)
	{
		aCurrentHealth = aValue;
	}
	float aCurrentHealth;
};

