#pragma once

namespace CommonUtilities
{

	class Space
	{
	public:
		Space();
		~Space();

		void SetPosition(const CU::Vector2f aPosition);
		void SetParent(const Space & aParentSpace);
		void SetNoParent();

		void Rotate2D(const float aRotationInRadians);
		void RotateAroundAxis2D(const float aRotationInRadians);
		
		const Matrix33f GetTransform() const;
		const Vector2f GetPosition() const;

	private:
		Matrix33f myTransformation;
		const Space * myParent;
	};

}