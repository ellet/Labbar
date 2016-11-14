#pragma once
#include "Engine\Scene\Scene.h"
#include "Utilities\Randomizer\Randomizer.h"

class TestEnemyCollisionScene :
	public SB::Scene
{
public:
	TestEnemyCollisionScene(SB::PostMasterState & aPostMasterState);
	~TestEnemyCollisionScene();


	void Update(const SB::Time & aDeltaTime) override;


	void Render() override;

private:
	void CreateEnemyObject(SB::ObjectPtr & aGameObject);

	SB::GrowingArray<SB::ObjectPtr> myEnemyObjects;

	SB::Randomizer myRandomizer;
};