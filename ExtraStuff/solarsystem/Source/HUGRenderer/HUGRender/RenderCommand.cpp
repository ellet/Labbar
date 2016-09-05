#include "stdafx.h"
#include "RenderCommand.h"


namespace HUG
{

	RenderCommand::RenderCommand()
	{
	}


	RenderCommand::RenderCommand(DX2D::CSprite * aSprite, const SpriteData & aSpriteData, const CU::Vector2f & aPosition) : mySprite(aSprite),
	myPosition(aPosition), mySpriteData(aSpriteData)
	{
	}

	RenderCommand::~RenderCommand()
	{
	}

	void RenderCommand::Render()
	{
		DX2D::Vector2f tempSize = mySprite->GetSize();

		DX2D::Vector2f position(myPosition.x, myPosition.y);
		DX2D::Vector2f pivot(mySpriteData.myPivot.x, mySpriteData.myPivot.y);
		DX2D::Vector2f SpriteSize(mySprite->GetSize().x * mySpriteData.mySize.x, mySprite->GetSize().y * mySpriteData.mySize.y);

		mySprite->SetPosition(position);
		mySprite->SetPivot(pivot);
		mySprite->SetRotation(mySpriteData.myRotationInRadians);
		mySprite->SetSize(SpriteSize);
		mySprite->Render();

		mySprite->SetSize(tempSize);
	}

}