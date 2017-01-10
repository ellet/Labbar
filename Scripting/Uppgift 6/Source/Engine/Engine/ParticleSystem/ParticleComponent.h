#pragma once
#include "Engine/Component/BaseComponent.h"

namespace SB
{
	class ParticleEmitter;
	enum class eParticleLayer;

	class ParticleComponent : public BaseComponent
	{
	public:
		ParticleComponent();
		~ParticleComponent();

		virtual void Initialize() override;

		virtual void Update(const Time & aDeltaTime) override;

		void SetEmitter(const std::string & anEmitterType, const bool aShouldBePaused = true, const SB::Vector3f & aPositionOffset = SB::Vector3f::Zero, const SB::Time & aTimerUntilStart = 0.f);

		virtual void LoadData(DataNode aProperties) override;
		void ToJson(JsonSerializer &aSerializer) const override;

		void Kill();

		void Pause();
		void Start();

		void SetOffset(const Vector3f & anOffset);
		void SetParticleLayer(const eParticleLayer & aLayer);

		void SetDynamicParticleSize(const float & aSize);

	private:
		std::string myEmitterType;
		std::shared_ptr<ParticleEmitter> myEmitter;
		SB::Time myTimeUntilUnpause;
		SB::Time myTimer;
		bool myStartedEmitter;
	};
}
