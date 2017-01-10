#pragma once
#include <Utilities\Randomizer\Randomizer.h>
#include "Engine/ParticleSystem/ParticleSystemStructs.h"


namespace SB
{
	class ParticleSystem;
	struct EmitterSettings;
	struct ScheduledParticleCommand;
	class ParticleComponent;
	class RandomDistributionShape;

	class ParticleEmitter
	{
	public:
		ParticleEmitter();
		ParticleEmitter(const std::shared_ptr<EmitterSettings> & someSettings, ParticleSystem & aSystem, const unsigned short aForceFieldsInstanceIndex);
		~ParticleEmitter();

		void Update(const Time & aDeltaTime, const Matrix44f & aTransformation);

		inline bool GetIsPaused() const
		{
			return myIsPaused;
		}
		void SetIsPaused(const bool aTrueOrFalse);
		void ReturnEmitter();

		inline const SB::Vector3f& GetPositionOffset() const
		{
			return myPositionOffset;
		}

		void SetPositionOffset(const SB::Vector3f & anOffset);
		void SetComponent(SB::ParticleComponent * aComponentPart);

		std::shared_ptr<EmitterSettings> GetSettingsForEditor();

		void SetParticleLayer(const eParticleLayer & aLayer);

		void SetDynamicSizeMultiplier(const float & aSize);

	private:
		void CreateCommands(const Time & aDeltaTime, const Matrix44f & aTransformation);
		void MakeNumberOfCommands(const Matrix44f & aTransformation, const Vector3f & aPosition, const unsigned short aNumberOfCommands);
		void Explode(const Time & aDeltaTime, const Matrix44f & aTransformation);
		const ScheduledParticleCommand CreateParticleCommand(const Vector3f & aPosition);

		SB::Randomizer myRandomizer;
		SB::RandomDistributionShape * myShape;
		SB::Vector3f myPositionOffset;

		std::shared_ptr<EmitterSettings> mySettings;
		ParticleSystem * mySystem;
		SB::ParticleComponent * myComponentPart;

		Time myEmittingCoolDown;

		struct EditorSpecific
		{
			Time myLoopCoolDown = 2.f;
			bool myIsEditorEmitter = false;
		} myEditorSpecifics;

		float myDynamicSizeMultiplier;
		eParticleLayer myLayer;
		unsigned short myForceFieldInstanceIndex;
		bool myIsPaused;
	};
}
