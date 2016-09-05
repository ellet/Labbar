#include "stdafx.h"
#include "Space.h"

namespace CommonUtilities
{

	Space::Space()
	{
		myParent = nullptr;
	}


	Space::~Space()
	{
	}

	void Space::SetPosition(const CU::Vector2f aPosition)
	{
		myTransformation.SetPosition(aPosition);
	}

	void Space::SetParent(const Space & aParentSpace)
	{
		myParent = &aParentSpace;
	}

	void Space::SetNoParent()
	{
		myParent = nullptr;
	}

	void Space::Rotate2D(const float aRotationInRadians)
	{
		myTransformation.Rotate2D(aRotationInRadians);
	}

	const Matrix33f Space::GetTransform() const
	{
		if (myParent != nullptr)
		{
			return myTransformation * (myParent->GetTransform());
		}
		else
		{
			return myTransformation;
		}
	}

	const Vector2f Space::GetPosition() const
	{
		return GetTransform().GetPosition();
	}

}