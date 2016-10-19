#pragma once

enum class CollisionFilter
{
	ePlayer			= 1 << 0,
	eEnemy			= 1 << 1,
	eEnviorment		= 1 << 2,
	eDefault		= 1 << 3
};

inline unsigned int operator|(unsigned int aLeft, CollisionFilter aRight)
{
	return  aLeft | static_cast<int>(aRight);
}

inline unsigned int operator|(CollisionFilter aLeft, CollisionFilter aRight)
{
	return  static_cast<int>(aLeft) | static_cast<int>(aRight);
}