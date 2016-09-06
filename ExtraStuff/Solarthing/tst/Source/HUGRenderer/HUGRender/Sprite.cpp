#include "stdafx.h"
#include "Sprite.h"
#include "Renderer.h"

namespace HUG
{

	Sprite::Sprite()
	{
	}


	Sprite::~Sprite()
	{
	}

	void Sprite::Init(const std::string & aFilepath)
	{
		myIndex = GET_RENDERER.CreateSprite(aFilepath);
	}

	void Sprite::Draw(const CU::Vector2f & aPosition) const
	{
		GET_RENDERER.AddSpriteToRender(myIndex, mySpriteData, aPosition);
	}

	void Sprite::SetPivot(const CU::Vector2f & aPivotPosition)
	{
		mySpriteData.myPivot = aPivotPosition;
	}

	void Sprite::SetRotationDegrees(const float aRotationInDegrees)
	{
		mySpriteData.myRotationInRadians = DEGRESS_TO_RADIANSF(aRotationInDegrees);
	}

	void Sprite::SetRotationRadians(const float aRotationInRadians)
	{
		mySpriteData.myRotationInRadians = aRotationInRadians;
	}

	void Sprite::SetSize(const float aSize)
	{
		mySpriteData.mySize = { aSize, aSize };
	}

	unsigned short Sprite::GetIndex() const
	{
		return myIndex;
	}

}