#include "stdafx.h"
#include "StaticSprite.h"
#include "tga2d/sprite/sprite.h"
#include "RenderConverter.h"
#include <CU/Utility/Math/Isometric.h>


CU::GrowingArray<DX2D::CSprite*> StaticSprite::ourSprites;
IndexMap StaticSprite::ourIndexDictionary;

StaticSprite::StaticSprite()
{
	myIsInitiedFlag = false;
}

StaticSprite::~StaticSprite()
{
}

void StaticSprite::Init(const std::string & aFilePath/* = "Sprites/trashTestFiles/biggerTestTile.png"*/, const  CU::Vector2f & aPivotAmount /*= CU::Vector2f::Half*/, bool aIsIsometric/* = true*/, const CU::Vector4f & aRect /*= CU::Vector4f::Zero*/)
{
	myIsInitiedFlag = true;
	myImageIndex = AddImage(aFilePath, aPivotAmount, aRect);
	myLayer = enumRenderLayer::eFloor;
	myColor = CU::Vector4f::One;
	myIsIsometricFlag = aIsIsometric;
	myRotation = 0.f;
}

unsigned short StaticSprite::AddImage(const std::string & aFilePath, const  CU::Vector2f & aPivotAmount, const CU::Vector4f & aRect /*= CU::Vector4f::One*/)
{
	IndexKey tempKey(aFilePath, aRect);

	if (ourIndexDictionary.count(tempKey) > 0)
	{
		unsigned short tempIndex = ourIndexDictionary[tempKey];
		return tempIndex;
	}

	ourSprites.Add(new DX2D::CSprite(aFilePath.c_str()));
	DX2D::CSprite * tempSprite = ourSprites.GetLast();
	

	if (aRect != CU::Vector4f::Zero)
	{
		const float spriteWidth = static_cast<float>(tempSprite->GetImageSize().x);
		const float spriteHeight = static_cast<float>(tempSprite->GetImageSize().y);

		const float TempStartPointX = aRect.x / spriteWidth;
		const float TempStartPointY = aRect.y / spriteHeight;

		const float TempWidth = aRect.Width / spriteWidth;
		const float TempHeight = aRect.Height / spriteHeight;

		const float TempEndPointX = TempStartPointX + TempWidth;
		const float TempEndPointY = TempStartPointY + TempHeight;

		tempSprite->SetTextureRect(TempStartPointX, TempStartPointY, TempEndPointX, TempEndPointY);
		tempSprite->SetSize(DX2D::Vector2f(tempSprite->GetSize().x * TempWidth, tempSprite->GetSize().y * TempHeight));
	}
	tempSprite->SetPivot(DX2D::Vector2f(aPivotAmount.x, aPivotAmount.y));

	ourIndexDictionary[tempKey] = (ourSprites.Size() - 1);
	return ourIndexDictionary[tempKey];
}



void StaticSprite::Draw(const CU::Vector2f & aPosition)
{
	DL_ASSERT(myIsInitiedFlag == true, "Static sprite not initialized");

	if (myIsIsometricFlag == true)
	{
		RenderConverter::CalculateAndRenderIso(*this, aPosition - myPositionOffset);
	}
	else
	{
		RenderConverter::CalculateAndRenderSprite(*this, aPosition);
	}
}


void StaticSprite::SetPivotWithPixels(const CU::Vector2f & aPivotOffsetInPixel)
{
	myPositionOffset = aPivotOffsetInPixel;
	//CU::Vector2f tempOffset = aPivotOffsetInPixel;
	//tempOffset.y = -tempOffset.y;

	//myPositionOffset = //CU::PixelToIsometric(tempOffset);
}

void StaticSprite::SetRotation(const float aRotation)
{
	myRotation = aRotation;
}