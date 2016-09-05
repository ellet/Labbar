#include "stdafx.h"
#include "StaticSprite.h"
#include "tga2d/sprite/sprite.h"
#include "RenderConverter.h"
#include <CU/Utility/Math/Isometric.h>
#include <CU/Utility/DataHolder/SingletonDataHolder.h>




CU::GrowingArray<DX2D::CSprite*> StaticSprite::ourSprites;

IndexMap StaticSprite::ourIndexDictionary;


StaticSprite::StaticSprite()
{
	myIsInitiedFlag = false;

	myRenderData.mySizeInPixels = { 100.f, 100.f };
	myPriority = 1000.f;
}

StaticSprite::~StaticSprite()
{
}

void StaticSprite::Init(const std::string & aFilePath/* = "Sprites/trashTestFiles/biggerTestTile.png"*/, const CU::Vector4f & aRect /*= CU::Vector4f::Zero*/, const CU::Vector2f & aPivotPoint /*= CU::Vector2f::Zero*/, const bool aSync)
{
	myIsInitiedFlag = true;

	unsigned short tempIndex;
	if (CheckIfSpriteExists(tempIndex, aFilePath, aRect) == false)
	{
		myImageIndex = AddImage(aFilePath, aRect, aPivotPoint);
		CalculateSizeOfSprite(aRect);		
	}
	else
	{
		myImageIndex = tempIndex;
		CalculateSizeOfSprite(aRect);
	}
	myLayer = enumRenderLayer::eFloor;
}

unsigned short StaticSprite::AddImage(const std::string & aFilePath, const CU::Vector4f & aRect /*= CU::Vector4f::One*/, const CU::Vector2f & aPivotPoint /*= CU::Vector2f::Zero*/)
{
	IndexKey tempKey(aFilePath, aRect);

	bool foundValue = false;
	DX2D::CSprite * workSprite = nullptr;
	if (ourIndexDictionary.count(tempKey) > 0)
	{
		unsigned short tempIndex = ourIndexDictionary[tempKey];
		foundValue = true;
		workSprite = ourSprites[tempIndex];
	}
	else
	{
		ourSprites.Add(new DX2D::CSprite(aFilePath.c_str()));
		workSprite = ourSprites.GetLast();
	}

	if (foundValue == true)
	{
		return ourIndexDictionary[tempKey];
	}

	const float spriteWidth = static_cast<float>(workSprite->GetImageSize().x);
	const float spriteHeight = static_cast<float>(workSprite->GetImageSize().y);

	const float TempStartPointX = aRect.x / spriteWidth;
	const float TempStartPointY = aRect.y / spriteHeight;

	const float TempWidth = aRect.Width / spriteWidth;
	const float TempHeight = aRect.Height / spriteHeight;

	const float TempEndPointX = TempStartPointX + TempWidth;
	const float TempEndPointY = TempStartPointY + TempHeight;

	if (aRect != CU::Vector4f::Zero)
	{
		workSprite->SetTextureRect(TempStartPointX, TempStartPointY, TempEndPointX, TempEndPointY);
	}
	
	workSprite->SetPivot(DX2D::Vector2f(aPivotPoint.x, aPivotPoint.y));	

	ourIndexDictionary[tempKey] = (ourSprites.Size() - 1);
	return ourIndexDictionary[tempKey];
}

CU::Vector2f StaticSprite::GetSizeInPixels() const
{
	return myRenderData.mySizeInPixels;
}

CU::Vector2f StaticSprite::GetSize() const
{
	return{ GetSprite()->GetSize().x, GetSprite()->GetSize().y };
}

/*
	Sprite will be added to buffer and rendered next frame. Changes after this point will not affect the sprite on the buffer.
*/
void StaticSprite::Draw(const CU::Vector2f & aPosition) const
{
	DL_ASSERT(myIsInitiedFlag == true, "Static sprite not initialized");
	RenderConverter::CalculateAndRenderSprite(*this, aPosition);	
}

void StaticSprite::DrawWithNormalized(const CU::Vector2f & aNormalizedPosition) const
{
	RenderConverter::RenderSpriteNormalized(*this, aNormalizedPosition);
}


void StaticSprite::SetSizeInPixels(const CU::Vector2f & aSizeInPixels)
{
	myRenderData.mySizeInPixels = aSizeInPixels;
}

void StaticSprite::CalculateSizeOfSprite(const CU::Vector4f & aSpriteCutout /*= CU::Vector4f::Zero*/)
{
	if (aSpriteCutout != CU::Vector4f::Zero)
	{
		DL_ASSERT(aSpriteCutout.z > 0.f && aSpriteCutout.w > 0.f, "Sprite does not have width or height");
		myRenderData.mySizeInPixels = { aSpriteCutout.z, aSpriteCutout.w };
		DL_ASSERT(myRenderData.mySizeInPixels != CU::Vector2f::Zero, "Sprite size set to zero");
	}
	else
	{
		myRenderData.mySizeInPixels = { FLOATCAST(GetSprite()->GetImageSize().x), FLOATCAST(GetSprite()->GetImageSize().y) };
		DL_ASSERT(myRenderData.mySizeInPixels != CU::Vector2f::Zero, "Sprite size set to zero");
	}
}

bool StaticSprite::CheckIfSpriteExists(unsigned short & aIndexToSet, const std::string & aPath, const CU::Vector4f & aRect /*= CU::Vector4f::Zero*/)
{
	IndexKey tempKey(aPath, aRect);

	if (ourIndexDictionary.count(tempKey) > 0)
	{
		aIndexToSet = ourIndexDictionary[tempKey];
		return true;
	}

	return false;
}

const RenderData & StaticSprite::GetRenderData() const
{
	return myRenderData;
}
