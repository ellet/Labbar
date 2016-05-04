#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>

namespace DX2D
{
	class CSprite;
}

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void BaseUpdate(const float aDeltaTime);
	virtual void BaseInit(const char * aSpritePath, const float aSpeed);
	virtual void Draw();
	inline void SetPosition(const float aX, const float aY);

	inline const DX2D::Vector2f& GetPosition() const;

	virtual void Update(float aDeltaTime) = 0;

protected:
	virtual void MoveUp(const float aDeltaTime);
	virtual void MoveDown(const float aDeltaTime);
	DX2D::Vector2f myPosition;
	DX2D::CSprite *mySprite;

private:
	float mySpeed;	
	
};

void GameObject::SetPosition(const float aX, const float aY)
{
	myPosition.Set(aX, aY);
}

const DX2D::Vector2f& GameObject::GetPosition() const
{
	return myPosition;
}