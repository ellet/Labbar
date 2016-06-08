#pragma once

class StaticSprite;

class PointOfView
{
public:
	PointOfView();
	~PointOfView();

	void Init();

	void Update(const CU::Time & aDeltaTime);

	void Draw() const;

	void SetPointOfView(const CU::Vector2f & aStartPosition, const CU::Vector2f & aEndPosition);
	const CU::Vector2f & GetPosition() const;

	const Intersection2D::Triangle & GetTriangle() const;

private:
	float myRotation;
	CU::Vector2f myPosition;
	CU::Vector2f myPositionEnd;
	CU::Vector2f myBPosition;
	CU::Vector2f myCPosition;
	Intersection2D::Triangle myFOV;
	

	StaticSprite * mySprite;
};