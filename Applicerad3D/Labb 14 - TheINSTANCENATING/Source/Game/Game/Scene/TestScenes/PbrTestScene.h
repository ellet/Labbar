#pragma once
#include <Engine\Scene\Scene.h>

namespace SB
{
	class CubeModel;
}

class PbrTestScene : public SB::Scene
{
public:
	PbrTestScene(SB::PostMasterState & aPostMasterState);
	~PbrTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::shared_ptr<SB::Model> myHead;
};

