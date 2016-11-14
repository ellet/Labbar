#include "stdafx.h"
#include "BeamWeaponComponent.h"
#include "Utilities/Intersection/Colliders/RayCollider.h"
#include "Engine/Physics/CollisionData.h"
#include "../../Enemy/EnemyComponent.h"
#include "../Projectiles/ShotComponent.h"
#include "Engine/ParticleSystem/ParticleComponent.h"
#include <Engine/Streak/StreakComponent.h>
#include <Engine/Streak/StreakLogic.h>
#include "../Projectiles/BeamShotComponent.h"
#include <Engine/Component/ModelComponent.h>

#define BEAM_LENGTH_INFINITE 10000.f

BeamWeaponComponent::BeamWeaponComponent() : WeaponComponent()
{
}

BeamWeaponComponent::BeamWeaponComponent(const WeaponData& aData) : WeaponComponent(aData)
{
}

BeamWeaponComponent::BeamWeaponComponent(SB::DataNode aProperties) : WeaponComponent(aProperties)
{
	myBeamData.beamRadius = aProperties["beamRadius"].GetFloat();
	myBeamData.beamMaxDistance = aProperties["beamMaxDistance"].GetFloat();
	myBeamData.beamLifeTime = aProperties["beamLifeTime"].GetFloat();
	myBeamData.beamPierces = aProperties["beamPierces"].GetBool();
}

BeamWeaponComponent::~BeamWeaponComponent()
{
	myUser = nullptr;
}


void BeamWeaponComponent::ToJson()const
{
	WeaponComponent::ToJson();

	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();

	serializer.WriteNode("beamMaxDistance", myBeamData.beamMaxDistance);
	serializer.WriteNode("beamPierces", myBeamData.beamPierces);
	serializer.WriteNode("beamLifeTime", myBeamData.beamLifeTime);
	serializer.WriteNode("beamRadius", myBeamData.beamRadius);

	EndToJson();
}

SB::ObjectPtr BeamWeaponComponent::CreateProjectile(const std::string& aIdentifier, const SB::Vector3f& aPosition, const SB::Quaternion& aWeaponOrientation, const SB::Quaternion& aLaunchDirection)
{
	myCollider = std::make_unique<SB::RayCollider>(aPosition, aLaunchDirection.GetForward());

	//Use growing array of collision data to extract all collision points & objects hit by the ray
	SB::GrowingArray<SB::CollisionData> collisionData;
	SB::Vector3f furthestCollisionPoint = DetermineFurthestBeamPoint(aPosition, aLaunchDirection);

	if (GetGameObject().GetScene().RayTraceAllObjectsInScene(*myCollider, collisionData) == true)
	{
		if (myBeamData.beamPierces == true)
		{
			for (unsigned short i = 0; i < collisionData.Size(); ++i)
			{
				HandleBeamCollision(collisionData[i]);
			}
		}
		else
		{
			furthestCollisionPoint = collisionData[0].myCollisionPoint;
			HandleBeamCollision(collisionData[0]);
		}
				
	}

	//Create beam
	SB::ObjectPtr beamObject = myObject->GetScene().CreateGameObject(GetDefaultProjectileIdentifier());
	beamObject->SetPosition(aPosition);

	beamObject->CreateComponent<BeamShotComponent>()->SetData(aPosition, furthestCollisionPoint, myBeamData.beamLifeTime);
	beamObject->CreateComponent<SB::StreakComponent>()->Setup(new SB::ConstantStreakProperties(SB::Vector4f(0.1f, 0.f, 1.f, 1.f), myBeamData.beamRadius * 2.f), 1.0f, 10);
	beamObject->Initialize();

	return beamObject;
}

void BeamWeaponComponent::CreateImpactParticles(const SB::Vector3f & aPosition)
{
	{
		SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUS");
		tempInpactParticles->SetPosition(aPosition);

		SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();
		particleees->SetEmitter("GatlingGunFireSparks", false);

		tempInpactParticles->Initialize();
	}
	{
		SB::ObjectPtr tempInpactParticles = GetGameObject().GetScene().CreateGameObject("PARICLUSFIRE");
		tempInpactParticles->SetPosition(aPosition);

		SB::ComponentPtr<SB::ParticleComponent> particleees = tempInpactParticles->CreateComponent<SB::ParticleComponent>();
		particleees->SetEmitter("GatlingGunFireExplosion", false);

		tempInpactParticles->Initialize();
	}
}

void BeamWeaponComponent::HandleBeamCollision(SB::CollisionData& aCollisionData)
{
	if (myBeamData.beamMaxDistance > 0.f) //0 = infinite range, only check distance vs max range if maxDistance isn't 0
	{
		float distanceBetween = (myCollider->GetPosition() - aCollisionData.myCollisionPoint).Length();
		if (distanceBetween > myBeamData.beamMaxDistance)
		{
			return;
		}
	}
	

	if (aCollisionData.myGameObject->GetComponentCount<EnemyComponent>() > 0)
	{
		aCollisionData.myGameObject->GetComponent<EnemyComponent>()->GetGameObject().GetComponent<EnemyComponent>()->TakeDamage(myWeaponData.damage);
	}

	CreateImpactParticles(aCollisionData.myCollisionPoint);
}

//Returns the "end" position of the beam, for purposes of spawning a streak between the firing position and the end point
SB::Vector3f BeamWeaponComponent::DetermineFurthestBeamPoint(const SB::Vector3f& aFiringPosition, const SB::Quaternion& aLaunchDirection) const
{
	SB::Vector3f furthestPoint = aFiringPosition;

	if (myBeamData.beamMaxDistance > 0.f)
	{
		furthestPoint += aLaunchDirection.GetForward().GetNormalized() * myBeamData.beamMaxDistance;
	}
	else
	{
		furthestPoint += aLaunchDirection.GetForward().GetNormalized() * BEAM_LENGTH_INFINITE;
	}

	return furthestPoint;
}
