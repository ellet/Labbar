#pragma once

class StaticSprite;
class PointOfView;

class Circle
{
public:
	Circle();
	~Circle();

	void Init(const CU::Vector2f & aPosition);
	void Draw() const;

	void Reset();
	void SetIsSeen();

	bool CollisionTest(const PointOfView & aPointOfView);
	bool CollisionTestRay(const Intersection2D::LineSegment2D & aRay);

	const CU::Vector2f & GetPosition()
	{
		return myCircle.myMainPoint;
	}

private:
	bool myIsSeen;
	//CU::Vector2f myPosition;
	Intersection2D::Circle2D myCircle;
	
	StaticSprite * mySprite;
public:
	void Update();
};