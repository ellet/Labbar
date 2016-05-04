#pragma once
#include <math.h>

template <typename Type>
class Vector4
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

	union
	{
		Type myW;
		Type w;
		Type a;
		Type myA;
	};

	Vector4 operator+(const Vector4 & aVector);
	Vector4 operator-(const Vector4 & aVector);
	Vector4 operator*(const Type aScalar);
	Vector4 operator/(const Type aScalar);

	Vector4 & operator+=(const Vector4 & aVector);
	Vector4 & operator-=(const Vector4 & aVector);
	Vector4 & operator*=(const Type aScalar);
	Vector4 & operator/=(const Type aScalar);

	inline Type Length2();
	inline Type Length();
	inline void Normalize();
	inline Vector4 GetNormalized();

	static inline Type Dot(const Vector4 & aVector1, const Vector4 & aVector2);
};

template <typename Type>
Vector4<Type> Vector4<Type>::operator+(const Vector4 & aVector)
{
	Vector4 temp = aVector;
	
	temp.x += x;
	temp.y += y;
	temp.z += z;
	temp.w += w;

	return temp;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator-(const Vector4 & aVector)
{
	Vector4 temp = aVector;

	temp.x -= x;
	temp.y -= y;
	temp.z -= z;
	temp.w -= w;

	return temp;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator*(const Type aScalar)
{
	Vector4 temp = (*this);

	temp.x *= aScalar;
	temp.y *= aScalar;
	temp.z *= aScalar;
	temp.w *= aScalar;

	return temp;
}

template <typename Type>
Vector4<Type> Vector4<Type>::operator/(const Type aScalar)
{
	Vector4 temp = (*this);

	temp.x /= aScalar;
	temp.y /= aScalar;
	temp.z /= aScalar;
	temp.w /= aScalar;

	return temp;
}

template <typename Type>
Vector4<Type> & Vector4<Type>::operator+=(const Vector4 & aVector)
{
	x += aVector.x;
	y += aVector.y;
	z += aVector.z;
	w += aVector.w;

	return (*this);
}

template <typename Type>
Vector4<Type> & Vector4<Type>::operator-=(const Vector4 & aVector)
{
	x -= aVector.x;
	y -= aVector.y;
	z -= aVector.z;
	w -= aVector.w;

	return (*this);
}

template <typename Type>
Vector4<Type> & Vector4<Type>::operator*=(const Type aScalar)
{
	x *= aScalar;
	y *= aScalar;
	z *= aScalar;
	w *= aScalar;

	return (*this);
}

template <typename Type>
Vector4<Type> & Vector4<Type>::operator/=(const Type aScalar)
{
	x /= aScalar;
	y /= aScalar;
	z /= aScalar;
	w /= aScalar;

	return (*this);
}

template <typename Type>
Type Vector4<Type>::Length2()
{
	return ((x*x) + (y*y) + (z*z) + (w*w));
}

template <typename Type>
Type Vector4<Type>::Length()
{
	return sqrt(Length2());
}

template <typename Type>
void Vector4<Type>::Normalize()
{
	const Type tempLength = Length();
	
	x = x / tempLength;
	y = y / tempLength;
	z = z / tempLength;
	w = w / tempLength;
}

template <typename Type>
Vector4<Type> Vector4<Type>::GetNormalized()
{
	Vector4 returnVector = (*this);

	returnVector.Normalize();
	return returnVector;
}

template <typename Type>
Type Vector4<Type>::Dot(const Vector4 & aVector1, const Vector4 & aVector2)
{
	return ((aVector1.x*aVector2.x) + (aVector1.y*aVector2.y) + (aVector1.z*aVector2.z) + (aVector1.w*aVector2.w));
}