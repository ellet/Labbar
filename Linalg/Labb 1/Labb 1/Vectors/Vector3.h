#pragma once
#include <math.h>

template <typename Type>
class Vector3
{
public:
	union
	{
		Type myX;
		Type x;
		Type r;
		Type myR;
	};

	union
	{
		Type myY;
		Type y;
		Type g;
		Type myG;
	};

	union
	{
		Type myZ;
		Type z;
		Type b;
		Type myB;
	};

	Vector3 operator+(const Vector3 & aVector);
	Vector3 operator-(const Vector3 & aVector);
	Vector3 operator*(const Type aScalar);
	Vector3 operator/(const Type aScalar);

	Vector3 & operator+=(const Vector3 & aVector);
	Vector3 & operator-=(const Vector3 & aVector);
	Vector3 & operator*=(const Type aScalar);
	Vector3 & operator/=(const Type aScalar);

	inline Type Length2();
	inline Type Length();
	inline void Normalize();
	inline Vector3 GetNormalized();

	static inline Type Dot(const Vector3 & aVector1, const Vector3 & aVector2);
	static inline Vector3 Cross(const Vector3 & aVector1, const Vector3 & aVector2);
};

template <typename Type>
Vector3<Type> Vector3<Type>::operator+(const Vector3 & aVector)
{
	Vector3 temp = aVector;
	
	temp.x += x;
	temp.y += y;
	temp.z += z;

	return temp;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator-(const Vector3 & aVector)
{
	Vector3 temp = aVector;

	temp.x -= x;
	temp.y -= y;
	temp.z -= z;

	return temp;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator*(const Type aScalar)
{
	Vector3 temp = (*this);

	temp.x *= aScalar;
	temp.y *= aScalar;
	temp.z *= aScalar;

	return temp;
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator/(const Type aScalar)
{
	Vector3 temp = (*this);

	temp.x /= aScalar;
	temp.y /= aScalar;
	temp.z /= aScalar;

	return temp;
}

template <typename Type>
Vector3<Type> & Vector3<Type>::operator+=(const Vector3 & aVector)
{
	x += aVector.x;
	y += aVector.y;
	z += aVector.z;

	return (*this);
}

template <typename Type>
Vector3<Type> & Vector3<Type>::operator-=(const Vector3 & aVector)
{
	x -= aVector.x;
	y -= aVector.y;
	z -= aVector.z;

	return (*this);
}

template <typename Type>
Vector3<Type> & Vector3<Type>::operator*=(const Type aScalar)
{
	x *= aScalar;
	y *= aScalar;
	z *= aScalar;

	return (*this);
}

template <typename Type>
Vector3<Type> & Vector3<Type>::operator/=(const Type aScalar)
{
	x /= aScalar;
	y /= aScalar;
	z /= aScalar;

	return (*this);
}

template <typename Type>
Type Vector3<Type>::Length2()
{
	return ((x*x) + (y*y) + (z*z));
}

template <typename Type>
Type Vector3<Type>::Length()
{
	return sqrt(Length2());
}

template <typename Type>
void Vector3<Type>::Normalize()
{
	const Type tempLength = Length();
	
	x = x / tempLength;
	y = y / tempLength;
	z = z / tempLength;
}

template <typename Type>
Vector3<Type> Vector3<Type>::GetNormalized()
{
	Vector3 returnVector = (*this);

	returnVector.Normalize();
	return returnVector;
}

template <typename Type>
Type Vector3<Type>::Dot(const Vector3 & aVector1, const Vector3 & aVector2)
{
	return ((aVector1.x*aVector2.x) + (aVector1.y*aVector2.y) + (aVector1.z*aVector2.z));
}

template <typename Type>
Vector3<Type> Vector3<Type>::Cross(const Vector3 & aVector1, const Vector3 & aVector2)
{
	Vector3 returnVector;

	returnVector.x = ((aVector1.y*aVector2.z) - (aVector1.z*aVector2.y));
	returnVector.y = ((aVector1.z*aVector2.x) - (aVector1.x*aVector2.z));
	returnVector.y = ((aVector1.z*aVector2.x) - (aVector1.x*aVector2.z));

	return returnVector;
}