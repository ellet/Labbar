#include "BaseAnimatedGameObject.h"

#include "..\..\..\RendererManager\RenderManager.h"

#include <tga2d/drawers/debug_drawer.h>

BaseAnimatedGameObject::BaseAnimatedGameObject()
	:myCurrentFrame(0), myPlayingAnimation(nullptr), myLeftoverDeltaTime(0.f), myDefaultAnimation(""), mySpriteData(1)
{
}
BaseAnimatedGameObject::~BaseAnimatedGameObject()
{
}

void BaseAnimatedGameObject::Update(const float aDeltaTime)
{

	if (myPlayingAnimation == nullptr)
	{
		return;
	}

	if (myPlayingAnimation->myLoop == false && myCurrentFrame > myPlayingAnimation->myEndFrame - myPlayingAnimation->myStartFrame)
	{
		return;
	}

	myLeftoverDeltaTime += aDeltaTime;

	if (myLeftoverDeltaTime >= myPlayingAnimation->myDisplayTime)
	{

		myLeftoverDeltaTime = 0;

		++myCurrentFrame;
		if (myCurrentFrame > myPlayingAnimation->myEndFrame - myPlayingAnimation->myStartFrame)
		{
			if (myPlayingAnimation->myLoop == true)
			{
				myCurrentFrame = 0;
			}
			else
			{
				if (myDefaultAnimation != "")
				{
					PlayAnimtaion(myDefaultAnimation);
				}
				return;
			}
		}

	}

}
void BaseAnimatedGameObject::Draw() const
{
	if (myIsActive == true)
	{
		if (myPlayingAnimation == nullptr)
		{
			return;
		}

		const float frameWidth = 1.f / myPlayingAnimation->mySpriteData->myColumns;
		const float frameHeight = 1.f / myPlayingAnimation->mySpriteData->myRows;

		unsigned short frameIndex = 0;
		if (myPlayingAnimation != nullptr)
		{
			frameIndex = myPlayingAnimation->myStartFrame + myCurrentFrame;
		}

		const float frameX = frameWidth * (frameIndex % myPlayingAnimation->mySpriteData->myColumns);
		const float frameY = frameHeight * (frameIndex / myPlayingAnimation->mySpriteData->myColumns);

		RenderManager::AddRenderCommand(RenderCommand(myPlayingAnimation->mySpriteData->mySprite.get(), GetPosition(), Vector2f(GetSize().x / myPlayingAnimation->mySpriteData->myColumns, GetSize().y / myPlayingAnimation->mySpriteData->myRows), GetPivot(), GetRotation(), GetColor(), Vector4f(frameX, frameY, frameX + frameWidth, frameY + frameHeight)), myRenderPriority);
	}

	

}

void BaseAnimatedGameObject::PlayAnimtaion(const std::string &anAnimationID)
{
	if (myPlayingAnimation != &myAnimations.at(anAnimationID))
	{
		ResetAnimation();
		myPlayingAnimation = &myAnimations[anAnimationID];
	}
}
void BaseAnimatedGameObject::StopAnimation()
{
	if (myDefaultAnimation != "")
	{
		PlayAnimtaion(myDefaultAnimation);
	}
}
void BaseAnimatedGameObject::ResetAnimation()
{
	myCurrentFrame = 0;
	myLeftoverDeltaTime = 0.f;
}
