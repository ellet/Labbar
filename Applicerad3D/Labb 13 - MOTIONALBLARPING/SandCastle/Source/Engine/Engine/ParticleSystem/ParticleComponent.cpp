#include "stdafx.h"
#include "ParticleComponent.h"
#include "Engine/Buffer/VertexBuffer.h"
#include "Engine/ParticleSystem/ParticleEffect.h"
#include "Engine/ParticleSystem/ParticleLogic.h"
#include "Engine/ParticleSystem/ParticleData.h"
#include "Engine/GameObject/GameObject.h"
#include <D3D11.h>
#include <imgui.h>

namespace ENGINE_NAMESPACE
{
	ParticleComponent::ParticleComponent()
	{	
		myParticles.Reserve(1024);
		myParticlesLogic.Reserve(1024);

		myVertexBuffer = std::make_shared<VertexBuffer<ParticleData>>(nullptr, 1024, false);
		myEffect = std::make_shared<ParticleEffect>();

		mySettings.myAmountOfParticles = 100;

		mySettings.myStartColor = Vector4f::One;
		mySettings.myEndColor = Vector4f::One;
		mySettings.myMinMaxVelocityX = Vector2f(-1.f, 1.f);
		mySettings.myMinMaxVelocityY = Vector2f(-1.f, 1.f);
		mySettings.myMinMaxVelocityZ = Vector2f(-1.f, 1.f);
		mySettings.myMinMaxLifeTime = Vector2f(1.f, 10.f);
		mySettings.myMinMaxSize = Vector2f(0.1f, 0.5f);

		myEmitCoolDown = 0.1f;
		myIsExplosion = false;
		myShouldExplode = false;

		myRandomizer.SetSeed();
	}

	ParticleComponent::~ParticleComponent()
	{
	}

	void ParticleComponent::Update(const Time & aDeltaTime)
	{
		if (myIsExplosion == false)
		{
			if (myEmittingCoolDown.GetElapsedTime() >= myEmitCoolDown)
			{
				unsigned short numberOfWrappings = static_cast<unsigned short>(myEmittingCoolDown.GetElapsedTime().InSeconds() / myEmitCoolDown.InSeconds());
				for (unsigned short iWrap = 0; iWrap < numberOfWrappings; ++iWrap)
				{
					if (myParticles.Size() < 1023)
					{
						SpawnParticle();
					}
				}
				myEmittingCoolDown.Restart();
			}
		}
		else
		{
			if (myShouldExplode == false && myParticles.Size() == 0)
			{
				myObject->Remove();
			}
		}

		for (unsigned short iParticle = 0; iParticle < myParticles.Size(); ++iParticle)
		{
			UpdateParticle(aDeltaTime, iParticle);

			if ((myParticlesLogic[iParticle].myLifeTimeLeft - aDeltaTime).InSeconds() <= 0.f)
			{
				myParticles.RemoveCyclicAtIndex(iParticle);
				myParticlesLogic.RemoveCyclicAtIndex(iParticle);
			}
		}
	}

	void ParticleComponent::Render() const
	{
		if (myParticles.Size() > 0)
		{
			myVertexBuffer->UpdateData(&myParticles[0], myParticles.Size(), true);

			myVertexBuffer->Bind(0);
			myEffect->Bind();

			Engine::GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			Engine::GetRenderer().GetContext()->Draw(myParticles.Size(), 0);
		}
		
	}

	void ParticleComponent::SpawnParticles(const unsigned short anAmount)
	{
		for (unsigned short iParticle = 0; iParticle < anAmount; ++iParticle)
		{
			SpawnParticle();
		}
	}

	void ParticleComponent::SpawnParticles()
	{
		myIsExplosion = true;
		myShouldExplode = false;
		for (unsigned short iParticle = 0; iParticle < mySettings.myAmountOfParticles; ++iParticle)
		{
			SpawnParticle();
		}
	}

