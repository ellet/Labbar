#include "BaseAnimatedGameObject.h"

#include "..\..\..\RendererManager\RenderManager.h"

BaseAnimatedGameObject::BaseAnimatedGameObject()
{
	
	myColumns = 1;
	myRows = 1;

	myCurrentAnimation = 0;
	myCurrentFrame = 0;
	myAnimations.Init(2);
	
	myLeftoverDeltaTime = 0.f;

}
BaseAnimatedGameObject::~BaseAnimatedGameObject()
{
}

void BaseAnimatedGameObject::Update(const float aDeltaTime)
{

	float deltaTime = aDeltaTime + myLeftoverDeltaTime;

	while (deltaTime >= myAnimations[myCurrentAnimation].GetDisplayTime())
	{

		deltaTime -= myAnimations[myCurrentAnimation].GetDisplayTime();
		
		++myCurrentFrame;
		if (myCurrentFrame >= myAnimations[myCurrentAnimation].GetFrameCount())
		{
			myCurrentFrame = 0;
		}

	}
	myLeftoverDeltaTime = deltaTime;

}
void BaseAnimatedGameObject::Draw() const
{
	
	const float frameWidth = 1.f / myColumns;
	const float frameHeight = 1.f / myRows;

	const unsigned short frameIndex = myAnimations[myCurrentAnimation].GetFirstFrame() + myCurrentFrame;

	const float frameX = frameWidth * (frameIndex % myColumns);
	const float frameY = frameHeight * (frameIndex / myColumns);

	RenderManager::AddRenderCommand(RenderCommand(GetSprite(), GetPosition(), Vector2f(GetSize().x / GetColumns(), GetSize().y / GetRows()), GetPivot(), GetRotation(), GetColor(), Vector4f(frameX, frameY, frameX + frameWidth, frameY + frameHeight)));

}

BaseAnimatedGameObject::AnimationHandle BaseAnimatedGameObject::AddAnimation()
{
	return AddAnimation(Animation());
}
BaseAnimatedGameObject::AnimationHandle BaseAnimatedGameObject::AddAnimation(const Animation &anAnimation)
{
	myAnimations.Add(anAnimation);
	return myAnimations.Size() - 1;
}
void BaseAnimatedGameObject::PlayAnimtaion(const AnimationHandle anAnimationHandle)
{
	if (myCurrentAnimation != anAnimationHandle)
	{
		ResetAnimation();
		myCurrentAnimation = anAnimationHandle;
	}
}
void BaseAnimatedGameObject::ResetAnimation()
{
	myCurrentFrame = 0;
	myLeftoverDeltaTime = 0.f;
}
