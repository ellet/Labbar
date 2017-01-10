#include "stdafx.h"
#include "StreakLogic.h"

namespace SB
{
	float StreakLogic::CalculateSize(float progress)
	{
		return 1.0f;
	}
	Vector4f StreakLogic::CalculateColor(float progress)
	{
		return Vector4f::One;
	}

	StreakLogic::~StreakLogic()
	{
	}
	void UnityStreakLogic::SaveToJson(JsonSerializer &aSerializer) const 
{
		JsonSerializer &serializer = aSerializer;
		serializer.WriteArray("colors");
		for (unsigned short i = 0;i < myColors.Size(); ++i)
		{
			serializer.WriteArrayValue(myColors[i]);
		}
		serializer.StepOut();

		serializer.WriteArray("sizes");
		for (unsigned short i = 0; i < myColors.Size(); ++i)
		{
			serializer.WriteArrayValue(mySizes[i]);
		}
		serializer.StepOut();
	}

	UnityStreakLogic::UnityStreakLogic(DataNode aNode)
	{
		auto && colors = aNode["colors"];
		myColors.Resize(static_cast<unsigned short>(colors.Size()));
		
		for (unsigned short i=0; i<myColors.Size(); i++)
		{
			myColors[i].x = colors[i][0].GetFloat();
			myColors[i].y = colors[i][1].GetFloat();
			myColors[i].z = colors[i][2].GetFloat();
			myColors[i].w = colors[i][3].GetFloat();
		}

		auto && sizes = aNode["sizes"];
		mySizes.Resize(static_cast<unsigned short>(sizes.Size()));

		for (unsigned short i = 0; i<mySizes.Size(); i++)
		{
			mySizes[i] = sizes[i].GetFloat();
		}
	}

	UnityStreakLogic::UnityStreakLogic(const GrowingArray<Vector4f>& aColors, const GrowingArray<float>& aSizes)
	{
		myColors = aColors;
		mySizes = aSizes;
	}

	float UnityStreakLogic::CalculateSize(float progress)
	{
		unsigned short index = static_cast<unsigned short>(static_cast<float>(mySizes.Size()) * progress);
		if (index >= mySizes.Size())
		{
			index = mySizes.Size() - 1;
		}

		const float thisSize = mySizes[index];
		float nextSize = thisSize;

		if (index + 1 < mySizes.Size())
		{
			nextSize = mySizes[index + 1];
		}

		const float progressStep = 1.f / static_cast<float>(mySizes.Size());

		float progressToNext = (progress - index * progressStep) / progressStep;

		return thisSize + (nextSize - thisSize) * progressToNext;
	}

	Vector4f UnityStreakLogic::CalculateColor(float progress)
	{
		unsigned short index = static_cast<unsigned short>(static_cast<float>(myColors.Size()) * progress);
		if (index >= myColors.Size())
		{
			index = myColors.Size() - 1;
		}

		const Vector4f & thisColor = myColors[index];
		Vector4f nextColor = thisColor;

		if (index + 1 < myColors.Size())
		{
			nextColor = myColors[index + 1];
		}

		const float progressStep = 1.f / static_cast<float>(myColors.Size());

		float progressToNext = (progress - index * progressStep) / progressStep;

		return thisColor + (nextColor - thisColor) * progressToNext;
	}

	

	ConstantStreakProperties::ConstantStreakProperties(const Vector3f& aColor, float aSize)
	{
		myColor = aColor;
		mySize = aSize;
	}

	float ConstantStreakProperties::CalculateSize(float aProgress)
	{
		return mySize;
	}

	Vector4f ConstantStreakProperties::CalculateColor(float aProgress)
	{
		return myColor;
	}
}
