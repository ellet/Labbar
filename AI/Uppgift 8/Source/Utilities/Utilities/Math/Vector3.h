#pragma once
#include <cmath>

namespace SB
{

	template<typename TYPE>
	class Vector4;

	template<typename TYPE>
	class Vector3
	{
	public:
		Vector3(void)
		{
			x = static_cast<TYPE>(0);
			y = static_cast<TYPE>(0);
			z = static_cast<TYPE>(0);
		}
		Vector3(const Vector3 &aVector3)
		{
			x = aVector3.x;
			y = aVector3.y;
			z = aVector3.z;
		}
		template<typename U> explicit Vector3(const Vector3<U> &aVector)
		{
			x = static_cast<TYPE>(aVector.x);
			y = static_cast<TYPE>(aVector.y);
			z = static_cast<TYPE>(aVector.z);
		}
		Vector3(const TYPE anX, const TYPE aY, const TYPE aZ)
		{
			x = anX;
			y = aY;
			z = aZ;
		}

		friend Vector3 operator +(Vector3 aLeft, const Vector3 &aRight)
		{
			return aLeft += aRight;
		}

		friend Vector3 operator -(Vector3 aLeft, const Vector3 &aRight)
		{
			return aLeft -= aRight;
		}


		friend Vector3 operator *(Vector3 aLeft, const TYPE aRight)
		{
			return aLeft *= aRight;
		}


		friend Vector3 operator /(Vector3 aLeft, const TYPE aRight)
		{
			return aLeft /= aRight;
		}

		friend Vector3 operator *(const TYPE aRight, Vector3 aLeft)
		{
			return aLeft *= aRight;
		}

		friend Vector3 operator *(const Vector3 aRight, Vector3 aLeft)
		{
			return aLeft *= aRight;
		}

		friend Vector3 operator /(const TYPE aRight, Vector3 aLeft)
		{
			return aLeft /= aRight;
		}

		friend Vector3 operator -(Vector3 aRight)
		{
			return aRight *= static_cast<TYPE>(-1);
		}

		friend bool operator ==(const Vector3 &aLeft, const Vector3 &aRight)
		{
			return aLeft.x == aRight.x &&
				aLeft.y == aRight.y &&
				aLeft.z == aRight.z;
		}

		friend bool operator !=(const Vector3 &aLeft, const Vector3 &aRight)
		{
			return (aLeft == aRight) == false;
		}

		Vector3 &operator =(const Vector3 &aRight)
		{
			x = aRight.x;
			y = aRight.y;
			z = aRight.z;
			return *this;
		}

		Vector3 &operator +=(const Vector3 &aRight)
		{
			x += aRight.x;
			y += aRight.y;
			z += aRight.z;
			return *this;
		}
		Vector3 &operator -=(const Vector3 &aRight)
		{
			x -= aRight.x;
			y -= aRight.y;
			z -= aRight.z;
			return *this;
		}
		Vector3 &operator *=(const TYPE aRight)
		{
			x *= aRight;
			y *= aRight;
			z *= aRight;
			return *this;
		}
		Vector3 &operator *=(const Vector3 aRight)
		{
			x *= aRight.x;
			y *= aRight.y;
			z *= aRight.z;
			return *this;
		}

		Vector3 &operator /=(const TYPE aRight)
		{
			x /= aRight;
			y /= aRight;
			z /= aRight;
			return *this;
		}

		TYPE Length(void) const
		{
			return static_cast<TYPE>(sqrt(x * x + y * y + z * z));
		}
		TYPE Length2(void) const
		{
			TYPE length = Length();
			return length * length;
		}
		TYPE Dot(const Vector3 &aRight) const
		{
			return x * aRight.x +
				y * aRight.y +
				z * aRight.z;
		}
		Vector3 Cross(const Vector3 &aRight) const
		{
			return Vector3(y * aRight.z - z * aRight.y,
				z * aRight.x - x * aRight.z,
				x * aRight.y - y * aRight.x);
		}
		Vector3 GetNormalized(void) const
		{
			return *this / Length();
		}

		Vector3 &Normalize(void)
		{
			*this = GetNormalized();
			return *this;
		}

#pragma warning( disable : 4201 )
		union
		{
			struct
			{
				TYPE x, y, z;
			};

			TYPE myNumbers[3];
		};
		template <typename TNewType>
		Vector3<TNewType> As() const
		{
			return Vector3<TNewType>(static_cast<TNewType>(x), static_cast<TNewType>(y), static_cast<TNewType>(z));
		}

		static TYPE Dot(const Vector3 &aLeft, const Vector3 &aRight)
		{
			return aLeft.Dot(aRight);
		}
		static Vector3 Cross(const Vector3 &aLeft, const Vector3 &aRight)
		{
			return aLeft.Cross(aRight);
		}
		static Vector3 Normalize(Vector3 aVector)
		{
			return aVector.GetNormalized();
		}


		static float GetShortestAngleBetween(const Vector3<TYPE> & aFirstVector, const Vector3<TYPE> & aSecondVector)
		{
			float sign = aFirstVector.Dot(aSecondVector);

			//Look in linalg book for proof that this works. Page 67. Only works for cross product of two NORMALIZED vectors
			float crossLength = Vector3<TYPE>::Cross(aFirstVector.GetNormalized(), aSecondVector.GetNormalized()).Length();
			//Clamp for float problems

			if (crossLength > 1.f)
			{
				crossLength = 1.f;
			}
			else if (crossLength < 0.f)
			{
				crossLength = 0.f;
			}

			float angle = asin(crossLength);

			if (sign < 0.f) // angle is greater than 90, but cross angle doesn't distinct forward from backwards
			{
				angle = 3.1415926f - angle;
			}

			return angle;
		}

		//Returns the positive "clockwise" Angle From first to second vector. 
		static float GetAngleBetween(const Vector3<TYPE> & aFirstVector, const Vector3<TYPE> & aSecondVector)
		{
			float angle = 0.f;

			angle = GetAngleFromCross(Vector3<TYPE>::Cross(aFirstVector.GetNormalized(), aSecondVector.GetNormalized()));

			//Handle angle that is 90 degrees behind us
			float dot = aFirstVector.Dot(aSecondVector);
			if (dot < 0.f)
			{
				angle += 90.f*(3.14159265f / 180.0f);
			}

			return angle;
		}

		static float GetAngleFromCross(const Vector3<TYPE> & aCrossProductFromNormalizedVectors)
		{
			//Look in linalg book for proof that this works. Page 67. Only works for cross product of two NORMALIZED vectors
			float crossLength = aCrossProductFromNormalizedVectors.Length();
			//Clamp for float problems
			if (crossLength > 1.f)
			{
				crossLength = 1.f;
			}
			else if (crossLength < 0.f)
			{
				crossLength = 0.f;
			}

			return crossLength;
		}

		operator Vector4<TYPE>() const
		{
			return Vector4<TYPE>(x, y, z, 1.f);
		}

		static const Vector3 Zero,
			UnitX,
			UnitY,
			UnitZ,
			One;
	};

	using Vector3c = Vector3 < char >;
	using Vector3i = Vector3 < int >;
	using Vector3ui = Vector3 < unsigned int >;
	using Vector3f = Vector3 < float >;
	using Vector3d = Vector3 < double >;

	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Zero(0, 0, 0);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitX(1, 0, 0);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitY(0, 1, 0);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitZ(0, 0, 1);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::One(1, 1, 1);
}
