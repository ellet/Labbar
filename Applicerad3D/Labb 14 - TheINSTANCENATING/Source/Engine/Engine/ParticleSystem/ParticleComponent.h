#pragma once
#include "Engine/Component/BaseComponent.h"

namespace ENGINE_NAMESPACE
{
	class ParticleEmitter;

	class ParticleComponent : public BaseComponent
	{
	public:
		ParticleComponent();
		~ParticleComponent();

		virtual void Initialize() override;

		virtual void Update(const Time & aDeltaTime) override;

		void SetEmitter(const std::string & anEmitterType, const bool aShouldBePaused = true, const SB::Vector3f & aPositionOffset = SB::Vector3f::Zero);

		virtual void LoadData(DataNode aProperties) override;
		void ToJson() const override;

		void Kill();
	private:
		std::string myEmitterType;
		std::shared_ptr<ParticleEmitter> myEmitter;
	};
}
