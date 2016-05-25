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
	const CU::Vector2f & GetPosition() const;

	void SetRotation(const float aRotation);
	const float GetRotation() const;

	const Intersection2D::Circle2D & GetCircle() const
	{
		return myCircle;
	}

private:
	float myRotation;

	Intersection2D::Circle2D myCircle;

	StaticSprite * mySprite;
};