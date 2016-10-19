#pragma once
#include "Engine\Component\BaseComponent.h"



namespace ENGINE_NAMESPACE
{
	class SphereCollider;
	struct CollisionData;

	class PhysicsComponent
		: public BaseComponent
	{
	public:
		friend class PhysicsManager;

		PhysicsComponent();
		~PhysicsComponent();

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Initialize() override;
		virtual void LoadData(DataNode aProperties) override;

		float GetCollisionForceReduction() const;
		void SetCollisionForceReduction(float aReduction);
		const Vector3f& GetForceDirection() const;
		void SetForceDirection(const Vector3f & aForceDirection);
		float GetSpeed() const;
		void SetSpeed(float aSpeed);
		void ApplyForce(const float aSpeed, const Vector3f & aDirection);
		float GetDrag() const;
		void SetDrag(float aDragAmount);
	private:
		bool myIsInitialized;

		ColliderData GetColliderData() const;
		const SphereCollider & GetMovedCollider() const;

		void MoveObjectToPosition() const;
		void HandleDrag(const Time & aDeltaTime);
		void SetMoveToPosition(const Time & aDeltaTime);
		void HandleCollisionMovement(const CollisionData & aCollisionData);
		
		Vector3f myMoveToPosition;
		std::unique_ptr< SphereCollider> mySphereCollider;

		float mySpeed;
		float myDrag;
		Vector3f myForceDirection;
		float myCollisionForceReduction;

		bool myMoveToSet;
	};

}