	void ParticleComponent::LoadData(DataNode aProperties)
	{
		mySettings.myStartColor.x = aProperties["StartColor"][0].GetFloat();
		mySettings.myStartColor.y = aProperties["StartColor"][1].GetFloat();
		mySettings.myStartColor.z = aProperties["StartColor"][2].GetFloat();
		mySettings.myStartColor.w = aProperties["StartColor"][3].GetFloat();

		mySettings.myEndColor.x = aProperties["EndColor"][0].GetFloat();
		mySettings.myEndColor.y = aProperties["EndColor"][1].GetFloat();
		mySettings.myEndColor.z = aProperties["EndColor"][2].GetFloat();
		mySettings.myEndColor.w = aProperties["EndColor"][3].GetFloat();

		mySettings.myAmountOfParticles = aProperties["AmountOfParticles"].GetUnsignedShort();
		mySettings.myEmitCoolDown = aProperties["EmitCoolDown"].GetFloat();

		mySettings.myMinMaxSize.x = aProperties["MinMaxSize"][0].GetFloat();
		mySettings.myMinMaxSize.y = aProperties["MinMaxSize"][1].GetFloat();

		myIsExplosion = aProperties["IsExplosion"].GetBool();
		myShouldExplode = aProperties["IsExplosion"].GetBool();
		
		if (mySettings.myMinMaxSize.x > mySettings.myMinMaxSize.y)
		{
			Error("Particle Settings error - Minimum Particle Size (the flat size, not the changing size) is greater than its max!");
		}

		mySettings.myEndSizeInPercent = aProperties["EndSizeInPercent"].GetFloat();

		mySettings.myMinMaxLifeTime.x = aProperties["MinMaxLifetime"][0].GetFloat();
		mySettings.myMinMaxLifeTime.y = aProperties["MinMaxLifetime"][1].GetFloat();

		if (mySettings.myMinMaxLifeTime.x > mySettings.myMinMaxLifeTime.y)
		{
			Error("Particle Settings error - Minimum Particle Lifetime is greater than its max!");
		}
		
		mySettings.myMinMaxVelocityX.x = aProperties["MinMaxVelocityX"][0].GetFloat();
		mySettings.myMinMaxVelocityX.y = aProperties["MinMaxVelocityX"][1].GetFloat();

		if (mySettings.myMinMaxVelocityX.x > mySettings.myMinMaxVelocityX.y)
		{
			Error("Particle Settings error - Minimum X velocity is greater than its max!");
		}

		mySettings.myMinMaxVelocityY.x = aProperties["MinMaxVelocityY"][0].GetFloat();
		mySettings.myMinMaxVelocityY.y = aProperties["MinMaxVelocityY"][1].GetFloat();

		if (mySettings.myMinMaxVelocityY.x > mySettings.myMinMaxVelocityY.y)
		{
			Error("Particle Settings error - Minimum Y velocity is greater than its max!");
		}

		mySettings.myMinMaxVelocityZ.x = aProperties["MinMaxVelocityZ"][0].GetFloat();
		mySettings.myMinMaxVelocityZ.y = aProperties["MinMaxVelocityZ"][1].GetFloat();

		if (mySettings.myMinMaxVelocityZ.x > mySettings.myMinMaxVelocityZ.y)
		{
			Error("Particle Settings error - Minimum Z velocity is greater than its max!");
		}
	
	}

	void ParticleComponent::Initialize()
	{
		myEmitCoolDown = mySettings.myEmitCoolDown;
		if (myShouldExplode == true)
		{
			SpawnParticles(mySettings.myAmountOfParticles);
			myShouldExplode = false;
		}
		myNumberOfParticles = static_cast<int>(mySettings.myAmountOfParticles);
	}

	void ParticleComponent::SetSettings(const ParticleSettings & someSettings)
	{
		mySettings = someSettings;
	}

