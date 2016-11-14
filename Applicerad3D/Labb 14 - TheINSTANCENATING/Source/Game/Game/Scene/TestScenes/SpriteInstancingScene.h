#pragma once
#include "Engine/Scene/Scene.h"
#include "../Utilities/Utilities/Randomizer/Randomizer.h"



class SpriteInstancingScene :
	public SB::Scene
{
public:
	SpriteInstancingScene(SB::PostMasterState & aPostMasterState);
	~SpriteInstancingScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;

private:
	SB::GrowingArray<SB::Sprite, size_t> mySprites;
	SB::Randomizer myRandomizer;
};

