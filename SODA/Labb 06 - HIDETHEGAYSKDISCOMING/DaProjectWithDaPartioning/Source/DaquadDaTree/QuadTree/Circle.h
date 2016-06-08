#pragma once
#include <CU/Vectors/vector3.h>
#include <CU/Intersection/Shapes.h>
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

	void Init(const CU::Vector3f & aPosition, const float aRadius);
	void Draw() const;
	void Update(const CU::Time & aTime);

	void Reset();
	void SetIsSeen();

	bool CollisionTest(const PointOfView & aPointOfView);

	float GetRadius() const;

	const CU::Vector3f & GetPosition() const
	{
		return mySphere.myCenterPosition;
	}

	void SetParentNode(OctoNode * aParentNode);
	OctoNode * GetParentNode() const;
	
	const Intersection3D::Sphere & GetSphere()
	{
		return mySphere;
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

	Intersection3D::Sphere mySphere;
	
	StaticSprite * mySprite;
};