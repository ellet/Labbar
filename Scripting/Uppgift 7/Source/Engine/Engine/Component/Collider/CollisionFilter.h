#pragma once

enum class CollisionFilter
{
	ePlayer				= 1 << 0,
	eEnemy				= 1 << 1,
	eEnvironment		= 1 << 2,
	eEnemyProjectile	= 1 << 3,
	eEnemySwarmer		= 1 << 4,
	eDefault			= 1 << 5,
	eShield				= 1 << 6
};

inline unsigned int operator|(unsigned int aLeft, CollisionFilter aRight)
{
	return  aLeft | static_cast<int>(aRight);
}

inline unsigned int operator|(CollisionFilter aLeft, CollisionFilter aRight)
{
	return  static_cast<int>(aLeft) | static_cast<int>(aRight);
}