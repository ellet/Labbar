#pragma once

class StaticSprite;

class PointOfView
{
public:
	PointOfView();
	~PointOfView();

	void Init();

	void Update();

	void Draw() const;

	void SetPosition(const CU::Vector2f & aPosition);

	const Intersection2D::Circle2D & GetCircle() const
	{
		return myCircle;
	}

private:
	Intersection2D::Circle2D myCircle;

	StaticSprite * mySprite;
};