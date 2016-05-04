#pragma once
#include <GrowingArray\GrowingArray.h>
#include "../Object/Object.h"
#include "../Levels/Border.h"
#include <RendererManager/Text/TextRenderer.h>

namespace std
{
	class fwd_string; // instead of #include <string>
}


namespace DX2D
{
	class CSprite;
}

class Level
{
public:
	Level();
	~Level();
	void Update(float aDeltaTime);
	void Draw();
	bool Init(CommonUtilities::GrowingArray<Object*> & aGameObjects, CommonUtilities::GrowingArray<Border> & aBorderList,
		const char* aPathToBackgroundImage, const std::string &aLevelName,
		bool aIsCurrentLevel, Vector2f &aPlayerStartPosition, std::string &aBackgroundSoundName);
	void SetIsCurrentLevel(bool aIsCurrentLevel);
	CommonUtilities::GrowingArray<Border> GetBorderList();
	bool GetIsCurrentLevel();
	const Vector2f& GetPlayerStartPosition();
	std::string& GetMyLevelName();

	float GetDistance(const Vector2f aPosition1, const Vector2f aPosition2);
	bool IsNearBorder(Border aBorder, Vector2f aPlayerPositionVector);
	void EditNodes(const Vector2f aMousePosition);
	void DrawPole();
	void SplitNodes(const Vector2f aMousePosition);
	void SetEditMode();
	bool IsCurrentlyEditing();
	void UserClickedBorder(bool aMouseIsDown, Vector2f aMousePosition);
	const std::string &GetBackgroundSoundName();

	inline void SetScaleValues(const float aTopY, const float aTopScale, const float aBottomY, const float aBottomScale);
	inline float GetScaleSlope() const;
	inline float GetScaleConstant() const;
	
private:
	BaseGameObject myBackgroundImage;
	std::string myLevelName;
	std::string myBackgroundSoundName;
	CommonUtilities::GrowingArray<Object*> myGameObjects;
	CommonUtilities::GrowingArray<Border> myBorderList;
	Vector2f myPlayerStartPosition;
	bool myIsCurrentLevel;
	bool myEditIsActive;

	float myScaleSlope;
	float myScaleConstant;

	TextRenderer myTextRenderer;

	BaseGameObject tempImageForReview;
	
};

inline void Level::SetScaleValues(const float aTopY, const float aTopScale, const float aBottomY, const float aBottomScale)
{

	myScaleSlope = (aBottomScale - aTopScale) / (aBottomY - aTopY);

	myScaleConstant = aTopScale - myScaleSlope * aTopY;

}
inline float Level::GetScaleSlope() const
{
	return myScaleSlope;
}
inline float Level::GetScaleConstant() const
{
	return myScaleConstant;
}
