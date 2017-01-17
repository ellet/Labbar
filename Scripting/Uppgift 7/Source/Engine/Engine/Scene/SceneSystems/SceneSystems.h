#pragma once

namespace SP
{
	class PhysicsManager;
}

namespace SB
{

	class SceneSystems
	{
	public:
		SceneSystems();
		~SceneSystems();

		void Update(const Time & aDeltaTime);
		void Render();

		SP::PhysicsManager & GetPhysicsManager();


	private:
		std::unique_ptr<SP::PhysicsManager> myPhysicsManager;
	};

}
