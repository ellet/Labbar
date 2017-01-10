#pragma once
#include "Engine\Component\BaseComponent.h"
#include "CollisionFilter.h"

namespace SB
{
	class CollisionManager;

	class ColliderComponent :
		public BaseComponent
	{
	public:
		ColliderComponent();
		~ColliderComponent();
		
		void Initialize() override;

		void SetPositionOffset(const Vector3f & aPositionOffset);

		const SB::Vector3f & GetOffset() const { return myOffset; }


		void Update(const Time & aDeltaTime) override;

		void SetRadius(const float aRadius);
		float GetRadius() const;


	private:
		void UpdatePosition(const Vector3f & aPosition);

		bool myInitilzedFlag;
		
		Vector3f myOffset;

		std::unique_ptr<BaseCollider> myCollider;

		ColliderTypes myColliderType;

		unsigned int myColliderID;
		unsigned int myCollisionFilter;
	};

}
