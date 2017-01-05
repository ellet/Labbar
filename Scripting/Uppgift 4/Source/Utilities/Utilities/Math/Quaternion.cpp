#include "stdafx.h"
#include "Quaternion.h"
#include "MathMacros.h"

namespace SB
{

	Quaternion::Quaternion(float aX, float aY, float aZ, float aW, bool aNormalize /*= true*/)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;

		if (aNormalize == true)
		{
			Normalize();
		}
	}

	void Quaternion::Normalize()
	{
		*this = GetNormalized();
	}

	Quaternion Quaternion::GetNormalized() const
	{
		Quaternion q(0.f, 0.f, 0.f, 0.f, false); //Do not normalize - for stack overflow
		float magnitude = Vector4f(x, y, w, z).Length();
		q.x = x / magnitude;
		q.y = y / magnitude;
		q.z = z / magnitude;
		q.w = w / magnitude;

		return q;
	}

	void Quaternion::RotateAlongAxis(const Vector3f &aAxis, float aRotationAmount)
	{
		float halfAngle = sinf(aRotationAmount / 2.f);

		Quaternion localRotation;
		localRotation.x = aAxis.x * halfAngle;
		localRotation.y = aAxis.y * halfAngle;
		localRotation.z = aAxis.z * halfAngle;
		localRotation.w = cosf(aRotationAmount / 2.f);

		*this = localRotation * *this;

		Normalize();
	}

	void Quaternion::RotateAroundWorldX(float aRotationAmount)
	{
		RotateAlongAxis(Vector3f(1.0f, 0.0f, 0.0f), aRotationAmount);
	}

	void Quaternion::RotateAroundWorldY(float aRotationAmount)
	{
		RotateAlongAxis(Vector3f(0.0f, 1.0f, 0.0f), aRotationAmount);
	}

	void Quaternion::RotateAroundWorldZ(float aRotationAmount)
	{
		RotateAlongAxis(Vector3f(0.0f, 0.0f, 1.0f), aRotationAmount);
	}

	void Quaternion::RotateAroundLocalX(float aRotationAmount)
	{
		RotateAlongAxis(GetRight(), aRotationAmount);
	}

	void Quaternion::RotateAroundLocalY(float aRotationAmount)
	{
		RotateAlongAxis(GetUpward(), aRotationAmount);
	}

	void Quaternion::RotateAroundLocalZ(float aRotationAmount)
	{
		RotateAlongAxis(GetForward(), aRotationAmount);
	}

	void Quaternion::RotateTowardsPoint(const Vector3f & aCurrentPosition,  const Vector3f & aTargetPosition, const float & aDeltaTimeInSeconds, const float & aMaxRotationInDegrees)
	{
		bool angleIsPositive = false;
		const Vector3f CurrentDirection = GetForward().GetNormalized();
		const float sign = GetRight().GetNormalized().Dot(aTargetPosition - aCurrentPosition); //Sign is positive to the right, negative to the left
		Vector3f rotAxis;

		if (sign > M_EPSILONF) // right
		{
			rotAxis = Vector3f::Cross(CurrentDirection, aTargetPosition - aCurrentPosition);
			angleIsPositive = true;
		}
		else if (sign < -M_EPSILONF) //left
		{
			rotAxis = Vector3f::Cross(aTargetPosition - aCurrentPosition, CurrentDirection);
			angleIsPositive = false;
		}
		else //on track or point is precisely behind us
		{
			return;
		}

		// if this is true, then we are on the opposite course :[ (or right course, but we handled that before we called the function)
		if (isnan(rotAxis.z) == true || isnan(rotAxis.y) == true || isnan(rotAxis.x) == true || rotAxis == Vector3f::Zero)
		{
			return;
		}

		float angle = Vector3f::GetAngleFromCross(rotAxis);

		if (isnan(angle) == true || angle == 0.f)
		{
			return;
		}

		const float MaxRotation = DEGREES_TO_RADIANSF(aMaxRotationInDegrees);

		if (angle > MaxRotation)
		{
			angle = MaxRotation;
		}

		angle *= aDeltaTimeInSeconds;


		if (angleIsPositive == false)
		{
			angle *= -1.f;
		}

		RotateAlongAxis(rotAxis, angle);
	}

	Quaternion Quaternion::GetRotation(const Vector3f &aForward, const Vector3f &aDirection, const Vector3f &aUpVector)
	{
		float dot = Vector3f::Dot(aForward, aDirection);
		// test for dot -1, need an almost equal to check here.
		if (dot == -1.0f)
		{
			// vector a and b point exactly in the opposite direction, 
			// so it is a 180 degrees turn around the up-axis
			Quaternion q;
			q.RotateAlongAxis(aUpVector, Pi);
			return q;
		}
		// test for dot 1, need an almost equal to check here.
		else if (dot == 1.f)
		{
			// vector a and b point exactly in the same direction
			// so we return the identity quaternion
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}

		float rotAngle = acos(dot);
		Vector3f rotAxis = Vector3f::Cross(aDirection, aForward);
		rotAxis = Vector3f::Normalize(rotAxis);
		Quaternion q;
		q.RotateAlongAxis(rotAxis, rotAngle);
		return q;
	}

	Quaternion Quaternion::operator*(const Quaternion& aRight) const
	{
		Quaternion returnValue;
		returnValue.x = w * aRight.x + x * aRight.w + y * aRight.z - z * aRight.y;
		returnValue.y = w * aRight.y - x * aRight.z + y * aRight.w + z * aRight.x;
		returnValue.z = w * aRight.z + x * aRight.y - y * aRight.x + z * aRight.w;
		returnValue.w = w * aRight.w - x * aRight.x - y * aRight.y - z * aRight.z;
		returnValue.Normalize();
		return returnValue;
	}

	Vector3f Quaternion::operator*(const Vector3f& aRight) const
	{
		//Proudly stolen from http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
		Vector3f quaternionAsVector(x, y, z);
		float scalar = w;

		Vector3f firstTest = 2.0f * Vector3f::Dot(quaternionAsVector, aRight) * quaternionAsVector;
		Vector3f secondTest = (scalar*scalar - Vector3f::Dot(quaternionAsVector, quaternionAsVector)) * aRight;
		Vector3f thirdTest = 2.0f * scalar * Vector3f::Cross(aRight, quaternionAsVector);

		return Vector3f(
			firstTest
			+ secondTest
			+ thirdTest);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& aRight)
	{
		return *this = *this * aRight;
	}

	Quaternion Quaternion::operator/(const float aScale) const
	{
		return Quaternion(x / aScale, y / aScale, z / aScale, w / aScale);
	}

	Quaternion Quaternion::operator+(const Quaternion& aRight) const
	{
		return Quaternion(x + aRight.x, y + aRight.y, z + aRight.z, w + aRight.w);
	}

	Quaternion Quaternion::operator-(const Quaternion& aRight) const
	{
		return Quaternion(x - aRight.x, y - aRight.y, z - aRight.z, w - aRight.w);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& aRight)
	{
		*this = *this + aRight;
		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& aRight)
	{
		*this = *this - aRight;
		return *this;
	}

	Quaternion& Quaternion::operator/=(const float aScale)
	{
		*this = *this / aScale;
		return *this;
	}

	float Quaternion::Dot(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion)
	{
		Vector3f tempRotationFirst(aFirstQuaternion.x, aFirstQuaternion.y, aFirstQuaternion.z);
		Vector3f tempRotationSecond(aSecondQuaternion.x, aSecondQuaternion.y, aSecondQuaternion.z);
		return tempRotationFirst.Dot(tempRotationSecond) + aFirstQuaternion.w * aSecondQuaternion.w;
	}

	void Quaternion::RotateVector(Vector3f& aRight) const
	{
		aRight = *this * aRight;
	}

	Matrix44f Quaternion::GenerateMatrix() const
	{
		//Shamefully stolen from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
		float X = x;
		float Y = y;
		float Z = z;
		float W = w;
		float xx = X * X;
		float xy = X * Y;
		float xz = X * Z;
		float xw = X * W;
		float yy = Y * Y;
		float yz = Y * Z;
		float yw = Y * W;
		float zz = Z * Z;
		float zw = Z * W;

		Matrix44f returnValue;
		returnValue.m11 = 1 - 2 * (yy + zz);
		returnValue.m12 = 2 * (xy - zw);
		returnValue.m13 = 2 * (xz + yw);

		returnValue.m21 = 2 * (xy + zw);
		returnValue.m22 = 1 - 2 * (xx + zz);
		returnValue.m23 = 2 * (yz - xw);

		returnValue.m31 = 2 * (xz - yw);
		returnValue.m32 = 2 * (yz + xw);
		returnValue.m33 = 1 - 2 * (xx + yy);

		returnValue.m14 = returnValue.m24 = returnValue.m34 = returnValue.m41 = returnValue.m42 = returnValue.m43 = 0;
		returnValue.m44 = 1;

		returnValue.Transpose();

		return returnValue;
	}

	Vector3f Quaternion::GetLeft() const
	{
		return -GetRight();
	}

	Vector3f Quaternion::GetRight() const
	{
		return Vector3f(1.f, 0.f, 0.f) * *this;
	}

	Vector3f Quaternion::GetForward() const
	{
		return Vector3f(0.f, 0.f, 1.f) * *this;
	}

	Vector3f Quaternion::GetBackward() const
	{
		return -GetForward();
	}

	Vector3f Quaternion::GetUpward() const
	{
		return Vector3f(0.f, 1.f, 0.f) * *this;
	}

	Vector3f Quaternion::GetDownward() const
	{
		return -GetUpward();
	}

	Quaternion Quaternion::Lerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress)
	{
		Quaternion temp = Quaternion(aFirstQuaternion.UnsafeScaleMul(1.f - aProgress) + aSecondQuaternion.UnsafeScaleMul(aProgress));
		temp.Normalize();
		return temp;
	}

	Quaternion Quaternion::Slerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress)
	{
		Quaternion first = aFirstQuaternion;
		Quaternion second = aSecondQuaternion;
		float angle = Quaternion::Dot(first, second);
		Quaternion quaternion;
		// make sure we use the short rotation
		if (angle < 0.0f)
		{
			first = first * -1.0f;
			angle *= -1.0f;
		}

		if (angle <= (1 - 0.05f)) // spherical interpolation
		{
			const float theta = acosf(angle);
			const float invsintheta = 1.0f / (sinf(theta));
			const float scale = sinf(theta * (1.0f - aProgress)) * invsintheta;
			const float invscale = sinf(theta * aProgress) * invsintheta;
			Quaternion firstMul = first * scale;
			Quaternion secondMul = second * invscale;
			Quaternion res = firstMul + secondMul;
			return res;
		}
		return Lerp(first, second, aProgress);

	}

	Quaternion Quaternion::CreateFromVectors(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp)
	{
		//stolen from Nicos Look at

		Vector3f forwardVector = Vector3f::Normalize(aEndPosition - aStartPosition);

		float dot = Vector3f::Dot(Vector3f(0.0f, 0.0f, 1.0f), forwardVector);

		if (std::abs(dot - (-1.0f)) < 0.000001f)
		{
			return Quaternion(aUp.x, aUp.y, aUp.z, Pi);
		}
		if (std::abs(dot - (1.0f)) < 0.000001f)
		{
			return Quaternion();
		}

		float rotAngle = (float)std::acosf(dot);
		Vector3f rotAxis = Vector3f::Cross(Vector3f(0.0f, 0.0f, 1.0f), forwardVector);
		rotAxis.Normalize();
		Quaternion quaternion;
		quaternion.RotateAlongAxis(rotAxis, rotAngle);
		return quaternion;
	}

	Quaternion Quaternion::CreateFromVectorsYlf(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp)
	{
		//stolen from Nicos Look at

		Vector3f forwardVector = Vector3f::Normalize(aEndPosition - aStartPosition);

		Vector3f rightVector = Vector3f::Cross(aUp, forwardVector);
		Vector3f realUp = Vector3f::Cross(forwardVector, rightVector);

		float dot = Vector3f::Dot(Vector3f(0.0f, 0.0f, 1.0f), forwardVector);

		if (std::abs(dot - (-1.0f)) < 0.000001f)
		{
			return Quaternion(aUp.x, aUp.y, aUp.z, Pi);
		}
		if (std::abs(dot - (1.0f)) < 0.000001f)
		{
			return Quaternion();
		}

		float rotAngle = (float)std::acosf(dot);
		Vector3f rotAxis = Vector3f::Cross(Vector3f(0.0f, 0.0f, 1.0f), forwardVector);
		rotAxis.Normalize();
		Quaternion quaternion;
		quaternion.RotateAlongAxis(rotAxis, rotAngle);

		float angle = Vector3f::GetAngleBetweenYlf(realUp, quaternion.GetUpward());
		quaternion.RotateAroundLocalZ(angle);

		return quaternion;
	}

	Vector4f Quaternion::GetXYZW() const
{
		return Vector4f(x, y, z, w);
	}

	Quaternion Quaternion::UnsafeScaleMul(const float aScale) const
	{
		return Quaternion(x * aScale, y * aScale, z * aScale, w * aScale, false);
	}

	Quaternion & Quaternion::UnsafeScaleMul(const float aScale)
	{
		*this = *this * aScale;
		return *this;
	}

}
