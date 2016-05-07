#pragma once
#include <vector>
#include <thread>
#include <CU/GrowingArray/GrowingArray.h>
#include <CU/Utility/Randomizer/Randomizer.h>
#include <tga2d/math/vector2.h>
#include <CU/NameSpaceAliases.h>

enum class eGameState
{
	eChoosingElements,
	eChoosingValues,
	eStarting,
	eRunning,
	eFinished
};

class Renderer;

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
} 

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

	void UpdatePosition(size_t aPosition);
//	{
////		mySprite->SetPosition()
//	}

	DX2D::Vector2f myOffset;
	DX2D::Vector2f myStartPos;

	size_t myNumber;
	DX2D::CSprite * mySprite;
};

typedef CommonUtilities::GrowingArray<DX2D::CSprite*, size_t> SpriteArray;
typedef CommonUtilities::GrowingArray<size_t, size_t> NumberArray;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 

	void SortWithInsert(NumberArray * aArrayOfNumbers, SpriteArray * aSpriteArray);
	void SortWithMerge(NumberArray * input, size_t size, SpriteArray * aSpriteArray);
	void SortWithShell(NumberArray * aArray, SpriteArray * aSpriteArray);

	void SortWithHeap(NumberArray * aArray, SpriteArray * aSpriteArray);
	void SortWithQuick(NumberArray * aArray, SpriteArray * aSpriteArray, int left, int right);

	void SortWithRadix(size_t * input, int n);

	void CreateRandomStaples();

private:
	void SetupArrays();
	void UpdateAllSprites();

	void StartAlgorithms();
	void DecideNumberOfElements();
	void DecidedElements();
	void DecideValueInterval();
	void DecidedValues();

	CU::GrowingArray<NumberArray> myNumberArrays;
	CU::GrowingArray<SpriteArray> mySpriteArrays;

	DX2D::CText * myText;
	Randomizer myRandomizer;
	Renderer * myRenderer;
	CommonUtilities::GrowingArray<std::thread*> myThreads;
	eGameState myState;

	DX2D::CSprite * myMergeSprite;
	DX2D::CSprite * myQuickSprite;
	DX2D::CSprite * myHeapSprite;
	DX2D::CSprite * myRadixSprite;
	DX2D::CSprite * myShellSprite;
};