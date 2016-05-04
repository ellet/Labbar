#pragma once

#include "../CommonUtilities/Vectors/Vector.h"
#include "tga2d\math\vector2.h"

//template<typename T>
//Vector2<T> operator DX2D::Vector2<T>(const DX2D::Vector2<T> aVector)
//{
//
//}



template<typename T>
Vector2<T> & operator<<(Vector2<T> & aLeftVector, const DX2D::Vector2<T> & aRightVector)
{
	aLeftVector.x = aRightVector.x;
	aLeftVector.y = aRightVector.y;

	return aLeftVector;
}

template<typename T>
DX2D::Vector2<T> & operator<<(DX2D::Vector2<T> & aLeftVector, const  Vector2<T> & aRightVector)
{
	aLeftVector.x = aRightVector.x;
	aLeftVector.y = aRightVector.y;

	return aLeftVector;
}