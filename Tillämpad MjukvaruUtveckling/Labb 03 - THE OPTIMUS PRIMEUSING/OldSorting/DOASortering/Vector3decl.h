#ifndef VECTOR3DECL_H
#define VECTOR3DECL_H

template <typename Type>
class Vector3
{
public:
	Vector3()
	{
		myX = 0;
		myY = 0;
		myZ = 0;
	}
	Vector3(Type aX, Type aY, Type aZ)
	{
		myX = aX;
		myY = aY;
		myZ = aZ;
	}
	Vector3(const Vector3<Type>& aCopy)
	{
		myX = aCopy.myX;
		myY = aCopy.myY;
		myZ = aCopy.myZ;
	}

	~Vector3()
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
		Type myG;
	};
	union
	{
		Type myZ;
		Type z;
		Type q;
		Type myB;
	};
};

#endif