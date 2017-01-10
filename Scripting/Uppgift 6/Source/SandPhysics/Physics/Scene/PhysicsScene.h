#pragma once

namespace physx
{
	class PxScene;
}

namespace SP
{

	class PhysicsScene
	{
	public:
		PhysicsScene();
		~PhysicsScene();

		void AddActor(BaseActor & aActorToAdd);

		void Update(const SB::Time & aDeltaTime);

	private:
		physx::PxScene * myScene;
	};

}
