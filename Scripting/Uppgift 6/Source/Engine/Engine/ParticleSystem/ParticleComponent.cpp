#include "stdafx.h"
#include "ParticleComponent.h"
#include "Engine/ParticleSystem/ParticleSystemStructs.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/ParticleSystem/ParticleEmitter.h"
#include "Engine/ParticleSystem/ParticleSystem.h"
#include <D3D11.h>
#include <imgui.h>

namespace SB
{
	ParticleComponent::ParticleComponent()
	{
		myTimeUntilUnpause = 0;
		myTimer = 0;
		myStartedEmitter = true;
	}

	ParticleComponent::~ParticleComponent()
	{
		myEmitter->ReturnEmitter();
	}

	void ParticleComponent::Initialize()
	{
	}

	void ParticleComponent::SetEmitter(const std::string & anEmitterType, const bool aShouldBePaused /*= true*/, const SB::Vector3f & aPositionOffset /*= SB::Vector3f::Zero*/, const SB::Time & aTimerUntilStart /*= 0.f*/)
	{
		myEmitter = myObject->GetScene().GetParticleSystem()->CreateEmitter(anEmitterType);
		myEmitter->SetIsPaused(aShouldBePaused);
		myEmitter->SetPositionOffset(aPositionOffset);
		myEmitter->SetComponent(this);

		myEmitterType = anEmitterType;

		if (aTimerUntilStart.InSeconds() != 0.f && aShouldBePaused == true)
		{
			myStartedEmitter = false;
			myTimeUntilUnpause = aTimerUntilStart;
			myTimer = 0.f;
		}
	}

	void ParticleComponent::LoadData(DataNode aProperties)
	{
		SetEmitter(
			aProperties["EmitterName"].GetString(), 
			aProperties["StartingPaused"].GetBool(),
			SB::Vector3f(aProperties["OffsetPosition"][0].GetFloat(), aProperties["OffsetPosition"][1].GetFloat(), aProperties["OffsetPosition"][2].GetFloat())
		);
	}

	void ParticleComponent::ToJson(JsonSerializer &aSerializer) const
	{
		SB::JsonSerializer& serializer = aSerializer;
		serializer.WriteObject("properties");

		serializer.WriteNode("EmitterName", myEmitterType);
		serializer.WriteNode("StartingPaused", myEmitter->GetIsPaused());
		serializer.WriteNode("OffsetPosition", myEmitter->GetPositionOffset());

		serializer.StepOut();
		serializer.WriteNode("type", "ParticleComponent");
	}

	void ParticleComponent::Kill()
	{
		myObject->Remove();
	}


	void ParticleComponent::Pause()
	{
		myEmitter->SetIsPaused(true);
	}

	void ParticleComponent::Start()
	{
		myEmitter->SetIsPaused(false);
	}


	void ParticleComponent::SetOffset(const Vector3f & anOffset)
	{
		myEmitter->SetPositionOffset(anOffset);
	}


	void ParticleComponent::SetParticleLayer(const eParticleLayer & aLayer)
	{
		myEmitter->SetParticleLayer(aLayer);
	}


	void ParticleComponent::SetDynamicParticleSize(const float & aSize)
	{
		myEmitter->SetDynamicSizeMultiplier(aSize);
	}

	void ParticleComponent::Update(const Time & aDeltaTime)
	{
		if (myStartedEmitter == false)
		{
			myTimer += aDeltaTime;
			if (myTimer >= myTimeUntilUnpause)
			{
				myEmitter->SetIsPaused(false);
				myStartedEmitter = true;
			}
		}

		myEmitter->Update(aDeltaTime, myObject->GetTransformation());
	}
}
