#pragma once
#include <BaseClasses/BaseGameObject/BaseAnimatedObject/BaseAnimatedGameObject.h>
#include "../Levels/Border.h"
#include <../CommonUtilities/GrowingArray/GrowingArray.h>
#include <tga2d\sprite\sprite.h>
#include "../Inventory/Inventory.h"
#include "../Object/Object.h"

class Player : public Object
{
public:
	Player();
	void Init(CommonUtilities::GrowingArray<Border> aBorderList);
	void SetGotoPosition(Vector2f aGotoPosition);
	void ResetGoto();
	void UpdateBorders(CommonUtilities::GrowingArray<Border> aBorderList);
	bool BorderIntersect(const Border &aBorder, const Vector2f &aStartPoint, const Vector2f &anEndPoint, Vector2f &anIntersectionPoint);
	void FindPath(const float aDeltaTime);
	void PathFinding();
	void Update(const float aDeltaTime) override;
	void SetSpeed(float aSpeed);
	float GetDistance(Vector2f aPosition1, Vector2f aPosition2);
	~Player();

	inline void SetPlayerScaleValues(const float aSlope, const float aConstant);

private:
	Vector2f myVelocity;
	Vector2f myPosition;
	Vector2f myGotoPosition;
	float mySpeed;
	float myDeltaTime;	
	CommonUtilities::GrowingArray<Border> myBordersToCheck;
	CommonUtilities::GrowingArray<Vector2f> myWayPoints;

	float myScaleSlope;
	float myScaleConstant;

	SIZE_T myAnimationDirection;

};

inline void Player::SetPlayerScaleValues(const float aSlope, const float aConstant)
{
	myScaleSlope = aSlope;
	myScaleConstant = aConstant;
}
