#pragma once

namespace ENGINE_NAMESPACE
{
	class CollisionManager;
	class SphereCollider;
	class GameObject;

	class PhysicsComponent;

	class PhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		void Update();

		void AddPhysicsComponent(PhysicsComponent & aComponentToAdd);
		void RemovePhysicsComponent(PhysicsComponent & aComponentToRemove);

		void AddCollisionCollider(const ColliderData & aColliderData);
		void RemoveCollisionCollider(const ColliderData & aColliderData);

		void AddTriggerCollider(const ColliderData & aColliderData);
		void RemoveTriggerCollider(const ColliderData & aColliderData);


	private:
		void UpdateComponentMovement(const PhysicsComponent & aComponentToUpdate);

		std::unique_ptr<CollisionManager> myCollisionManager;
		
		GrowingArray<PhysicsComponent *> myPhysicsComponents;
	};

}