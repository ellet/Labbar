#pragma once
#include <Utilities\Randomizer\Randomizer.h>


namespace ENGINE_NAMESPACE
{
	class ParticleSystem;
	struct EmitterSettings;
	struct ScheduledParticleCommand;
	class ParticleComponent;

	class ParticleEmitter
	{
	public:
		ParticleEmitter();
		ParticleEmitter(const std::shared_ptr<EmitterSettings> & someSettings, ParticleSystem & aSystem);
		~ParticleEmitter();

		void Update(const Time & aDeltaTime, const Vector3f & aPosition);

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

	private:
		void CreateCommands(const Time & aDeltaTime, const Vector3f & aPosition);
		void Explode(const Time & aDeltaTime, const Vector3f & aPosition);
		const ScheduledParticleCommand CreateParticleCommand(const Vector3f & aPosition);

		SB::Randomizer myRandomizer;
		SB::Vector3f myPositionOffset;

		ParticleSystem * mySystem;
		SB::ParticleComponent * myComponentPart;
		std::shared_ptr<EmitterSettings> mySettings;

		Time myEmittingCoolDown;

		bool myIsPaused;

		struct EditorSpecific
		{
			bool myIsEditorEmitter = false;
			Time myLoopCoolDown = 2.f;
		} myEditorSpecifics;
	};
}
