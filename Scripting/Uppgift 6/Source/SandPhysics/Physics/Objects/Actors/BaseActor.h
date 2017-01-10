#pragma once

namespace physx
{
	class PxRigidActor;
}

namespace SP
{

	class BaseActor
	{
	public:
		virtual ~BaseActor();

		void AddShape(const SB::BoxShape & aBoxShape);
		void AddShape(const SB::SphereShape & aSphereShape);

		physx::PxRigidActor & GetActor() const;

		SB::Vector3f GetPosition() const;
		SB::Quaternion GetRotation() const;

	protected:
		BaseActor();
		physx::PxRigidActor * myActor;

	};

}