	void ParticleComponent::UpdateParticle(const Time & aDeltaTime, const unsigned short anIndex)
	{
		float progress = myParticlesLogic[anIndex].myLifeTimeLeft.InSeconds() / myParticlesLogic[anIndex].myStartLifeTime.InSeconds();
		float reverseProgress = (1.f - progress);

		myParticlesLogic[anIndex].myLifeTimeLeft -= aDeltaTime;

		myParticles[anIndex].myPosition += myParticlesLogic[anIndex].myVelocity * aDeltaTime.InSeconds();
		Vector4f endSample = (mySettings.myEndColor * reverseProgress);
		Vector4f startSample = (mySettings.myStartColor * progress);

		myParticles[anIndex].myColor = startSample + endSample;
		myParticles[anIndex].myColor.w = 1.f;

		float endSize = myParticlesLogic[anIndex].myStartSize * mySettings.myEndSizeInPercent;

		float size = myParticlesLogic[anIndex].myStartSize + ((endSize - myParticlesLogic[anIndex].myStartSize ) * reverseProgress);

		myParticles[anIndex].mySize = size;
	}

	void ParticleComponent::SpawnParticle()
	{

		ParticleData tempData;
		tempData.myPosition = myObject->GetPosition();
		tempData.mySize = myRandomizer.GetRandomValue(mySettings.myMinMaxSize.x, mySettings.myMinMaxSize.y);
		tempData.myColor = mySettings.myStartColor;
		tempData.myColor.w = 1.f;

		myParticles.Add(tempData);
		
		ParticleLogic tempLogic;
		tempLogic.myLifeTimeLeft = Time::FromSeconds(myRandomizer.GetRandomValue(mySettings.myMinMaxLifeTime.x, mySettings.myMinMaxLifeTime.y));
		tempLogic.myStartLifeTime = tempLogic.myLifeTimeLeft;
		tempLogic.myStartSize = tempData.mySize;
		tempLogic.myVelocity.x = myRandomizer.GetRandomValue(mySettings.myMinMaxVelocityX.x, mySettings.myMinMaxVelocityX.y);
		tempLogic.myVelocity.z = myRandomizer.GetRandomValue(mySettings.myMinMaxVelocityY.x, mySettings.myMinMaxVelocityY.y);
		tempLogic.myVelocity.y = myRandomizer.GetRandomValue(mySettings.myMinMaxVelocityZ.x, mySettings.myMinMaxVelocityZ.y);

		myParticlesLogic.Add(tempLogic);
	}

