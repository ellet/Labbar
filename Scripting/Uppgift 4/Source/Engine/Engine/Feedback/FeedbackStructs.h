#pragma once

namespace SB
{
	class ParticleEmitter;
	class VisualEffect;

	struct FeedbackParticleEmitter
	{
		std::shared_ptr<ParticleEmitter> myEmitter;
		Vector3f myOffset;
		Time myStartTime = 0;
	};

	struct FeedbackVisualEffect
	{
		std::shared_ptr<VisualEffect> myVisualEffect;
		Vector3f myOffset;
		Time myStartTime = 0;
	};

	struct FeedbackSettings
	{
		GrowingArray<FeedbackParticleEmitter> myParticleEmitters;
		GrowingArray<FeedbackVisualEffect> myVisualEffects;
	};
}