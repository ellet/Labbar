#include "stdafx.h"
#include "ParticleComponent.h"
#include "Engine/ParticleSystem/ParticleSystemStructs.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/ParticleSystem/ParticleEmitter.h"
#include "Engine/ParticleSystem/ParticleSystem.h"
#include <D3D11.h>
#include <imgui.h>

namespace ENGINE_NAMESPACE
{
	ParticleComponent::ParticleComponent()
	{
	}

	ParticleComponent::~ParticleComponent()
	{
		myEmitter->ReturnEmitter();
	}

	void ParticleComponent::Initialize()
	{
	}

	void ParticleComponent::SetEmitter(const std::string & anEmitterType, const bool aShouldBePaused /*= true*/, const SB::Vector3f & aPositionOffset /*= SB::Vector3f::Zero*/)
	{
		myEmitter = myObject->GetScene().GetParticleSystem()->CreateEmitter(anEmitterType);
		myEmitter->SetIsPaused(aShouldBePaused);
		myEmitter->SetPositionOffset(aPositionOffset);
		myEmitter->SetComponent(this);

		myEmitterType = anEmitterType;
	}

	void ParticleComponent::LoadData(DataNode aProperties)
	{
		SetEmitter(
			aProperties["EmitterName"].GetString(), 
			aProperties["StartingPaused"].GetBool(),
			SB::Vector3f(aProperties["OffsetPosition"][0].GetFloat(), aProperties["OffsetPosition"][1].GetFloat(), aProperties["OffsetPosition"][2].GetFloat())
		);
	}

	void ParticleComponent::ToJson() const
	{
		SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
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

	void ParticleComponent::Update(const Time & aDeltaTime)
	{
		myEmitter->Update(aDeltaTime, myObject->GetPosition());
	}
}
