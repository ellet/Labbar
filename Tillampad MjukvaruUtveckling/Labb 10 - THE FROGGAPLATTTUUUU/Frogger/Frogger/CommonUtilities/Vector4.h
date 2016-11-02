#ifndef COMMONUTILITIES_VECTOR4_HEADER
#define COMMONUTILITIES_VECTOR4_HEADER

#include <math.h>
#include "assert.h"
#include "MathDefines.h"
#include "Vector3.h"

namespace CommonUtilities
{
	template <typename T>
	class Vector4
	{
	public:
		Vector4();
		Vector4(const T aX, const T aY, const T aZ, const T aW = 1);
		Vector4(const Vector4<T>& aVector);
		Vector4(const Vector3<T>& aVectorToConvertFrom);
		Vector4(const Vector4& aStartingPoint, const Vector4& aDestinationPoint);
		~Vector4();

		inline void			Set(const T aX, const T aY, const T aZ, const T aW);

		inline T			Length() const;
		inline T			LengthSquared() const;
		inline Vector4<T>&	Normalize();
		inline Vector4<T>	Direction();
		inline Vector4<T>	CrossProduct(const Vector4 &aVector) const;
		inline T			DotProduct(const Vector4 &aVector) const;
		inline T			AngleInRadians(const Vector4& aVector) const;

		inline void			Homogenize();


		//////////////////////////////////////////////////////////////////////////
		//																		//
		//						Operator Overloading							//
		//																		//
		//////////////////////////////////////////////////////////////////////////
		inline Vector4&		operator+=(const Vector4& aVector);
		inline Vector4&		operator-=(const Vector4& aVector);
		inline Vector4&		operator*=(const T& aScalar);
		inline Vector4&		operator/=(const T& aScalar);
		inline Vector4&		operator=(const Vector4& aVector);

		inline bool			operator==(const Vector4& aVector) const;
		inline bool			operator!=(const Vector4& aVector) const;

		inline T&			operator[](const unsigned int aIndex);
		inline const T&		operator[](const unsigned int aIndex)const;


		T myX;
		T myY;
		T myZ;
		T myW;
	};

	template <typename T>
	Vector4<T>::Vector4()
	{
		myX = 0;
		myY = 0;
		myZ = 0;
		myW = 0;
	}

