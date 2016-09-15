#ifndef VECTOR4DECL_H
#define VECTOR4DECL_H


template <typename Type>
class Vector4
{
public:
	Vector4()
	{
		myX = 0;
		myY = 0;
		myZ = 0;
		myW = 0;
	}
	Vector4(Type aX, Type aY, Type aZ, Type aW)
	{
		myX = aX;
		myY = aY;
		myZ = aZ;
		myW = aW;
	}
	Vector4(const Vector4<Type>& aCopy)
	{
		myX = aCopy.myX;
		myY = aCopy.myY;
		myZ = aCopy.myZ;
		myW = aCopy.myW;
	}

	~Vector4()
	{

	}

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
};

#endif