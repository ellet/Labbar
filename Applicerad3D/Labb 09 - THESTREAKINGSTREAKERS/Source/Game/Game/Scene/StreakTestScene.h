#pragma once

#include <Engine\Scene\Scene.h>

namespace SB
{
	class CubeModel;
	class StreakEmitterInstance;
}



class StreakTestScene 
	: public SB::Scene
{
public:
	StreakTestScene();
	~StreakTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<SB::Model> myHead;
	std::unique_ptr<SB::StreakEmitterInstance> myStreakEmitter;
};
