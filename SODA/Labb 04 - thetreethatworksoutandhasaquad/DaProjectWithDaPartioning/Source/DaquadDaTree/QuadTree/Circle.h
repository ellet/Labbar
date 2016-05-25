#pragma once

#include <CU/Utility/Randomizer/Randomizer.h>

class StaticSprite;
class PointOfView;
class Randomizer;
struct QuadNode;

class Circle
{
public:
	Circle();
	~Circle();

	void Init(const CU::Vector2f & aPosition);
	void Draw() const;
	void Update(const CU::Time & aTime);

	void Reset();
	void SetIsSeen();

	bool CollisionTest(const PointOfView & aPointOfView);
	bool CollisionTestRay(const Intersection2D::LineSegment2D & aRay);

	float GetRadius() const;

	const CU::Vector2f & GetPosition() const
	{
		return myCircle.myMainPoint;
	}

	void SetParentNode(QuadNode * aParentNode);
	QuadNode * GetParentNode() const;
	
private:
	void MoveBall(const CU::Vector2f & aDelta);

	static CU::Vector2f ourConstraints;
	static Randomizer ourRandomizer;

	CU::Vector2f myDirection;

	bool myIsSeen;
	//CU::Vector2f myPosition;

	QuadNode * myParentNode;

	Intersection2D::Circle2D myCircle;
	
	StaticSprite * mySprite;
};