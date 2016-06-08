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

	void SetPosition(const CU::Vector2f & aPosition);
	const CU::Vector2f & GetPosition() const;

	void SetRotation(const CU::Vector3f & aRotation);
	const CU::Vector3f & GetRotation() const;

	const Intersection3D::Fov90Frustum & GetFrustum() const
	{
		return myFrustum;
	}

	/*const Intersection3D::AABB GetAABB() const
	{
		Intersection3D::AABB tempBox;
	}*/

	Intersection3D::Sphere GetSphere() const
	{
		Intersection3D::Sphere tempCircle;

		tempCircle.myCenterPosition = myPosition;
		tempCircle.myRadius = 130.f;
		tempCircle.myRadiusSquared = tempCircle.myRadius * tempCircle.myRadius;

		return tempCircle;
	}

private:
	void DrawFrustum() const;
	CU::Vector3f myRotation;
	CU::Vector3f myPosition;
	Intersection3D::Fov90Frustum myFrustum;

	StaticSprite * mySprite;
};