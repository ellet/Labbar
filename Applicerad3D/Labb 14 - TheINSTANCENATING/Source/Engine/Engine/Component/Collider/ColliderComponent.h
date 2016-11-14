#pragma once
#include "Engine\Component\BaseComponent.h"
#include "CollisionFilter.h"

namespace ENGINE_NAMESPACE
{
	class CollisionManager;

	class ColliderComponent :
		public BaseComponent
	{
	public:
		ColliderComponent();
		~ColliderComponent();

		void Initialize() override;

		void UpdatePosition(const Vector3f & aPosition);

		bool GetIsTrigger() const;
		void SetIsTrigger();

		void SetRadius(const float aRadius);
		void SetPositionOffset(const Vector3f & aPositionOffset);

		const SB::Vector3f & GetOffset() const { return myOffset; }

		void SetOffsetAndRadius(const Vector3f & aPosition, const float aRadius);
		void SetOffsetAndRadius(const SphereShape & aSphereShape);

		void Update(const Time & aDeltaTime) override;


		void SetColliderLayerID(const CollisionFilter & aLayedID);
		void SetCollisionFilter(const unsigned int aCollisionFilter);

		ColliderData GetColliderData() const;

		const SphereCollider & GetCollider() const
		{
			return myCollider;
		}

		float GetColliderRadius() const
		{
			return myCollider.GetRadius();
		}
		float GetColliderRadiusSquared() const
		{
			return myCollider.GetRadiusSquared();
		}

		virtual void LoadData(DataNode aProperties) override;

		void ToJson()const override;

	private:
		void AddColliderToManager();
		void RemoveColliderFromManager();

		bool myInitilzedFlag;
		bool myIsTrigger;

		Vector3f myOffset;
		SphereCollider myCollider;
		unsigned int myColliderID;
		unsigned int myCollisionFilter;
	};

}