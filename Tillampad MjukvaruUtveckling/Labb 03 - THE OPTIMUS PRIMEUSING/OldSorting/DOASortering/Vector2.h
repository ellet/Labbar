#ifndef VECTOR2_H
#define VECTOR2_H
#include "Vector2decl.h"


template <typename Type> 
float Length(const Vector2<Type> &aType)
{
	float magn = static_cast<float>(sqrt( aType.myX*aType.myX + aType.myY*aType.myY ));
	return magn;
}

template <typename Type> 
float Length2(const Vector2<Type> &aType)
{
	return (Length(aType)*Length(aType));
}

template <typename Type> 
void Normalize(Vector2<Type> &aType)
{
	aType /= static_cast<Type>(sqrt( aType.myX*aType.myX + aType.myY*aType.myY ));
}

template <typename Type>
Type GetNormalized(const Type &aType)
{
	Type temp = aType;
	Normalize(temp);
	return temp;
}

template <typename Type>
Type Dot(Vector2<Type>& aTypeLeft, Vector2<Type>& aTypeRight)
{
	Type returnObj = 0;

	returnObj += (aTypeLeft.myX*aTypeRight.myX);
	returnObj += (aTypeLeft.myY*aTypeRight.myY);

	return returnObj;
}

//------Operators with other vectors-----------------------
template <typename Type>
Vector2<Type> operator+(const Vector2<Type>& aLeftArgument, const Vector2<Type> &aRightArgument)
{
	Vector2<Type> returnObj;
	returnObj.myX  = aLeftArgument.myX+ aRightArgument.myX;
	returnObj.myY  = aLeftArgument.myY+ aRightArgument.myY;
	return returnObj;	
}

template <typename Type>
void operator+=(Vector2<Type>& aLeftArgument, const Vector2<Type> &aRightArgument)
{
	aLeftArgument.myX = aRightArgument.myX + aLeftArgument.myX;
	aLeftArgument.myY = aRightArgument.myY + aLeftArgument.myY;
}

template <typename Type>
Vector2<Type> operator-(const Vector2<Type> &aLeftArgument, const Vector2<Type> &aRightArgument)
{
	Vector2<Type> returnObj = aRightArgument;
	returnObj.myX  = (aRightArgument.myX - aLeftArgument.myX)*-1;
	returnObj.myY  = (aRightArgument.myY - aLeftArgument.myY)*-1;
	return returnObj;	
}
template <typename Type>
void operator-=(Vector2<Type>& aLeftArgument, const Vector2<Type> &aRightArgument)
{
	aLeftArgument.myX  = aLeftArgument.myX - aRightArgument.myX;
	aLeftArgument.myY  = aLeftArgument.myY - aRightArgument.myY;
}

template <typename Type>
Vector2<Type> operator*(const Vector2<Type>& aLeftArgument, const Vector2<Type> &aRightArgument)
{
	Vector2<Type> returnObj = aRightArgument;
	returnObj.myX = returnObj.myX * aLeftArgument.myX;
	returnObj.myY = returnObj.myY * aLeftArgument.myY;

	return returnObj;
}
template <typename Type>
void operator*=(Vector2<Type> &aLeftArgument, const Vector2<Type> &aRightArgument)
{
	aLeftArgument.myX  = aRightArgument.myX * aLeftArgument.myX;
	aLeftArgument.myY  = aRightArgument.myY * aLeftArgument.myY;
}

template <typename Type>
Vector2<Type> operator/(const Vector2<Type> &aLeftArgument, const Vector2<Type> &aRightArgument)
{
	Vector2<Type> returnObj = aRightArgument;

	returnObj.myX = aLeftArgument.myX/aRightArgument.myX;
	returnObj.myY = aLeftArgument.myY/aRightArgument.myY;

	return returnObj;
}

template <typename Type>
void operator/=(Vector2<Type> &aLeftArgument, const Vector2<Type> &aRightArgument)
{
	aLeftArgument.myX  = aLeftArgument.myX / aRightArgument.myX;
	aLeftArgument.myY  = aLeftArgument.myY / aRightArgument.myY;
}
//---------Operators with scalars---------------------------
	
template <typename Type>
Vector2<Type> operator*(const Vector2<Type>& aLeftArgument, const Type aScalar)
{
	Vector2<Type> returnObj = aLeftArgument;
	returnObj.myX = returnObj.myX * aScalar;
	returnObj.myY = returnObj.myY * aScalar;
	return returnObj;
}

template <typename Type>
void operator*=(Vector2<Type>& aLeftArgument, const Type aScalar)
{
	aLeftArgument = aLeftArgument*aScalar;
}
template <typename Type>
Vector2<Type> operator/(const Vector2<Type> &aLeftArgument, const Type aScalar)
{
	Vector2<Type> returnObj = aLeftArgument;
	returnObj.myX = returnObj.myX / aScalar;
	returnObj.myY = returnObj.myY / aScalar;
	return returnObj;
}

template <typename Type>
void operator/=(Vector2<Type>& aLeftArgument, const Type aScalar)
{
	aLeftArgument = aLeftArgument / aScalar;
}

//------------Logicals-------------
template <typename Type>
bool operator==(const Vector2<Type>& aLeftArgument, const Vector2<Type> &aRightArgument)
{
	return ((aLeftArgument.myX == aRightArgument.myX) && (aLeftArgument.myY == aRightArgument.myY));
}


#endif