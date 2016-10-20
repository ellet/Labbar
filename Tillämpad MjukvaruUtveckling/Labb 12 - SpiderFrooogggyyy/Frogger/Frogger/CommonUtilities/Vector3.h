#ifndef COMMONUTILITIES_VECTOR3_HEADER
#define COMMONUTILITIES_VECTOR3_HEADER

#include <math.h>
#include "assert.h"
#include "MathDefines.h"

namespace CommonUtilities
{
	template <typename T>
	class Matrix33;

	template <typename T>
	class Vector4;

	template <typename T>
	class Vector3
	{
	public:
		Vector3();
		Vector3(const T aX, const T aY, const T aZ);
		Vector3(const Vector3& aStartingPoint, const Vector3& aDestinationPoint);
		Vector3(const Vector3& aVector);
		Vector3(const float* aVector);
		Vector3(Vector4<T> aVectorToConvertFrom);
		~Vector3();

		inline void			Set(const T aX, const T aY, const T aZ);

		inline T			Length() const;
		inline T			LengthSquared() const;
		inline Vector3<T>&	Normalize();
		static Vector3<T>	Normalize(const Vector3& aVector);
		inline Vector3<T>	Direction();
		inline Vector3<T>	CrossProduct(const Vector3 &aVector) const;
		inline T			DotProduct(const Vector3 &aVector) const;        
		inline T			AngleInRadians(const Vector3& aVector) const;
		inline void			Truncate(T aMaxValue);
		inline void			DeTruncate(T aMinValue);


		//////////////////////////////////////////////////////////////////////////
		//																		//
		//						Operator Overloading							//
		//																		//
		//////////////////////////////////////////////////////////////////////////
		inline Vector3&		operator+=(const Vector3& aVector);
		inline Vector3&		operator-=(const Vector3& aVector);
		inline Vector3&		operator*=(const T& aScalar);
		inline Vector3&		operator/=(const T& aScalar);
		inline Vector3&		operator=(const Vector3& aVector);
		inline Vector3&		operator=(const float* aVector);
		inline bool			operator<(const T& aScalar);

		inline bool			operator==(const Vector3& aVector) const;
		inline bool			operator!=(const Vector3& aVector) const;

		inline T&			operator[](const unsigned int aIndex);
		inline const T&		operator[](const unsigned int aIndex)const;


		T myX;
		T myY;
		T myZ;
	};

	template <typename T>
	Vector3<T>::Vector3()
	{
	}

