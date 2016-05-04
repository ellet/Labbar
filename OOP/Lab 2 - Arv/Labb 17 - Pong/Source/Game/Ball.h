#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>
#include "GameObject.h"


class Paddle;

class Ball : public GameObject
{
public:
	Ball();
	~Ball();
	void Update(const float aDeltaTime) override;
	void Init();
	void ReverseDirection();
	float GetWidth() const;
	float GetHeight() const;
	void Reset();
	

private:
	DX2D::Vector2f myVelocity;
};


