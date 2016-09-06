#include "stdafx.h"
#include "RenderCommand.h"
#include <tga2d\math\vector2.h>

namespace HUG
{

	RenderCommand::RenderCommand()
	{
	}


	RenderCommand::RenderCommand(Tga2D::CSprite * aSprite, const SpriteData & aSpriteData, const CU::Vector2f & aPosition) : mySprite(aSprite),
	myPosition(aPosition), mySpriteData(aSpriteData)
	{
	}

	RenderCommand::~RenderCommand()
	{
	}

	void RenderCommand::Render()
	{
		Tga2D::Vector2f tempSize = mySprite->GetSize();

		Tga2D::Vector2f position(myPosition.x, myPosition.y);
		Tga2D::Vector2f pivot(mySpriteData.myPivot.x, mySpriteData.myPivot.y);
		Tga2D::Vector2f SpriteSize(mySprite->GetSize().x * mySpriteData.mySize.x, mySprite->GetSize().y * mySpriteData.mySize.y);

		mySprite->SetPosition(position);
		mySprite->SetPivot(pivot);
		mySprite->SetRotation(mySpriteData.myRotationInRadians);
		mySprite->SetSize(SpriteSize);
		mySprite->Render();

		mySprite->SetSize(tempSize);
	}

}