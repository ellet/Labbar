#pragma once
#include "Renderer.h"
#include <tga2d/math/vector2.h>
#include <CU/GrowingArray/GrowingArray.h>

typedef CommonUtilities::GrowingArray<Staple, size_t> StapleArray;

class Staple
{
public:
	Staple();
	Staple(size_t aNumber);

	bool operator >(const Staple & aRight) const
	{
		return (myNumber > aRight.myNumber);
	}
	bool operator <(const Staple & aRight) const
	{
		return (myNumber < aRight.myNumber);
	}

	void UpdatePosition(size_t aIndex);

	DX2D::Vector2f myOffset;
	DX2D::Vector2f myStartPos;

	size_t myNumber;
	DX2D::CSprite * mySprite;
};

void CreateRandomStaples(StapleArray & aArrayOfNumbers, Renderer & aRenderer)
{
	for (size_t iNumber = 0; iNumber < MaxElementsNumber; ++iNumber)
	{
		size_t tempNumber = static_cast<size_t>(myRandomizer.GetRandomValue(1.f, static_cast<float>(MaxValueNumber)));
		aArrayOfNumbers.Add(Staple(tempNumber));
		aRenderer->AddSprite(*aArrayOfNumbers.GetLast().mySprite);
	}
}

void FixPosition(StapleArray & aArrayOfNumbers, const DX2D::Vector2f & aStartPosition = DX2D::Vector2f(0.f, 0.2f), const DX2D::Vector2f & aOffsetPosition = DX2D::Vector2f(0.001f, 0.0f));