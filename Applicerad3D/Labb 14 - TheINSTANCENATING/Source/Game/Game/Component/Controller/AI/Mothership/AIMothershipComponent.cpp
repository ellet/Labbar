#include "stdafx.h"
#include "AIMothershipComponent.h"
#include "Engine\Physics\PhysicsComponent.h"
#include "Engine\Component\Collider\ColliderComponent.h"
#include "Engine\Component\Collider\RenderColliderComponent.h"
#include "..\AISwarmerComponent.h"
#include "..\..\..\Enemy\EnemyComponent.h"
#include "Engine/Model/AssimpModel.h"
#include "..\..\..\Health\HealthComponent.h"
#include "AIMothershipShieldComponent.h"
#include "..\Engine\Engine\Marker\MarkerComponent.h"


AIMothershipComponent::AIMothershipComponent()
{
	myUnqiueDeathEventTimer = 5.f;
	myHasBeenDefeated = false;
	mySwarmerRespawnTime = 10.f;
	mySpawnedSwarmers = 0;
	myCurrentPhase = 1;
	myPhaseSpeedMultiplier = 1.0f;
}

AIMothershipComponent::~AIMothershipComponent()
{
}

void AIMothershipComponent::Update(const SB::Time & aDeltaTime)
{
	if (myObject->GetChildren().Empty() == true)
	{
		//myHasBeenDefeated = true;
	}
	SpawnSwarmers(aDeltaTime);
	UpdateSwarmerPositions(aDeltaTime);
	UpdateShieldPositions(aDeltaTime);


	RunDeathEventFunction(aDeltaTime);
	myObject->GetRotation().RotateTowardsPoint(myObject->GetPosition(), myObject->GetPosition() + myObject->GetRotation().GetForward() * 10.f + myObject->GetRotation().GetLeft() * 2.f, aDeltaTime.InSeconds(), 3.f * myPhaseSpeedMultiplier);
	myPhysicsComponent->SetSpeed(40.f * myPhaseSpeedMultiplier);
	myPhysicsComponent->SetForceDirection(myObject->GetRotation().GetForward());
}

void AIMothershipComponent::Initialize()
{
	for (unsigned short i = 0; i < 8; i++)
	{
		SwarmerSlot newSwarmerSlot;
		newSwarmerSlot.myRespawnTimer = 0.f;


		newSwarmerSlot.mySlotPosition = SB::Vector3f(100.f, 0.f, 0.f);
		SB::Quaternion rot = myObject->GetRotation();
		rot.RotateAroundLocalZ(DEGREES_TO_RADIANSF((360.f / 8.f) * (i + 1)));
		rot.RotateVector(newSwarmerSlot.mySlotPosition);


		newSwarmerSlot.mySwarmer = nullptr;
		mySwarmerSlots.Add(newSwarmerSlot);
	}
	SetPlayer(myObject->GetScene().FindObject("Player"));
	myPhysicsComponent = &*myObject->GetComponent<SB::PhysicsComponent>();

	SpawnShieldGenerators();
}

void AIMothershipComponent::LoadData(SB::DataNode aProperties)
{
	if (aProperties.HasMember("isDefeated"))
	{
		myHasBeenDefeated = aProperties["isDefeated"].GetBool();
	}
}

void AIMothershipComponent::ToJson() const
{
	SB::JsonSerializer &serializer = SB::Engine::GetJsonSerializer();
	serializer.WriteNode("type", "AIMothershipComponent");
	serializer.WriteObject("properties");
	serializer.WriteNode("isDefeated", true);
	serializer.StepOut();
}

void AIMothershipComponent::ShieldsReportingFailure(unsigned short aShieldNumber)
{
	myShieldGenerators[aShieldNumber].myShieldGenerator = nullptr;

	bool allShieldsDown = false;

	for(unsigned short i = 0; i < myShieldGenerators.Size(); i++)
	{
		if (myShieldGenerators[i].myShieldGenerator != nullptr)
		{
			allShieldsDown = false;
			break;
		}
		allShieldsDown = true;
	}

	if (allShieldsDown == true)
	{
		myCurrentPhase = 2;
		myPhaseSpeedMultiplier = 0.5f;
	}
	//TODO: add shield take down code.
}

