#pragma once

#include <string>
#include <memory>
#include <map>

#include <GrowingArray/GrowingArray.h>

#include "..\BaseGameObject.h"

class BaseAnimatedGameObject : public BaseGameObject
{
public:

	BaseAnimatedGameObject();
	virtual ~BaseAnimatedGameObject();

	virtual void Update(const float aDeltaTime) override;
	virtual void Draw() const override;

	inline void SetDefaultAnimation(const std::string &anAnimationID);

	inline unsigned short AddSpriteData(std::shared_ptr<DX2D::CSprite> aSprite, const unsigned short aColumns, const unsigned short aRows);
	inline void AddAnimation(
		const std::string &anAnimationID, const float aDisplayTime, const unsigned short aStartFrame,
		const unsigned short anEndFrame, const bool aLoop, const unsigned short anSpriteDataIndex
		);
	inline void AddSimpleAnimation(std::shared_ptr<DX2D::CSprite> aSprite);

	void PlayAnimtaion(const std::string &anAnimationID);
	void StopAnimation();
	void ResetAnimation();

private:

	struct SpriteData
	{
		std::shared_ptr<DX2D::CSprite> mySprite;
		unsigned short myColumns;
		unsigned short myRows;
	};

	struct Animation
	{
		SpriteData *mySpriteData;
		float myDisplayTime;
		unsigned short myStartFrame;
		unsigned short myEndFrame;
		bool myLoop;
	};

	std::string myDefaultAnimation;
	std::map<std::string, Animation> myAnimations;
	CommonUtilities::GrowingArray<std::shared_ptr<SpriteData>> mySpriteData;

	Animation *myPlayingAnimation;
	unsigned short myCurrentFrame;
	float myLeftoverDeltaTime;

};

inline void BaseAnimatedGameObject::SetDefaultAnimation(const std::string &anAnimationID)
{
	myDefaultAnimation = anAnimationID;
	if (myPlayingAnimation == nullptr)
	{
		PlayAnimtaion(myDefaultAnimation);
	}
}

inline unsigned short BaseAnimatedGameObject::AddSpriteData(std::shared_ptr<DX2D::CSprite> aSprite, const unsigned short aColumns, const unsigned short aRows)
{
	mySpriteData.Add(std::make_shared<SpriteData>(SpriteData({ aSprite, aColumns, aRows })));
	return mySpriteData.Size() - 1;
}
inline void BaseAnimatedGameObject::AddAnimation(
	const std::string &anAnimationID, const float aDisplayTime, const unsigned short aStartFrame,
	const unsigned short anEndFrame, const bool aLoop, const unsigned short anSpriteDataIndex
	)
{

	ResetAnimation();

	myAnimations[anAnimationID] = { mySpriteData[anSpriteDataIndex].get(), aDisplayTime, aStartFrame, anEndFrame, aLoop };

	if (myDefaultAnimation != "")
	{
		PlayAnimtaion(myDefaultAnimation);
	}
	else
	{
		PlayAnimtaion(anAnimationID);
	}

}
inline void BaseAnimatedGameObject::AddSimpleAnimation(std::shared_ptr<DX2D::CSprite> aSprite)
{
	AddAnimation("default", 0.f, 0, 0, false, AddSpriteData(aSprite, 1, 1));
	SetDefaultAnimation("default");
}

