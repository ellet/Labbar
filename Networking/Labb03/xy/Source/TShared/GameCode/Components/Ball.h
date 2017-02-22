#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>
#include <GameCode\Components\BaseComponent.h>

namespace DX2D
{
	class CSprite;
}

class CPaddleComponent;

class CBall : public CBaseComponent
{
public:
	CBall();
	~CBall();
	void Render() override;
	void Update(const float aDeltaTime) override;
	void Init();
	void ReverseDirection();
	float GetWidth() const;
	float GetHeight() const;
	void Reset();
	const DX2D::Vector2f& GetPosition() const;

private:
	DX2D::Vector2f myVelocity;
	DX2D::Vector2f mySize;
};