void AIMothershipComponent::SpawnSwarmers(const SB::Time & aDeltaTime)
{
	for (unsigned short i = 0; i < mySwarmerSlots.Size(); ++i)
	{
		if (mySwarmerSlots[i].mySwarmer == nullptr)
		{
			mySwarmerSlots[i].myRespawnTimer -= aDeltaTime.InSeconds();
			if (mySwarmerSlots[i].myRespawnTimer < 0)
			{
				mySpawnedSwarmers++;
				SB::ObjectPtr swarmer = myObject->GetScene().CreateObjectWithModel("MothershipSwarmer" + mySpawnedSwarmers, 
					SB::Engine::GetResourceManager().Get<SB::AssimpModel>("Assets/Models/Ships/Enemies/Swarmer/swarmer_lp.fbx"),
					SB::Vector3f::Zero,SB::Vector3f::One, 
					myObject->GetRotation());

				swarmer->SetScale(SB::Vector3f::One / 100.f);
				//swarmer->SetPosition(myObject->GetPosition() + myObject->AdjustOffset(mySwarmerSlots[i].mySlotPosition));
				swarmer->CreateComponent<EnemyComponent>();
				swarmer->CreateComponent<HealthComponent>()->SetHealth(1.f);
				swarmer->CreateComponent<SB::PhysicsComponent>();
				swarmer->CreateComponent<SB::ColliderComponent>()->SetRadius(10.f);
				swarmer->CreateComponent<SB::RenderColliderComponent>();
				swarmer->CreateComponent<SB::MarkerComponent>();
				swarmer->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(CollisionFilter::eEnemySwarmer);
				swarmer->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(0|CollisionFilter::ePlayer);
				swarmer->CreateComponent<AISwarmerComponent>()->SetMothership(this, i);
				swarmer->Initialize();

				mySwarmerSlots[i].myRespawnTimer = mySwarmerRespawnTime;
				mySwarmerSlots[i].mySwarmer = &*swarmer->GetComponent<AISwarmerComponent>();
			}
		}
	}
}

void AIMothershipComponent::SpawnShieldGenerators()
{
	for (unsigned short i = 0; i < 2; i++)
	{
		SB::ObjectPtr shieldGenerator = myObject->GetScene().CreateObjectWithModel("MothershipShieldGenerator" + i+1,
			SB::Engine::GetResourceManager().Get<SB::AssimpModel>("Assets/Models/Ships/Enemies/Swarmer/swarmer_lp.fbx"),
			SB::Vector3f::Zero, SB::Vector3f::One,
			myObject->GetRotation());
		shieldGenerator->SetScale(SB::Vector3f::One / 100.f);
		shieldGenerator->CreateComponent<EnemyComponent>();
		shieldGenerator->CreateComponent<HealthComponent>()->SetHealth(1.f);
		shieldGenerator->CreateComponent<SB::PhysicsComponent>();
		shieldGenerator->CreateComponent<SB::ColliderComponent>()->SetRadius(10.f);
		shieldGenerator->CreateComponent<SB::RenderColliderComponent>();
		shieldGenerator->GetComponent<SB::ColliderComponent>()->SetColliderLayerID(CollisionFilter::eEnemy);
		shieldGenerator->GetComponent<SB::ColliderComponent>()->SetCollisionFilter(0 | CollisionFilter::ePlayer);
		shieldGenerator->CreateComponent<AIMothershipShieldComponent>()->SetMothership(this, i);
		shieldGenerator->Initialize();

		myShieldGenerators.Add({SB::Vector3f(150.f - 300.f * i, 0.f, 0.f),&*shieldGenerator->GetComponent<AIMothershipShieldComponent>() });
	}
}

void AIMothershipComponent::RunDeathEventFunction(const SB::Time & aDeltaTime)
{
	if (myHasBeenDefeated == true)
	{
		myUnqiueDeathEventTimer -= aDeltaTime.InSeconds();
	}
	if (myUnqiueDeathEventTimer <= 0.f)
	{
		myObject->Remove();
	}
}

void AIMothershipComponent::UpdateSwarmerPositions(const SB::Time & aDeltaTime)
{
	for (unsigned short i = 0; i < mySwarmerSlots.Size(); ++i)
	{
		SB::Vector3f newPos = mySwarmerSlots[i].mySlotPosition;
		SB::Quaternion rot = myObject->GetRotation();

		rot.RotateAroundLocalZ(DEGREES_TO_RADIANSF(90.f * aDeltaTime.InSeconds()));
		rot.RotateVector(newPos);

		newPos = newPos *  myObject->GetRotation();
		mySwarmerSlots[i].mySlotPosition = newPos;
		if (mySwarmerSlots[i].mySwarmer != nullptr)
		{
			mySwarmerSlots[i].mySwarmer->SetPositionAndRotation(myObject->GetPosition() + mySwarmerSlots[i].mySlotPosition, myObject->GetRotation());
		}
	}
}

void AIMothershipComponent::UpdateShieldPositions(const SB::Time & aDeltaTime)
{
	for (unsigned short i = 0; i < myShieldGenerators.Size(); ++i)
	{
		if (myShieldGenerators[i].myShieldGenerator != nullptr)
		{
			myShieldGenerators[i].myShieldGenerator->SetPositionAndRotation(myObject->GetPosition() + myObject->AdjustOffset(myShieldGenerators[i].mySlotPosition), myObject->GetRotation());
		}
	}
}
