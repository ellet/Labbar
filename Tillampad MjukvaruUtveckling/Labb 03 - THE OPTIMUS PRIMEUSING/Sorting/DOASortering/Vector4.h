#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector4decl.h"

template <typename Type>
float Length(const Vector4<Type> &aType)
{
	float magn = static_cast<float>(aType.myX*aType.myX + aType.myY*aType.myY + aType.myZ*aType.myZ + aType.myW*aType.myW);
	return magn;
}

template <typename Type>
float Length2(const Vector4<Type> &aType)
{
	return (Length(aType)*Length(aType));
}

template <typename Type>
void Normalize(Vector4<Type> &aType)
{
	aType /= static_cast<Type>(sqrt( aType.myX*aType.myX + aType.myY*aType.myY + aType.myZ*aType.myZ + aType.myW*aType.myW));
}

template <typename Type>
Type Dot(Vector4<Type>& aTypeLeft, Vector4<Type>& aTypeRight)
{
	Type returnObj = 0;

	returnObj +=(aTypeLeft.myX*aTypeRight.myX);
	returnObj +=(aTypeLeft.myY*aTypeRight.myY);
	returnObj +=(aTypeLeft.myZ*aTypeRight.myZ);
	returnObj +=(aTypeLeft.myW*aTypeRight.myW);

	return returnObj;
}


//With other vectors----------------------------------------------
template <typename Type>
Vector4<Type> operator+(const Vector4<Type>& aLeftArgument, const Vector4<Type> &aRightArgument)
{
	Vector4<Type> returnObj;
	returnObj.myX  = aLeftArgument.myX+ aRightArgument.myX;
	returnObj.myY  = aLeftArgument.myY+ aRightArgument.myY;
	returnObj.myZ  = aLeftArgument.myZ+ aRightArgument.myZ;
	returnObj.myW  = aLeftArgument.myW+ aRightArgument.myW;

	return returnObj;
}

template <typename Type>
void operator+=(Vector4<Type>& aLeftArgument, const Vector4<Type> &aRightArgument)
{
	aLeftArgument.myX = aRightArgument.myX + aLeftArgument.myX;
	aLeftArgument.myY = aRightArgument.myY + aLeftArgument.myY;
	aLeftArgument.myZ = aRightArgument.myZ + aLeftArgument.myZ;
	aLeftArgument.myW = aRightArgument.myW + aLeftArgument.myW;
}

template <typename Type>
Vector4<Type> operator-(const Vector4<Type> &aLeftArgument, const Vector4<Type> &aRightArgument)
{
	Vector4<Type> returnObj = aRightArgument;
	returnObj.myX  = (aRightArgument.myX - aLeftArgument.myX)*-1;
	returnObj.myY  = (aRightArgument.myY - aLeftArgument.myY)*-1;
	returnObj.myZ  = (aRightArgument.myZ - aLeftArgument.myZ)*-1;
	returnObj.myW  = (aRightArgument.myW - aLeftArgument.myW)*-1;

	return returnObj;	
}

template <typename Type>
void operator-=(Vector4<Type>& aLeftArgument, const Vector4<Type> &aRightArgument)
{
	aLeftArgument.myX  = aLeftArgument.myX - aRightArgument.myX;
	aLeftArgument.myY  = aLeftArgument.myY - aRightArgument.myY;
	aLeftArgument.myZ  = aLeftArgument.myZ - aRightArgument.myZ;
	aLeftArgument.myW  = aLeftArgument.myW - aRightArgument.myW;
}

template <typename Type>
Vector4<Type> operator*(const Vector4<Type>& aLeftArgument, const Vector4<Type> &aRightArgument)
{
	Vector4<Type> returnObj = aRightArgument;
	returnObj.myX = returnObj.myX * aLeftArgument.myX;
	returnObj.myY = returnObj.myY * aLeftArgument.myY;
	returnObj.myZ = returnObj.myZ * aLeftArgument.myZ;
	returnObj.myW = returnObj.myW * aLeftArgument.myW;

	return returnObj;
}

template <typename Type>
void operator*=(Vector4<Type> &aLeftArgument, const Vector4<Type> &aRightArgument)
{
	aLeftArgument = aLeftArgument*aRightArgument;
}

template <typename Type>
Vector4<Type> operator/(const Vector4<Type> &aLeftArgument, const Vector4<Type> &aRightArgument)
{
	Vector4<Type> returnObj = aRightArgument;

	returnObj.myX = aLeftArgument.myX/aRightArgument.myX;
	returnObj.myY = aLeftArgument.myY/aRightArgument.myY;
	returnObj.myZ = aLeftArgument.myZ/aRightArgument.myZ;
	returnObj.myW = aLeftArgument.myW/aRightArgument.myW;

	return returnObj;
}

template <typename Type>
void operator/=(Vector4<Type> &aLeftArgument, const Vector4<Type> &aRightArgument)
{
	aLeftArgument.myX  = aLeftArgument.myX / aRightArgument.myX;
	aLeftArgument.myY  = aLeftArgument.myY / aRightArgument.myY;
	aLeftArgument.myZ  = aLeftArgument.myZ / aRightArgument.myZ;
	aLeftArgument.myW  = aLeftArgument.myW / aRightArgument.myW;
}

template <typename Type>
Vector4<Type> operator*(const Vector4<Type>& aLeftArgument, const Type aScalar)
{
	Vector4<Type> returnObj = aLeftArgument;
	returnObj.myX = returnObj.myX * aScalar;
	returnObj.myY = returnObj.myY * aScalar;
	returnObj.myZ = returnObj.myZ * aScalar;
	returnObj.myW = returnObj.myW * aScalar;

	return returnObj;
}

template <typename Type>
void operator*=(Vector4<Type>& aLeftArgument, const Type aScalar)
{
	aLeftArgument = aLeftArgument * aScalar;
}

template <typename Type>
Vector4<Type> operator/(const Vector4<Type> &aLeftArgument, const Type aScalar)
{
	Vector4<Type> returnObj = aLeftArgument;
	returnObj.myX = returnObj.myX / aScalar;
	returnObj.myY = returnObj.myY / aScalar;
	returnObj.myZ = returnObj.myZ / aScalar;
	returnObj.myW = returnObj.myW / aScalar;

	return returnObj;
}

template <typename Type>
void operator/=( Vector4<Type>& aLeftArgument, const Type aScalar)
{
	aLeftArgument = aLeftArgument / aScalar;
}
#endif