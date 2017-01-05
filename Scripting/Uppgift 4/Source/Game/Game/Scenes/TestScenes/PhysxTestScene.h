#pragma once
#include "Physics\Objects\Actors\DynamicActor.h"
#include "Physics\Objects\Actors\StaticActor.h"

namespace SP
{
	class PhysicsManager;
}

class PhysxTestScene : public SB::Scene
{
public:
	PhysxTestScene(SB::PostMasterState & aPostMasterState);
	~PhysxTestScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;

private:
	void shootSphere();
	void AddBox(const SB::Vector3f & aPosition);

	std::unique_ptr< SB::InputListener> myInputListener;

	SB::GrowingArray<std::shared_ptr<SP::DynamicActor>> myBoxes;
	SB::GrowingArray<std::shared_ptr<SP::DynamicActor>> myShots;

	SP::StaticActor myPlane;

	SB::ObjectPtr myObject;
	SB::ObjectPtr myPlaneObject;
};

