#ifndef COMMONUTILITIES_VECTOR_HEADER
#define COMMONUTILITIES_VECTOR_HEADER

#include <math.h>
#include "MathDefines.h"
//#include "Vector3.h"
namespace CommonUtilities
{
	template <typename T>
	class Vector3;
	template <typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T aX,T aY);
		Vector2(const Vector2& aVector);
		Vector2(const Vector3<T>& aVector);
		Vector2(const Vector2& aStartingPoint, const Vector2& aDestinationPoint);
		~Vector2();

		inline void			Set(T aX,T aY);

		inline Vector2		Direction();
		inline T			Length() const;
		inline T			LengthSquared() const;
		inline T			DotProduct(const Vector2& aVector2);
		inline T			DotPerpendicular(const Vector2& aVector2);
		inline Vector2<T>&	Normalize();
		inline T			AngleInRadians(const Vector2& aTarget);
		inline void			Rotate(const float& aRadian);


		//////////////////////////////////////////////////////////////////////////
		//																		//
		//						Operator Overloading							//
		//																		//
		//////////////////////////////////////////////////////////////////////////

		inline Vector2&		operator+=(const Vector2& aVector);
		inline Vector2&		operator-=(const Vector2& aVector);
		inline Vector2&		operator*=(const T& aType);
		inline Vector2&		operator/=(const T& aType);
		inline Vector2&		operator=(const Vector2& aVector);        

		inline bool			operator==(const Vector2& aVector) const;        
		inline bool			operator!=(const Vector2& aVector) const;

		inline T&			operator[](const unsigned int aIndex);
		inline const T&		operator[](const unsigned int aIndex)const;

		T			myX;
		T			myY;
	};

	template <typename T>
	Vector2<T>::Vector2()
	{
	}

	template <typename T>
	Vector2<T>::Vector2(const T aX,const T aY)
	{
		myX=aX;
		myY=aY;
	}

	template <typename T>
	Vector2<T>::Vector2(const Vector3<T>& aVector)
	{
		myX = aVector.myX;
		myY = aVector.myZ;
	}

	template <typename T>
	Vector2<T>::Vector2(const Vector2<T>& aVector)
	{
		*this = aVector;
	}
	
	template <typename T>
	Vector2<T>::Vector2(const Vector2& aStartingPoint, const Vector2& aDestinationPoint)
	{
		myX = aDestinationPoint.myX - aStartingPoint.myX;
		myY = aDestinationPoint.myY - aStartingPoint.myY;
	}

	template <typename T>
	Vector2<T>::~Vector2()
	{
	}

	template <typename T>
	void Vector2<T>::Set(const T aX,const T aY)
	{
		myX=aX;
		myY=aY;
	}

	template<typename T>
	Vector2<T> Vector2<T>::Direction()
	{
		Vector2<T> aVector((*this));
		aVector.Normalize();
		return aVector;
	}

	template<typename T>
	Vector2<T>& Vector2<T>::operator=(const Vector2<T>& aVector)
	{
		myX = aVector.myX;
		myY = aVector.myY;
		return (*this);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::Normalize()
	{
		T aLength=this->Length();
        if(aLength == 0)
        {
            return(*this);
        }
		myX/=aLength;
		myY/=aLength;
		return *this;
	}

	template <typename T>
	T Vector2<T>::Length() const 
	{
		return(sqrt(myX*myX + myY*myY));
	}

	template <typename T>
	T Vector2<T>::LengthSquared() const 
	{
		return(myX*myX + myY*myY);
	}

	template <typename T>
	T Vector2<T>::DotProduct(const Vector2& aVector2)
	{
 		return myX*aVector2.myX + myY*aVector2.myY;
	}

	template <typename T>
	T Vector2<T>::DotPerpendicular(const Vector2& aVector2)
	{
		return myX*aVector2.myY - myY*aVector2.myX;
	}

	template <typename T>
	T Vector2<T>::AngleInRadians(const Vector2& aTarget)
	{
		T aDotProduct = this->DotProduct(aTarget);
		T aCalculatedLenght = this->Length() * aTarget.Length();
		T aResultAngle = acos(aDotProduct/aCalculatedLenght);

		return(aResultAngle);
	}

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//						Operator Overloading							//
	//																		//
	//////////////////////////////////////////////////////////////////////////

	template <typename T>
	Vector2<T> operator+(const Vector2<T>& aLeftSideVector,const Vector2<T>& aRightSideVector)
	{
		Vector2<T> returnValue(aLeftSideVector);
		returnValue+=aRightSideVector;
		return(returnValue);
	}
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& aLeftSideVector,const Vector2<T>& aRightSideVector)
	{
		Vector2<T> returnValue(aLeftSideVector);
		returnValue-=aRightSideVector;
		return(returnValue);
	}

	template <typename T>
	Vector2<T> operator*(const Vector2<T>& aLeftSideVector,const T& aRightSideType)
	{
		Vector2<T> returnValue(aLeftSideVector);
		returnValue*=aRightSideType;
		return(returnValue);
	}

	template <typename T>
	Vector2<T> operator/(const Vector2<T>& aLeftSideVector,const T& aRightSideType)
	{
		Vector2<T> returnValue(aLeftSideVector);
		returnValue/=aRightSideType;
		return(returnValue);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& aVector)
	{
		myX+=aVector.myX;
		myY+=aVector.myY;
		return(*this);
	}

	template <typename T>
	void Vector2<T>::Rotate(const float& aRadian)
	{
		float x = myX;
		float y = myY;
		float SIN = sin(aRadian);
		float COS = cos(aRadian);
		myX = COS * x - SIN *y;
		myY = SIN * x + COS *y;
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& aVector)
	{
		myX-=aVector.myX;
		myY-=aVector.myY;
		return(*this);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator*=(const T& aType)
	{
		myX*=aType;
		myY*=aType;
		return(*this);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator/=(const T& aType)
	{
		myX/=aType;
		myY/=aType;
		return(*this);
	}

	template <typename T>
	bool Vector2<T>::operator==(const Vector2<T>& aRightSideVector) const 
	{
		if(myX!=aRightSideVector.myX) return(false);
		if(myY!=aRightSideVector.myY) return(false);
		return(true);
	}

	template <typename T>
	bool Vector2<T>::operator!=(const Vector2<T>& aRightSideVector) const 
	{
		if(myX==aRightSideVector.myX) return(false);
		if(myY==aRightSideVector.myY) return(false);
		return(true);
	}

	template <typename T>
	T& Vector2<T>::operator [](const unsigned int aIndex)
	{
		assert(aIndex < 2 && "Attempted to access out of range of Vector!");
		if(aIndex == 0)			return(myX);
		else if(aIndex == 1)	return(myY);
		else assert(false && "Code should never reach this point, debug operator[] in Vector2!");

		return(myX); //This line will never be reached, but the function needs to return something
	}

	template <typename T>
	const T& Vector2<T>::operator [](const unsigned int aIndex) const
	{
		assert(aIndex < 2 && "Attempted to access out of range of Vector!");
		if(aIndex == 0)			return(myX);
		else if(aIndex == 1)	return(myY);
		else assert(false && "Code should never reach this point, debug operator[] in Vector2!");

		return(myX); //This line will never be reached, but the function needs to return something
	}

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<int> Vector2i;
};

#endif