#pragma once

namespace physx
{
	class PxFoundation;
	class PxProfileZoneManager;
	class PxPhysics;	
	class PxDefaultCpuDispatcher;
}



namespace SP
{

	class CreationManager
	{
	public:
		static void Create();
		static void Destroy();		

		static void ConnectToVisualDebugger();

		static physx::PxPhysics & GetPhysicsSystem();
		static physx::PxFoundation & GetFoundation();
		static physx::PxProfileZoneManager & GetProfileManager();
		static physx::PxDefaultCpuDispatcher & GetDispatcher();

	private:
		static CreationManager & GetInstance();

		physx::PxFoundation * myFoundation;
		physx::PxProfileZoneManager * myProfileManager;
		physx::PxPhysics * myPhysicsSystem;
		physx::PxDefaultCpuDispatcher * myDispatcher;
		void * myDebuggerConnection;

		static CreationManager * ourInstance;

		CreationManager();
		~CreationManager();
	};

	inline CreationManager & CreationManager::GetInstance()
	{
		if (ourInstance == nullptr)
		{
			Error("Physics Creation Manager is nullptr");
		}

		return *ourInstance;
	}

	inline physx::PxPhysics & CreationManager::GetPhysicsSystem()
	{
		if (GetInstance().myPhysicsSystem == nullptr)
		{
			Error("physx PhysicsSystem was nullptr");
		}
		return *GetInstance().myPhysicsSystem;
	}

	inline physx::PxFoundation & CreationManager::GetFoundation()
	{
		if (GetInstance().myFoundation == nullptr)
		{
			Error("physx Foundation was nullptr");
		}
		return *GetInstance().myFoundation;
	}

	inline physx::PxProfileZoneManager & CreationManager::GetProfileManager()
	{
		if (GetInstance().myProfileManager == nullptr)
		{
			Error("physx ProfileManager was nullptr");
		}
		return *GetInstance().myProfileManager;
	}

	inline physx::PxDefaultCpuDispatcher & CreationManager::GetDispatcher()
	{
		if (GetInstance().myDispatcher == nullptr)
		{
			Error("physx Dispatcher was nullptr");
		}
		return *GetInstance().myDispatcher;
	}
}
