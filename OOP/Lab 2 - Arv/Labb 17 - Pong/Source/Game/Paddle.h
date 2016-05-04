#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>
#include "GameObject.h"

namespace DX2D
{
	class CSprite;
}

class Ball;

class Paddle : public GameObject
{
public:
	Paddle();
	~Paddle();
	bool Collides(const Ball& aBall);
	
	void Update(const float aDeltaTime) override;
	void Init(bool aMakeAI, Ball& aBall);

private:	
	bool myIsAI;
	Ball * myBallPointer;
};

