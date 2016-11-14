#pragma once
#include <Engine\Scene\Scene.h>

class PlayerTestScene : public SB::Scene
{
public:
	PlayerTestScene(SB::PostMasterState & aPostMasterState);
	~PlayerTestScene();


	virtual void Update(const SB::Time & aDeltaTime) override;


	virtual void Render() override;

private:
	SB::ObjectPtr myPlayer;
};

