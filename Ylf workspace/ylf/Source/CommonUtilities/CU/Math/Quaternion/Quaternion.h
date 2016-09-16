#pragma once

	//created using reference from http://www.cprogramming.com/tutorial/3d/quaternions.html
namespace CommonUtilities
{
	class Quaternion
	{
	public:
		Quaternion(float aX = 0.0f, float aY = 0.0f, float aZ = 0.0f, float aW = 1.0f);
		void Normalize();

		void RotateAlongAxis(const CU::Vector3f& aAxis, float aRotationAmount);
		void Rotate(const CU::Vector3f& aRotationAmount);
		void RotateX(float aRotationAmount);
		void RotateY(float aRotationAmount);
		void RotateZ(float aRotationAmount);

		//note: (Q1*Q2) != (Q2*Q1)
		Quaternion operator *(const Quaternion& aRight) const;

		//note: (Q1*Q2) != (Q2*Q1)
		Quaternion& operator *=(const Quaternion& aRight);

		//this assumes the quaternion is normalized
		CU::Matrix44f GenerateMatrix() const;
	private:
		CU::Vector3f myRotation;
		float myRotationAmount;
	};
}
