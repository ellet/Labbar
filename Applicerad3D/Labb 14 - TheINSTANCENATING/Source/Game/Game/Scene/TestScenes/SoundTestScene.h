#pragma once
#include "Engine\Scene\Scene.h"

class SoundTestScene : public SB::Scene
{
public:
	SoundTestScene(SB::PostMasterState & aPostMasterState);
	~SoundTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;
private:
	bool myPlaying;
	float mySoundLoop;
};

