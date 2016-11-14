#pragma once
#include "Engine\Scene\Scene.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace SB
{
	struct SplashScreenCBuffer;
	class SplashScreenEffect;
}

class CollisionTestScene : public SB::Scene
{
public:
	CollisionTestScene(SB::PostMasterState & aPostMasterState);
	virtual ~CollisionTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;

private:
	SB::CapsuleCollider myCapsule;
	SB::CapsuleCollider myCapsule2;

	SB::RayCollider myRay;

	SB::SphereCollider mySphere;

	SB::Vector4f myRenderColor;
};

