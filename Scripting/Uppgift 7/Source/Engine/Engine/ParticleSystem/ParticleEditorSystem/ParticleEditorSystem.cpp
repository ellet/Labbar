#include "stdafx.h"
#include "ParticleEditorSystem.h"
#include "Engine/ParticleSystem/ParticleSystemStructs.h"

namespace ENGINE_NAMESPACE
{
	ParticleEditorSystem::ParticleEditorSystem(SB::Scene & aScene) : ParticleSystem(aScene)
	{
	}

	ParticleEditorSystem::~ParticleEditorSystem()
	{
	}

	void ParticleEditorSystem::RemoveEmitterType(const std::string & aName)
	{
		if (myEmitterTypes.find(aName) == myEmitterTypes.end())
		{
			Error("\nParticle System Error - Tried to remove an emitter which we don't have!\n\nEmitterType :  " + aName + "\nDid you spell the emitter type name wrong?\n\nAssets/Data/ParticleEmitters/particleEmitters.json contains all possible emitter types.\n");
		}
		myEmitterTypes.erase(aName);
	}

	void ParticleEditorSystem::AddEmitterType(const EmitterSettings & someSettings, const std::string & aName)
	{
		std::shared_ptr<EmitterSettings> emitter = std::make_shared<EmitterSettings>();
		*emitter = someSettings;
		std::pair<std::string, std::shared_ptr<EmitterSettings>> prettyEmitter(aName, emitter);
		myEmitterTypes.insert(prettyEmitter);
	}

	void ParticleEditorSystem::SaveEmitterTypes() const
	{
	/*	SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
		serializer.WriteObject("properties");

		serializer.WriteNode("EmitterName", myEmitterType);
		serializer.WriteNode("StartingPaused", myEmitter->GetIsPaused());
		serializer.WriteNode("OffsetPosition", myEmitter->GetPositionOffset());

		serializer.StepOut();
		serializer.WriteNode("type", "ParticleComponent");*/
	}

	std::shared_ptr<Texture> ParticleEditorSystem::GetAtlas()
	{
		return myTextureAtlas;
	}

}