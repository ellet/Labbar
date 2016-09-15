#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector3decl.h"

template <typename Type>
float Length(const Vector3<Type> &aType)
{
	float magn = static_cast<float>(aType.myX*aType.myX + aType.myY*aType.myY + aType.myZ*aType.myZ);
	return magn;
}

template <typename Type>
float Length2(const Vector3<Type> &aType)
{
	return (Length(aType)*Length(aType));
}

template <typename Type>
void Normalize(Vector3<Type> &aType)
{
	aType /= static_cast<Type>(sqrt( aType.myX*aType.myX + aType.myY*aType.myY + aType.myZ*aType.myZ));
}

template <typename Type>
Vector3<Type> Cross(const Vector3<Type> &aLeftArgument, const Vector3<Type> &aRightArgument)
{
	Vector3<Type> returnObj;
	returnObj.myX =	(aLeftArgument.myY*aRightArgument.myZ) - (aLeftArgument.myZ*aRightArgument.myY);
	returnObj.myY = (aLeftArgument.myZ*aRightArgument.myX) - (aLeftArgument.myX*aRightArgument.myZ);
	returnObj.myZ = (aLeftArgument.myX*aRightArgument.myY) - (aLeftArgument.myY*aRightArgument.myX);

	return returnObj;
}

template <typename Type>
Type Dot(Vector3<Type>& aTypeLeft, Vector3<Type>& aTypeRight)
{
	Type returnObj = 0;
	returnObj += (aTypeLeft.myX*aTypeRight.myX);
	returnObj += (aTypeLeft.myY*aTypeRight.myY);
	returnObj += (aTypeLeft.myZ*aTypeRight.myZ);
	return returnObj;
}

//With other vectors-------------------------------------------
template <typename Type>
Vector3<Type> operator+(const Vector3<Type>& aLeftArgument, const Vector3<Type> &aRightArgument)
{
	Vector3<Type> returnObj;
	returnObj.myX  = aLeftArgument.myX+ aRightArgument.myX;
	returnObj.myY  = aLeftArgument.myY+ aRightArgument.myY;
	returnObj.myZ  = aLeftArgument.myZ+ aRightArgument.myZ;
	return returnObj;
}

template <typename Type>
void operator+=(Vector3<Type>& aLeftArgument, const Vector3<Type> &aRightArgument)
{
	aLeftArgument.myX = aRightArgument.myX + aLeftArgument.myX;
	aLeftArgument.myY = aRightArgument.myY + aLeftArgument.myY;
	aLeftArgument.myZ = aRightArgument.myZ + aLeftArgument.myZ;
}

template <typename Type>
Vector3<Type> operator-(const Vector3<Type> &aLeftArgument, const Vector3<Type> &aRightArgument)
{
	Vector3<Type> returnObj = aRightArgument;
	returnObj.myX  = (aRightArgument.myX - aLeftArgument.myX)*-1;
	returnObj.myY  = (aRightArgument.myY - aLeftArgument.myY)*-1;
	returnObj.myZ  = (aRightArgument.myZ - aLeftArgument.myZ)*-1;
	return returnObj;	
}
template <typename Type>
void operator-=(Vector3<Type>& aLeftArgument, const Vector3<Type> &aRightArgument)
{
	aLeftArgument.myX  = aLeftArgument.myX - aRightArgument.myX;
	aLeftArgument.myY  = aLeftArgument.myY - aRightArgument.myY;
	aLeftArgument.myZ  = aLeftArgument.myZ - aRightArgument.myZ;

}

template <typename Type>
Vector3<Type> operator*(const Vector3<Type>& aLeftArgument, const Vector3<Type> &aRightArgument)
{
	Vector3<Type> returnObj = aRightArgument;
	returnObj.myX = returnObj.myX * aLeftArgument.myX;
	returnObj.myY = returnObj.myY * aLeftArgument.myY;
	returnObj.myZ = returnObj.myZ * aLeftArgument.myZ;
	return returnObj;
}

template <typename Type>
void operator*=(Vector3<Type> &aLeftArgument, const Vector3<Type> &aRightArgument)
{
	aLeftArgument.myX  = aRightArgument.myX * aLeftArgument.myX;
	aLeftArgument.myY  = aRightArgument.myY * aLeftArgument.myY;
	aLeftArgument.myZ  = aRightArgument.myZ * aLeftArgument.myZ;

}

template <typename Type>
Vector3<Type> operator/(const Vector3<Type> &aLeftArgument, const Vector3<Type> &aRightArgument)
{
	Vector3<Type> returnObj = aRightArgument;

	returnObj.myX = aLeftArgument.myX/aRightArgument.myX;
	returnObj.myY = aLeftArgument.myY/aRightArgument.myY;
	returnObj.myZ = aLeftArgument.myZ/aRightArgument.myZ;

	return returnObj;
}

template <typename Type>
void operator/=(Vector3<Type> &aLeftArgument, const Vector3<Type> &aRightArgument)
{
	aLeftArgument.myX  = aLeftArgument.myX / aRightArgument.myX;
	aLeftArgument.myY  = aLeftArgument.myY / aRightArgument.myY;
	aLeftArgument.myZ  = aLeftArgument.myZ / aRightArgument.myZ;
}

//With scalars---------------------------------------------------
template <typename Type>
Vector3<Type> operator*(const Vector3<Type>& aLeftArgument, const Type aScalar)
{
	Vector3<Type> returnObj = aLeftArgument;
	returnObj.myX = returnObj.myX * aScalar;
	returnObj.myY = returnObj.myY * aScalar;
	returnObj.myZ = returnObj.myZ * aScalar;

	return returnObj;
}

template <typename Type>
void operator*=(Vector3<Type>& aLeftArgument, const Type aScalar)
{
	aLeftArgument = aLeftArgument * aScalar;
}

template <typename Type>
Vector3<Type> operator/(const Vector3<Type> &aLeftArgument, const Type aScalar)
{
	Vector3<Type> returnObj = aLeftArgument;
	returnObj.myX = returnObj.myX / aScalar;
	returnObj.myY = returnObj.myY / aScalar;
	returnObj.myZ = returnObj.myZ / aScalar;

	return returnObj;
}

template <typename Type>
void operator/=( Vector3<Type>& aLeftArgument, const Type aScalar)
{
	aLeftArgument = aLeftArgument / aScalar;
}
#endif VECTOR3_H