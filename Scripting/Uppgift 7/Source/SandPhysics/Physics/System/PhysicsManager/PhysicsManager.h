#pragma once


namespace SP
{
	class PhysicsScene;

	class PhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		void AddActor(BaseActor & aAcotr);

		void Update(const SB::Time & aDeltaTime);

	private:
		std::unique_ptr<PhysicsScene> myScene;
	};

}
