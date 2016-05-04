#pragma once
#include <tga2d/math/vector2.h>
#include <vector>
#include <tga2d/sprite/sprite.h>

//namespace DX2D
//{
//	class CSprite;
//}

enum class enumGameObjects
{
	eBall,
	eFirstPaddle,
	eSecondPadde,
	enumLength
};

struct CollisionRectangle
{
	DX2D::Vector2f myTopLeft;
	DX2D::Vector2f myBottomRight;
	
};

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init(const char* aTexturePath, enumGameObjects aType, const bool aRenderTexture = false);

	void SetMovement(float aDirection, float aSpeed = 0.003f, bool aTrueSet = false);

	void SetPosition(float aXPosition, float aYPosition);
	void SetScale(float aXScale, float aYScale);
	void SetSizeOfChild(DX2D::CSprite & aSprite);
	

	DX2D::Vector2f GetScale() const;
	DX2D::CSprite & GetMySprite() const;



	void Draw();

	
	inline const DX2D::Vector2f & GetPostion() const;
	inline const CollisionRectangle & GetCollisionRectangle() const;
	inline void SetUseFriciton(bool const aUseFriction);
	inline void SetClampToScreen(bool const aCanGoOutsideScreen);

	void CheckCollision(const CollisionRectangle & aRectangle);

	void DoCollision();

	void Update(float aDeltaTime);

private:
	inline void AddDirection(float aDirection);
	inline void SetCollisionBox();

	void SetDirectionFromAngleSpeeds();
	void Bounce();

	bool myIUseFriction;
	bool myICanGoOutside;
	bool myIShouldRender;

	float GetXSpeed();
	float GetYSpeed();

	float mySpeed;
	float myXSpeed;
	float myYSpeed;
	float myDirection;

	CollisionRectangle myCollisionRectangle;
	DX2D::Vector2f myPreviousPosition;
	DX2D::Vector2f myScale;


	float myFriction;

	float myMaxSpeed;

	float myHeight;
	float myWidth;

	DX2D::CSprite* myObject;
	
	enumGameObjects myType;
};


const CollisionRectangle & GameObject::GetCollisionRectangle() const
{
	return myCollisionRectangle;
}

const DX2D::Vector2f & GameObject::GetPostion() const
{
	return myObject->GetPosition();
}

void GameObject::AddDirection(float aDirection)
{
	myDirection += aDirection;

	if (myDirection >= 360.f)
	{
		myDirection -= 360.f;
	}
}

void GameObject::SetUseFriciton(bool const aUseFriction)
{
	myIUseFriction = aUseFriction;
}

void GameObject::SetClampToScreen(bool const aCanGoOutsideScreen)
{
	myICanGoOutside = aCanGoOutsideScreen;
}

void GameObject::SetCollisionBox()
{
	myCollisionRectangle.myTopLeft = myObject->GetPosition();
	myCollisionRectangle.myBottomRight.x = myCollisionRectangle.myTopLeft.x + myWidth;
	myCollisionRectangle.myBottomRight.y = myCollisionRectangle.myTopLeft.y + myHeight;
}

