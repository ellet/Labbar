#pragma once

namespace SB
{

	class SphereCollider :
		public BaseCollider
	{
	public:
		SphereCollider();
		
		SphereCollider(const Vector3f & aPosition, const float aRadius);
		SphereCollider(const SphereShape & aSphere) : myPosition(aSphere.myPosition)
		{
			SetRadius(aSphere.myRadius);
		}

		~SphereCollider();

		virtual bool CheckCollisionAgainstCollider(const BaseCollider & aCollider) const override;

		virtual bool CheckCollisionAgainstSphere(const SphereCollider & aSphereCollider) const override;

		virtual bool CheckCollisionAgainstCapsule(const CapsuleCollider & aSphereCollider) const override;

		virtual bool CheckCollisionAgainstRay(const RayCollider & aRayCollider) const override;

		void SetSphere(const SphereShape & aSphere)
		{
			UpdatePosition(aSphere.myPosition);
			SetRadius(aSphere.myRadius);
		}

		virtual void UpdatePosition(const Vector3f & aPosition) override
		{
			myPosition = aPosition;
		}
		const Vector3f & GetPosition() const
		{
			return myPosition;
		}

		virtual void SetRadius(const float aRadius) override
		{
			myRadius = aRadius;
			myRadiusSquared = aRadius * aRadius;
		}
		virtual float GetRadius() const override
		{
			return myRadius;
		}
		float GetRadiusSquared() const
		{
			return myRadiusSquared;
		}

		SphereShape GetBasicSphere() const
		{
			return SphereShape(myPosition, myRadius);
		}


	private:
		Vector3f myPosition;
		float myRadius;
		float myRadiusSquared;
	};


}

