#pragma once

#include <tga2d\math\vector2.h>
#include <Vectors\vector2.h>

template<typename T>
Vector2<T>& operator <<(Vector2<T> &aLeft, const DX2D::Vector2<T> &aRight)
{
	aLeft.x = aRight.x;
	aLeft.y = aRight.y;
	return aLeft;
}

template<typename T>
DX2D::Vector2<T>& operator <<(DX2D::Vector2<T> &aLeft, const Vector2<T> &aRight)
{
	aLeft.x = aRight.x;
	aLeft.y = aRight.y;
	return aLeft;
}