	template <typename T>
	Vector3<T>::Vector3(const T aX, const T aY, const T aZ)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
	}

	template <typename T>
	Vector3<T>::Vector3(const Vector3& aStartingPoint, const Vector3& aDestinationPoint)
	{
		myX = aDestinationPoint.myX - aStartingPoint.myX;
		myY = aDestinationPoint.myY - aStartingPoint.myY;
		myZ = aDestinationPoint.myZ - aStartingPoint.myZ;
	}

	template <typename T>
	Vector3<T>::Vector3(const float* aVector)
	{
		*this = aVector;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator=(const float* aVector)
	{
		myX = aVector[0];
		myY = aVector[1];
		myZ = aVector[2];
		return *this;
	}

	template <typename T>
	Vector3<T>::Vector3(const Vector3& aVector)
	{
		*this = aVector;
	}

	template <typename T>
	Vector3<T>::Vector3(Vector4<T> aVectorToConvertFrom)
	{
		if(aVectorToConvertFrom.myW != 1)
		{
			aVectorToConvertFrom.Homogenize();
		}
		
		myX = aVectorToConvertFrom.myX;
		myY = aVectorToConvertFrom.myY;
		myZ = aVectorToConvertFrom.myZ;
	}

	template <typename T>
	Vector3<T>::~Vector3()
	{
	}

	template <typename T>
	void Vector3<T>::Set(const T aX, const T aY, const T aZ)
	{
		myX=aX;
		myY=aY;
		myZ=aZ;
	}

	template <typename T>
	Vector3<T>& Vector3<T>::Normalize()
	{
		T aLength=Length();
		myX/=aLength;
		myY/=aLength;
		myZ/=aLength;
		return *this;
	}

	template <typename T>
	Vector3<T> Vector3<T>::Normalize(const Vector3<T>& aVector)
	{
		Vector3<T> tmpVec = aVector;
		T length = tmpVec.Length();
		tmpVec.myX /= length;
		tmpVec.myY /= length;
		tmpVec.myZ /= length;
		return tmpVec;
	}

	template <typename T>
	Vector3<T> Vector3<T>::Direction()
	{
		Vector3<T> aCopy(*this);
		aCopy.Normalize();
		return(aCopy);
	}

	template <typename T>
	T Vector3<T>::Length() const 
	{
		return sqrt(myX*myX + myY*myY + myZ*myZ);
	}

	template <typename T>
	T Vector3<T>::LengthSquared() const 
	{
		return(myX*myX + myY*myY + myZ*myZ);
	}

	template <typename T>
	Vector3<T> Vector3<T>::CrossProduct(const Vector3 &aVector) const
	{
		return Vector3<T>(
			myY*aVector.myZ - myZ*aVector.myY,
			myZ*aVector.myX - myX*aVector.myZ,
			myX*aVector.myY - myY*aVector.myX);
	}

	template <typename T>
	T Vector3<T>::DotProduct(const Vector3 &aVector) const 
	{
		return(aVector.myX*myX + aVector.myY*myY + aVector.myZ*myZ);
	}

	template <typename T>
	T Vector3<T>::AngleInRadians(const Vector3& aVector) const
	{
		T aDotProduct = this->DotProduct(aVector);
		T aCalculatedLenght = this->Length() * aVector.Length();
		T aResultAngle = acos(aDotProduct/aCalculatedLenght);

		return(aResultAngle);
	}

	template <typename T>
	void Vector3<T>::Truncate(T aMaxValue)
	{
		if(this->Length() > aMaxValue)
		{
			this->Normalize();
			*this *= aMaxValue;
		}
	}

	template <typename T>
	void Vector3<T>::DeTruncate(T aMinValue)
	{
		if(this->Length() < aMinValue)
		{
			this->Normalize();
			*this *= aMinValue;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//						Operator Overloading							//
	//																		//
	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& aVector)
	{
		myX+=aVector.myX;
		myY+=aVector.myY;
		myZ+=aVector.myZ;
		return(*this);
	}
	template <typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& aVector)
	{
		myX-=aVector.myX;
		myY-=aVector.myY;
		myZ-=aVector.myZ;
		return(*this);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator*=(const T& aType)
	{
		myX*=aType;
		myY*=aType;
		myZ*=aType;
		return(*this);
	}

	template <typename T>
	bool Vector3<T>::operator<(const T& aScalar)
	{
		if(myX > aScalar) return false;
		if(myY > aScalar) return false;
		if(myZ > aScalar) return false;
		return false;
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator/=(const T& aType)
	{
		myX/=aType;
		myY/=aType;
		myZ/=aType;
		return(*this);
	}

	template <typename T>
	Vector3<T>& Vector3<T>::operator=(const Vector3<T>& aVector)
	{
		myX=aVector.myX;
		myY=aVector.myY;
		myZ=aVector.myZ;
		return(*this);
	}

	template <typename T>
	bool Vector3<T>::operator==(const Vector3<T>& aRightSideVector) const 
	{
		if(myX!=aRightSideVector.myX) return(false);
		if(myY!=aRightSideVector.myY) return(false);
		if(myZ!=aRightSideVector.myZ) return(false);
		return(true);
	}

	template<typename T>
	bool Vector3<T>::operator !=(const Vector3<T> &aRightSideVector) const
	{
		return(!(*this == aRightSideVector));
	}


	template <typename T>
	T& Vector3<T>::operator [](const unsigned int aIndex)
	{
		assert(aIndex < 3 && "Attempted to access out of range of Vector!");
		if(aIndex == 0)			return(myX);
		else if(aIndex == 1)	return(myY);
		else if(aIndex == 2)	return(myZ);
		else assert(false && "Code should never reach this point, debug operator[] in Vector3!");

		return(myX); //This line will never be reached, but the function needs to return something
	}

	template <typename T>
	const T& Vector3<T>::operator [](const unsigned int aIndex) const
	{
		assert(aIndex < 3 && "Attempted to access out of range of Vector!");
		if(aIndex == 0)			return(myX);
		else if(aIndex == 1)	return(myY);
		else if(aIndex == 2)	return(myZ);
		else assert(false && "Code should never reach this point, debug operator[] in Vector3!");

		return(myX);
	}

	template <typename T>
	Vector3<T> operator+(const Vector3<T>& aLeftSideVector,const Vector3<T>& aRightSideVector)
	{
		Vector3<T> returnValue(aLeftSideVector);
		returnValue+=aRightSideVector;
		return(returnValue);
	}
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& aLeftSideVector,const Vector3<T>& aRightSideVector)
	{
		Vector3<T> returnValue(aLeftSideVector);
		returnValue-=aRightSideVector;
		return(returnValue);
	}

	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aLeftSideVector,const T& aRightSideScalar)
	{
		Vector3<T> returnValue(aLeftSideVector);
		returnValue*=aRightSideScalar;
		return(returnValue);
	}
	template <typename T>
	Vector3<T> operator/(const Vector3<T>& aLeftSideVector,const T& aRightSideScalar)
	{
		Vector3<T> returnValue(aLeftSideVector);
		returnValue/=aRightSideScalar;
		return(returnValue);
	}

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int> Vector3i;
};

namespace CU = CommonUtilities;

#endif