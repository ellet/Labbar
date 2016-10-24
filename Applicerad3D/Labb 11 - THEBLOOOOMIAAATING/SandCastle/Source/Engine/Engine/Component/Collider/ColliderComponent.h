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

		void SetIsTrigger();

		void SetRadius(const float aRadius);
		void SetPositionOffset(const Vector3f & aPositionOffset);

		void SetOffsetAndRadius(const Vector3f & aPosition, const float aRadius);
		void SetOffsetAndRadius(const SphereShape & aSphereShape);

		void Update(const Time & aDeltaTime) override;


		void SetColliderLayedID(const CollisionFilter & aLayedID);
		void SetCollisionFilter(const unsigned int aCollisionFilter);

		ColliderData GetColliderData() const;

		const SphereCollider & GetCollider() const
		{
			return myCollider;
		}


		virtual void LoadData(DataNode aProperties) override;

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