#pragma once
#include "Engine\Scene\Scene.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace SB
{
	struct SplashScreenCBuffer;
	class SplashScreenEffect;
	class SphereCollider;
}

class CollisionTestScene : public SB::Scene
{
public:
	CollisionTestScene();
	virtual ~CollisionTestScene();
	
	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;

private:
	void CreateGameObjectWithCollider(SB::ObjectPtr & aGameObject);

	SB::GrowingArray<SB::ObjectPtr> myCollisionObjects;

	SB::ObjectPtr myTestObject1;
	SB::Randomizer myRandomizer;

	void CreateFactories();
};