	void ParticleComponent::DebugUpdate(const Time & aDeltaTime)
	{
		//ImGui::Begin("ParticleEditor");

		//ImGui::SliderFloat("Start Color: ", &mySettings.myStartColor.x, 0.f, 1.f);
		//ImGui::SliderFloat("Start Color: ", &mySettings.myStartColor.y, 0.f, 1.f);
		//ImGui::SliderFloat("Start Color: ", &mySettings.myStartColor.z, 0.f, 1.f);

		//ImGui::SliderFloat("End Color: ", &mySettings.myEndColor.x, 0.f, 1.f);
		//ImGui::SliderFloat("End Color: ", &mySettings.myEndColor.y, 0.f, 1.f);
		//ImGui::SliderFloat("End Color: ", &mySettings.myEndColor.z, 0.f, 1.f);

		//ImGui::SliderFloat("MinX: ", &mySettings.myMinMaxVelocityX.x, -1.f, 1.f);
		//ImGui::SliderFloat("MaxX: ", &mySettings.myMinMaxVelocityX.y, -1.f, 1.f);

		//ImGui::SliderFloat("MinY: ", &mySettings.myMinMaxVelocityY.x, -1.f, 1.f);
		//ImGui::SliderFloat("MaxY: ", &mySettings.myMinMaxVelocityY.y, -1.f, 1.f);

		//ImGui::SliderFloat("MinZ: ", &mySettings.myMinMaxVelocityZ.x, -1.f, 1.f);
		//ImGui::SliderFloat("MaxZ: ", &mySettings.myMinMaxVelocityZ.y, -1.f, 1.f);

		//ImGui::SliderFloat("Min Lifetime: ", &mySettings.myMinMaxVelocityZ.x, 0.f, 60.f);
		//ImGui::SliderFloat("Max Lifetime: ", &mySettings.myMinMaxVelocityZ.y, 0.f, 60.f);

		//ImGui::SliderFloat("Min Size: ", &mySettings.myMinMaxVelocityZ.x, -100.f, 100.f);
		//ImGui::SliderFloat("Max Size: ", &mySettings.myMinMaxVelocityZ.y, -100.f, 100.f);

		//ImGui::SliderFloat("End Size %: ", &mySettings.myMinMaxVelocityZ.y, -10.f, 10.f);
		//ImGui::SliderInt("Num of Particles: ", &myNumberOfParticles, 0, 1024);

		//ImGui::End();

		//ImGui::SetNextWindowPos({ 16, 16 }, ImGuiSetCond_Once);
		//ImGui::SetNextWindowSize({ 375, 400 }, ImGuiSetCond_Once);
		//ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_Once);

		//if (ImGui::Begin("Collision", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		//{
		//	if (ImGui::CollapsingHeader("Object 1") == true)
		//	{
		//		SB::Vector3f tempVector1 = myTestObject1->GetPosition();
		//		float tempScale1 = myTestObject1->GetScale().x * 100.f;
		//		ImGui::SliderFloat("X1", &tempVector1.x, -3.f, 3.f);
		//		ImGui::SliderFloat("Y1", &tempVector1.y, -3.f, 3.f);
		//		ImGui::SliderFloat("Z1", &tempVector1.z, -3.f, 3.f);
		//		
		//		ImGui::SliderFloat("Scale1", &tempScale1, -0.1f, 3.f);
		//		
		//		myTestObject1->GetComponent<SB::ColliderComponent>()->SetRadius(tempScale1 / 2.f);
		//		tempScale1 /= 100.f;
		//		myTestObject1->SetScale(SB::Vector3f(tempScale1, tempScale1, tempScale1));
		//		myTestObject1->SetPosition(tempVector1);
		//		myTestObject1->GetComponent<SB::ColliderComponent>()->UpdatePosition(tempVector1);
		//		
		//		
		//	}
		//	
		//	if (ImGui::CollapsingHeader("Object 2") == true)
		//	{
		//		SB::Vector3f tempVector2 = myTestObject2->GetPosition();
		//		float tempScale2 = myTestObject2->GetScale().x * 100.f;
		//		ImGui::SliderFloat("X2", &tempVector2.x, -3.f, 3.f);
		//		ImGui::SliderFloat("Y2", &tempVector2.y, -3.f, 3.f);
		//		ImGui::SliderFloat("Z2", &tempVector2.z, -3.f, 3.f);
		//		ImGui::SliderFloat("Scale2", &tempScale2, -0.1f, 3.f);
		//		myTestObject2->GetComponent<SB::ColliderComponent>()->SetRadius(tempScale2 / 2.f);
		//		tempScale2 /= 100.f;
		//		myTestObject2->SetScale(SB::Vector3f(tempScale2, tempScale2, tempScale2));
		//		myTestObject2->SetPosition(tempVector2);
		//		myTestObject2->GetComponent<SB::ColliderComponent>()->UpdatePosition(tempVector2);
		//		
		//	}
		//	if (SB::Intersection::SphereVsSphere(myTestObject1->GetComponent<SB::ColliderComponent>()->GetCollider(), myTestObject2->GetComponent<SB::ColliderComponent>()->GetCollider()) == true)
		//	{
		//		//myTestObject1->TriggerEvent(SB::CollisionEvent());
		//		//myTestObject2->TriggerEvent(SB::CollisionEvent());
		//	}
		//
		//	bool tempCollisionObj1 = myTestObject1->GetComponent<TestHandleCollisionComponent>()->HasCollided();
		//	bool tempCollisionObj2 = myTestObject2->GetComponent<TestHandleCollisionComponent>()->HasCollided();
		//	if (tempCollisionObj1 == true && tempCollisionObj2 == true)
		//	{
		//		ImGui::Text("Collision!");
		//	}
		//	else
		//	{
		//		ImGui::Text("void!!!");
		//	}
		/*}
		ImGui::End();*/
	}
}
