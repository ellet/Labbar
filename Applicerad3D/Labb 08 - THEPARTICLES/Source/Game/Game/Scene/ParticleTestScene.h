#pragma once

#include <Engine\Scene\Scene.h>

namespace SB
{
	class CubeModel;
	class ParticleEmitterInstance;
}



class ParticleTestScene 
	: public SB::Scene
{
public:
	ParticleTestScene();
	~ParticleTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<SB::Model> myHead;
	std::unique_ptr<SB::ParticleEmitterInstance> myParticleEmitter;
};