	template <typename T>
	Vector4<T>::Vector4(const T aX, const T aY, const T aZ, const T aW)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
		myW=aW;
	}

	template <typename T>
	Vector4<T>::Vector4(const Vector4& aStartingPoint, const Vector4& aDestinationPoint)
	{
		myX = aDestinationPoint.myX - aStartingPoint.myX;
		myY = aDestinationPoint.myY - aStartingPoint.myY;
		myZ = aDestinationPoint.myZ - aStartingPoint.myZ;
		myW = 1;
	}

	template <typename T>
	Vector4<T>::Vector4(const Vector4& aVector)
	{
		*this = aVector;
	}

	template <typename T>
	Vector4<T>::Vector4(const Vector3<T>& aVectorToConvertFrom)
	{
		myX = aVectorToConvertFrom.myX;
		myY = aVectorToConvertFrom.myY;
		myZ = aVectorToConvertFrom.myZ;
		myW = 1;
	}

	template <typename T>
	Vector4<T>::~Vector4()
	{
	}

	template <typename T>
	void Vector4<T>::Set(const T aX, const T aY, const T aZ, const T aW)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
		myW=aW;
	}

	template <typename T>
	Vector4<T>& Vector4<T>::Normalize()
	{
		T aLength=Length();
		myX/=aLength;
		myY/=aLength;
		myZ/=aLength;
		myW = 1.0;
		return *this;
	}

	template <typename T>
	Vector4<T> Vector4<T>::Direction()
	{
		Vector4<T> aCopy(*this);
		aCopy.Normalize();
		return(aCopy);
	}

	template <typename T>
	T Vector4<T>::Length() const 
	{
		return sqrt(myX*myX + myY*myY + myZ*myZ);
	}

	template <typename T>
	T Vector4<T>::LengthSquared() const 
	{
		return(myX*myX + myY*myY + myZ*myZ);
	}

	template <typename T>
	Vector4<T> Vector4<T>::CrossProduct(const Vector4 &aVector) const
	{
		return Vector4<T>(
			myY*aVector.myZ - myZ*aVector.myY,
			myZ*aVector.myX - myX*aVector.myZ,
			myX*aVector.myY - myY*aVector.myX);
	}

	template <typename T>
	T Vector4<T>::DotProduct(const Vector4 &aVector) const 
	{
		return(aVector.myX*myX + aVector.myY*myY + aVector.myZ*myZ);
	}

	template <typename T>
	T Vector4<T>::AngleInRadians(const Vector4& aVector) const
	{
		T aDotProduct = this->DotProduct(aVector);
		T aCalculatedLenght = this->Length() * aVector.Length();
		T aResultAngle = acos(aDotProduct/aCalculatedLenght);

		return(aResultAngle);
	}

	template <typename T>
	void Vector4<T>::Homogenize()
	{
		if(myW != 1)
		{
			myX /= myW;
			myY /= myW;
			myZ /= myW;
			myW = 1.0;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//						Operator Overloading							//
	//																		//
	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& aVector)
	{
		myX+=aVector.myX;
		myY+=aVector.myY;
		myZ+=aVector.myZ;
		myW+=aVector.myW;
		return(*this);
	}
	template <typename T>
	Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& aVector)
	{
		myX-=aVector.myX;
		myY-=aVector.myY;
		myZ-=aVector.myZ;
		myW-=aVector.myW;
		return(*this);
	}

	template <typename T>
	Vector4<T>& Vector4<T>::operator*=(const T& aType)
	{
		myX*=aType;
		myY*=aType;
		myZ*=aType;
		myW*=aType;
		return(*this);
	}

	template <typename T>
	Vector4<T>& Vector4<T>::operator/=(const T& aType)
	{
		myX/=aType;
		myY/=aType;
		myZ/=aType;
		myW/=aType;
		return(*this);
	}

	template <typename T>
	Vector4<T>& Vector4<T>::operator=(const Vector4<T>& aVector)
	{
		myX=aVector.myX;
		myY=aVector.myY;
		myZ=aVector.myZ;
		myW=aVector.myW;
		return(*this);
	}

	template <typename T>
	bool Vector4<T>::operator==(const Vector4<T>& aRightSideVector) const 
	{
		if(myX!=aRightSideVector.myX) return(false);
		if(myY!=aRightSideVector.myY) return(false);
		if(myZ!=aRightSideVector.myZ) return(false);
		if(myW!=aRightSideVector.myW) return(false);
		return(true);
	}

	template<typename T>
	bool Vector4<T>::operator !=(const Vector4<T> &aRightSideVector) const
	{
		return(!(*this == aRightSideVector));
	}


	template <typename T>
	T& Vector4<T>::operator [](const unsigned int aIndex)
	{
		assert(aIndex < 4 && "Attempted to access out of range of Vector!");
		if(aIndex == 0)			return(myX);
		else if(aIndex == 1)	return(myY);
		else if(aIndex == 2)	return(myZ);
		else if(aIndex == 3)	return(myW);
		else assert(false && "Code should never reach this point, debug operator[] in Vector4!");

		return(myX); //This line will never be reached, but the function needs to return something
	}

	template <typename T>
	const T& Vector4<T>::operator [](const unsigned int aIndex) const
	{
		assert(aIndex < 4 && "Attempted to access out of range of Vector!");
		if(aIndex == 0)			return(myX);
		else if(aIndex == 1)	return(myY);
		else if(aIndex == 2)	return(myZ);
		else if(aIndex == 3)	return(myW);
		else assert(false && "Code should never reach this point, debug operator[] in Vector4!");

		return(myX);
	}

	template <typename T>
	Vector4<T> operator+(const Vector4<T>& aLeftSideVector,const Vector4<T>& aRightSideVector)
	{
		Vector4<T> returnValue(aLeftSideVector);
		returnValue+=aRightSideVector;
		return(returnValue);
	}
	template <typename T>
	Vector4<T> operator-(const Vector4<T>& aLeftSideVector,const Vector4<T>& aRightSideVector)
	{
		Vector4<T> returnValue(aLeftSideVector);
		returnValue-=aRightSideVector;
		return(returnValue);
	}

	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aLeftSideVector,const T& aRightSideScalar)
	{
		Vector4<T> returnValue(aLeftSideVector);
		returnValue*=aRightSideScalar;
		return(returnValue);
	}
	template <typename T>
	Vector4<T> operator/(const Vector4<T>& aLeftSideVector,const T& aRightSideScalar)
	{
		Vector4<T> returnValue(aLeftSideVector);
		returnValue/=aRightSideScalar;
		return(returnValue);
	}

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
	typedef Vector4<int> Vector4i;
};

#endif