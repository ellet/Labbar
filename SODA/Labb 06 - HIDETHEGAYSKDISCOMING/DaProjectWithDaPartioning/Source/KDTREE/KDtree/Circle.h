#pragma once
#include <CU/Vectors/vector3.h>
#include <CU/Intersection/Shapes2D.h>
#include <CU/Utility/Randomizer/Randomizer.h>

class StaticSprite;
class PointOfView;
class Randomizer;
struct OctoNode;

class Circle
{
public:
	Circle();
	~Circle();

	void Init(const CU::Vector2f & aPosition, const float aRadius);
	void Draw() const;
	void Update(const CU::Time & aTime);

	void Reset();
	void SetIsSeen();
	void SetLayerChecked();

	bool CollisionTest(const PointOfView & aPointOfView);

	float GetRadius() const;

	const CU::Vector2f & GetPosition() const
	{
		return myCircle.myMainPoint;
	}

	void SetParentNode(OctoNode * aParentNode);
	OctoNode * GetParentNode() const;
	
	const Intersection2D::Circle2D & GetSphere()
	{
		return myCircle;
	}

	void SetColor(const CU::Vector4f & aColor)
	{
		myColor = aColor;
	}

private:

	static CU::Vector2f ourConstraints;
	static Randomizer ourRandomizer;

	CU::Vector4f myColor;

	bool myIsSeen;

	OctoNode * myParentNode;

	Intersection2D::Circle2D myCircle;
	
	StaticSprite * mySprite;
};