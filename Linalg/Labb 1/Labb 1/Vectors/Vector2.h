#pragma once
#include <math.h>

template <typename Type>
class Vector2
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

	Vector2 operator+(const Vector2 & aVector);
	Vector2 operator-(const Vector2 & aVector);
	Vector2 operator*(const Type aScalar);
	Vector2 operator/(const Type aScalar);

	Vector2 & operator+=(const Vector2 & aVector);
	Vector2 & operator-=(const Vector2 & aVector);
	Vector2 & operator*=(const Type aScalar);
	Vector2 & operator/=(const Type aScalar);

	inline Type Length2();
	inline Type Length();
	inline void Normalize();
	inline Vector2 GetNormalized();

	static inline Type Dot(const Vector2 & aVector1, const Vector2 & aVector2);
};

template <typename Type>
Vector2<Type> Vector2<Type>::operator+(const Vector2 & aVector)
{
	Vector2 temp = aVector;
	
	temp.x += x;
	temp.y += y;

	return temp;
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator-(const Vector2 & aVector)
{
	Vector2 temp = aVector;

	temp.x -= x;
	temp.y -= y;

	return temp;
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator*(const Type aScalar)
{
	Vector2 temp = (*this);

	temp.x *= aScalar;
	temp.y *= aScalar;

	return temp;
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator/(const Type aScalar)
{
	Vector2 temp = (*this);

	temp.x /= aScalar;
	temp.y /= aScalar;

	return temp;
}

template <typename Type>
Vector2<Type> & Vector2<Type>::operator+=(const Vector2 & aVector)
{
	x += aVector.x;
	y += aVector.y;

	return (*this);
}

template <typename Type>
Vector2<Type> & Vector2<Type>::operator-=(const Vector2 & aVector)
{
	x -= aVector.x;
	y -= aVector.y;

	return (*this);
}

template <typename Type>
Vector2<Type> & Vector2<Type>::operator*=(const Type aScalar)
{
	x *= aScalar;
	y *= aScalar;

	return (*this);
}

template <typename Type>
Vector2<Type> & Vector2<Type>::operator/=(const Type aScalar)
{
	x /= aScalar;
	y /= aScalar;

	return (*this);
}

template <typename Type>
Type Vector2<Type>::Length2()
{
	return ((x*x) + (y*y));
}

template <typename Type>
Type Vector2<Type>::Length()
{
	return sqrt(Length2());
}

template <typename Type>
void Vector2<Type>::Normalize()
{
	const Type tempLength = Length();
	
	x = x / tempLength;
	y = y / tempLength;
}

template <typename Type>
Vector2<Type> Vector2<Type>::GetNormalized()
{
	Vector2 returnVector = (*this);

	returnVector.Normalize();
	return returnVector;
}

template <typename Type>
Type Vector2<Type>::Dot(const Vector2 & aVector1, const Vector2 & aVector2)
{
	return ((aVector1.x*aVector2.x) + (aVector1.y*aVector2.y));
}