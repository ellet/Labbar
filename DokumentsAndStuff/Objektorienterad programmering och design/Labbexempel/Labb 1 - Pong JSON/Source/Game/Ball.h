#pragma once
#include <..\DX2DEngine\tga2d\math\vector2.h>
#include "picojson.h"

namespace DX2D
{
	class CSprite;
}

namespace tinyxml2
{
	class XMLElement;
}

class Paddle;

class Ball
{
public:
	Ball();
	~Ball();
	void Draw();
	void Update(const float aDeltaTime);
	void Init(const picojson::value::object &aJSONObject);
	void ReverseDirection();
	float GetWidth() const;
	float GetHeight() const;
	void Reset();
	inline const DX2D::Vector2f& GetPosition() const;

private:
	DX2D::Vector2f myPosition;
	DX2D::Vector2f myVelocity;
	DX2D::CSprite *mySprite;
	float myBallStartSpeed;
	float myBallAcceleration;
};

const DX2D::Vector2f& Ball::GetPosition() const
{
	return myPosition;
}


