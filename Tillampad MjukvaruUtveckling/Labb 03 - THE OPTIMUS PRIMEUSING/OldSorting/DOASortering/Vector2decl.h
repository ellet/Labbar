#ifndef VECTOR2DECL_H
#define VECTOR2DECL_H
#include <math.h>


template <typename Type> class Vector2
{
public:
	Vector2()
	{
		myX = 0;
		myY = 0;
	}
	Vector2(Type aX, Type aY)
	{
		myX = aX;
		myY = aY;
	}
	Vector2(const Vector2<Type>& aCopy)
	{
		myX = aCopy.myX;
		myY = aCopy.myY;
	}

	~Vector2()
	{
	}


	union
	{
		Type myX;
		Type x;
		Type u;
		Type myR;
	};
	union
	{
		Type myY;
		Type y;
		Type v;
		Type G;
	};
	
};

typedef Vector2<float> Vector2f;

#endif