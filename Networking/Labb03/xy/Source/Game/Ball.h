#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>

namespace DX2D
{
	class CSprite;
}

class CPaddleComponent;

class CBall
{
public:
	CBall();
	~CBall();
	void Render();
	void Update(const float aDeltaTime);
	void Init();
	void ReverseDirection();
	float GetWidth() const;
	float GetHeight() const;
	void Reset();
	inline const DX2D::Vector2f& GetPosition() const;

private:
	DX2D::Vector2f myPosition;
	DX2D::Vector2f myVelocity;
	DX2D::CSprite *mySprite;
};

const DX2D::Vector2f& CBall::GetPosition() const
{
	return myPosition;
}


