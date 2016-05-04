#include "stdafx.h"
#include "GameObject.h"

#include <math.h>
#include <cmath>

#include <tga2d/Engine.h>
#include <tga2d/math/vector2.h>

#include <tga2d/sprite/sprite.h>

#include <Macros.h>
#include <vector>



GameObject::GameObject()
{
	myObject = nullptr;
}


GameObject::~GameObject()
{
	SAFE_DELETE(myObject);
}

void GameObject::Init(const char* aTexturePath, enumGameObjects aType, const bool aRenderTexture)
{
	myObject = new DX2D::CSprite(aTexturePath);
	myObject->SetPosition(DX2D::Vector2f(0.f, 0.f));
	
	//myHeight = myObject->GetSize().y;
	//myWidth = myObject->GetSize().x;// *DX2D::CEngine::GetInstance()->GetWindowRatioInversed();

	SetCollisionBox();

	mySpeed = 0;
	myXSpeed = 0;
	myYSpeed = 0;
	myDirection = 0;

	myMaxSpeed = 0.75f;
	myFriction = 0.2f;

	myIUseFriction = true;
	myICanGoOutside = false;
	myIShouldRender = aRenderTexture;

	myType = aType;

	SetScale();
}

void GameObject::Draw()
{
	if (myIShouldRender == true)
	{
		myObject->Render();
	}
}

void GameObject::Update(float aDeltaTime)
{
	if (mySpeed > 0)
	{
		DX2D::Vector2f position = myObject->GetPosition();
		position.x += myXSpeed * aDeltaTime;
		position.y += -myYSpeed * aDeltaTime;


		mySpeed = CLAMP(mySpeed, 0.0f, myMaxSpeed);
		SetPosition(position.x, position.y);

		SetCollisionBox();

		if (myIUseFriction == true)
		{
			const float TempFriction = myFriction * aDeltaTime;
			if (mySpeed > mySpeed - TempFriction)
			{
				mySpeed = mySpeed - TempFriction;
			}
			else
			{
				mySpeed = 0;
			}
		}
	}
}

void GameObject::Bounce()
{
	myYSpeed = -myYSpeed;
	SetDirectionFromAngleSpeeds();
	myObject->SetPosition(myPreviousPosition);
}

bool GameObject::CheckCollision(const CollisionRectangle & aRectangle)
{
	/*if ((myCollisionRectangle.myTopLeft.x >= aRectangle.myTopLeft.x 
		&& myCollisionRectangle.myTopLeft.x <= aRectangle.myBottomRight.x)
		&& (myCollisionRectangle.myTopLeft.y >= aRectangle.myTopLeft.y 
		&& myCollisionRectangle.myTopLeft.y <= aRectangle.myBottomRight.y))*/
	if (myCollisionRectangle.myTopLeft.x > aRectangle.myBottomRight.x)
	{
		return false;
	}

	if (myCollisionRectangle.myBottomRight.x < aRectangle.myTopLeft.x)
	{
		return false;
	}

	if (myCollisionRectangle.myBottomRight.y < aRectangle.myTopLeft.y)
	{
		return false;
	}

	if (myCollisionRectangle.myTopLeft.y > aRectangle.myBottomRight.y)
	{
		return false;
	}

	{
		DoCollision();
		return true;
	}
}

void GameObject::DoCollision()
{
	myXSpeed = -myXSpeed;
	SetDirectionFromAngleSpeeds();
	myObject->SetPosition(myPreviousPosition);
}

void GameObject::SetPosition(float aXPosition, float aYPosition)
{
	if (myICanGoOutside == false)
	{
		aXPosition = CLAMP(1.0f -myWidth, 0.0f, aXPosition);
		aYPosition = CLAMP(1.0f -myHeight, 0.0f, aYPosition);
	}
	else
	{
		if (aYPosition > (1.f - myHeight) || aYPosition < 0.f)
		{
			Bounce();
		}
	}

	myPreviousPosition = myObject->GetPosition();
	myObject->SetPosition(DX2D::Vector2f(aXPosition, aYPosition));
}

void GameObject::SetScale()
{
	DX2D::Vector2ui windowSize = DX2D::CEngine::GetInstance()->GetRenderSize();
	DX2D::Vector2ui spriteSize = myObject->GetImageSize();

	DX2D::Vector2f windowSizef(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
	DX2D::Vector2f spriteSizef(static_cast<float>(spriteSize.x), static_cast<float>(spriteSize.y));

	myScale = DX2D::Vector2f((spriteSizef.x / windowSizef.x) * 1.f, (spriteSizef.y / windowSizef.y) * 1.f);
	myHeight = myScale.y;
	myWidth = myScale.x;

	//myObject->SetSize(myScale);	
}

DX2D::Vector2f GameObject::GetScale() const
{
	return myScale;
}

DX2D::CSprite& GameObject::GetMySprite() const
{
	return (*myObject);
}

void GameObject::SetSizeOfChild(DX2D::CSprite & aSprite)
{
	DX2D::Vector2ui worldSize = myObject->GetImageSize();
	DX2D::Vector2ui spriteSize = aSprite.GetImageSize();

	DX2D::Vector2f worldSizef(static_cast<float>(worldSize.x), static_cast<float>(worldSize.y));
	DX2D::Vector2f spriteSizef(static_cast<float>(spriteSize.x), static_cast<float>(spriteSize.y));

	DX2D::Vector2f sizeOfChild(((worldSizef.x / spriteSizef.x) * myScale.x), ((worldSizef.y / spriteSizef.y) * myScale.y));

	aSprite.SetSize(sizeOfChild);
}

void GameObject::SetMovement(float aDirection, float aSpeed, bool aTrueSet)
{
	if (aDirection != myDirection)
	{
		if ((mySpeed - aSpeed) > 0)
		{
			aDirection = myDirection;
			aSpeed = -aSpeed;
		}
	}

	if (aTrueSet == true)
	{
		mySpeed = aSpeed;
	}
	else
	{
		mySpeed += aSpeed;
	}

	myDirection = aDirection;

	myXSpeed = GetXSpeed();
	myYSpeed = GetYSpeed();

	mySpeed = CLAMP(mySpeed, 0.0f, myMaxSpeed);
}



void GameObject::SetDirectionFromAngleSpeeds()
{
	const float TempDegressInRadians = std::sinhf(myYSpeed / myXSpeed);
	myDirection = RADIANS_TO_DEGRESSF(TempDegressInRadians);
	AddDirection(0);
}


float GameObject::GetXSpeed()
{
	return std::cos(DEGRESS_TO_RADIANSF(myDirection)) * mySpeed;
}

float GameObject::GetYSpeed()
{
	return std::sin(DEGRESS_TO_RADIANSF(myDirection)) * mySpeed;
}