#pragma once


//created using reference from http://www.cprogramming.com/tutorial/3d/quaternions.html
namespace ENGINE_NAMESPACE
{

	class Quaternion
	{
	public:
		Quaternion(float aX = 0.0f, float aY = 0.0f, float aZ = 0.0f, float aW = 1.f, bool aNormalize = true);

		void Normalize();
		Quaternion GetNormalized() const;

		void RotateAlongAxis(const Vector3f& aAxis, float aRotationAmount);

		void RotateAroundWorldX(float aRotationAmount);
		void RotateAroundWorldY(float aRotationAmount);
		void RotateAroundWorldZ(float aRotationAmount);

		void RotateAroundLocalX(float aRotationAmount);
		void RotateAroundLocalY(float aRotationAmount);
		void RotateAroundLocalZ(float aRotationAmount);

		void RotateTowardsPoint(const Vector3f & aCurrentPosition, const Vector3f & aTargetPosition, const float & aDeltaTimeInSeconds, const float & aMaxRotationInDegrees);

		static Quaternion GetRotation(const Vector3f &aForward, const Vector3f &aDirection, const Vector3f &aUpVector);

		static float Dot(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion);

		//note: (Q1*Q2) != (Q2*Q1)
		Quaternion operator *(const Quaternion& aRight) const;
		//note: (Q1*Q2) != (Q2*Q1)
		Quaternion& operator *=(const Quaternion& aRight);
		//Rotate into
		Vector3f operator *(const Vector3f& aRight) const;
		void RotateVector(Vector3f& aRight) const;

		//----
		//Quaternion operator*(const float aScale) const;
		Quaternion operator / (const float aScale) const;
		Quaternion operator + (const Quaternion& aRight) const;
		Quaternion operator - (const Quaternion& aRight) const;

		//Quaternion& operator *=(const float aScale);
		Quaternion& operator /= (const float aScale);
		Quaternion& operator += (const Quaternion& aRight);
		Quaternion& operator -= (const Quaternion& aRight);

		//this assumes the quaternion is normalized
		Matrix44f GenerateMatrix() const;

		Vector3f GetLeft() const;
		Vector3f GetRight() const;
		Vector3f GetForward() const;
		Vector3f GetBackward() const;
		Vector3f GetUpward() const;
		Vector3f GetDownward() const;

		static Quaternion Lerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress);
		static Quaternion Slerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress);

		static Quaternion CreateFromVectors(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp);
		static Quaternion CreateFromVectorsYlf(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp);

		Vector4f GetXYZW()const ;
	private:
		//Unsafe since the quaternions are not normalized afterwards
		Quaternion UnsafeScaleMul(const float aScale) const;
		Quaternion & UnsafeScaleMul(const float aScale);

		float x, y, z, w;
	};

	inline Vector3f operator *(const Vector3f & aVector, const Quaternion & aQuaternion)
	{
		Vector4f m = Vector4f(aVector, 1.f);
		m = m * aQuaternion.GetNormalized().GenerateMatrix();
		return Vector3f(m.x, m.y, m.z);
	}

	inline Vector3f & operator *=(Vector3f & aVector, const Quaternion & aQuaternion)
	{
		aVector = aVector * aQuaternion;
		return aVector;
	}

}
