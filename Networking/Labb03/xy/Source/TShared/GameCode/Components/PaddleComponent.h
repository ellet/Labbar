#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>

#include "GameCode\Components\BaseComponent.h"


namespace Input
{
	class InputWrapper;
}

class CBall;

class CPaddleComponent : public CBaseComponent
{
public:
	CPaddleComponent();
	~CPaddleComponent();
	bool Collides(const CBall& aBall);
	void Update(const float aDeltaTime) override;
	virtual void Render() override;
	void Init();
	void SetPosition(const float aX, const float aY);
	void OnMessage(CComponentMessageBase* aMessage);
	static unsigned int myID;
private:
	void MoveUp(const float aDeltaTime);
	void MoveDown(const float aDeltaTime);
	bool myIsAI;
	DX2D::Vector2f myVelocity;
	DX2D::Vector2f mySize;
};

