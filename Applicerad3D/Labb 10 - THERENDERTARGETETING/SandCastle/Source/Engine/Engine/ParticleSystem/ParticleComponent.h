#pragma once
#include "Engine/Component/BaseComponent.h"
#include <Utilities/Randomizer/Randomizer.h>
#include "Engine/ParticleSystem/ParticleSettings.h"

namespace ENGINE_NAMESPACE
{
	class Effect;
	template <typename T>
	class VertexBuffer;
	struct ParticleData;
	struct ParticleLogic;

	class ParticleComponent : public BaseComponent
	{
	public:
		ParticleComponent();
		~ParticleComponent();

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render() const override;

		virtual void DebugUpdate(const Time & aDeltaTime) override; //Definition is last in cpp

		void SpawnParticles(const unsigned short anAmount);
		void SpawnParticles();

		virtual void LoadData(DataNode aProperties) override;

		virtual void Initialize() override;

		void SetSettings(const ParticleSettings & someSettings);

	private:
		void UpdateParticle(const Time & aDeltaTime, const unsigned short anIndex);
		void SpawnParticle();


		GrowingArray<ParticleData> myParticles;
		GrowingArray<ParticleLogic> myParticlesLogic;

		Randomizer myRandomizer;
		ParticleSettings mySettings;

		std::shared_ptr<Effect> myEffect;
		std::shared_ptr<VertexBuffer<ParticleData>> myVertexBuffer;

		SB::Stopwatch myEmittingCoolDown;
		Time myEmitCoolDown;

		int myNumberOfParticles;
		bool myIsExplosion;
		bool myShouldExplode;
	};
}
