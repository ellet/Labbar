#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>
#include "picojson.h"

namespace DX2D
{
	class CSprite;
}

namespace Input
{
	class InputWrapper;
}

class Ball;

class Paddle
{
public:
	Paddle();
	~Paddle();
	bool Collides(const Ball& aBall);
	void Draw();
	void Update(const float aDeltaTime, const Input::InputWrapper& aInputWrapper, const Ball& aBall);
	void Init(const picojson::value::object &aJSONObject, bool aMakeAI);
	void SetPosition(const float aX, const float aY);

private:
	void MoveUp(const float aDeltaTime);
	void MoveDown(const float aDeltaTime);
	bool myIsAI;
	float myPaddleSpeed;
	DX2D::Vector2f myPosition;
	DX2D::CSprite *mySprite;
};

