#pragma once

namespace ENGINE_NAMESPACE
{
	struct EmitterSettings
	{
		//in pixels!
		Vector4f myTextureUV;

		//randomized particle behavior
		Vector4f myStartColor;
		Vector4f myEndColor;

		Vector2f myMinMaxVelocityX;
		Vector2f myMinMaxVelocityY;
		Vector2f myMinMaxVelocityZ;
		Vector2f myMinMaxRotationPerSecond;
		Vector2f myMinMaxStartRotation;
		Vector2f myMinMaxLifeTime;
		Vector2f myMinMaxSize;
		float myEndSizeInPercent;

		//emitter behavior
		Time myEmitCoolDown;
		unsigned short myAmountOfParticles;

		bool myShouldRotateInDirection;
		bool myIsExplosion;
	};

#pragma region PerParticleInstance

	struct ParticleDeltaInfo
	{
		Vector4f myStartColor;
		Vector4f myEndColor;
		float myEndSizeInPercent;
		float myRotationDelta;
	};

	struct ParticleData //Used for Vertex buffer!
	{
		Vector4f myRotation;
		Vector3f myPosition;
		float mySize;
		Vector4f myColor;
		Vector4f myUV;
	};

	struct ParticleLogic
	{
		Matrix33f myRotation;
		Vector3f myVelocity;
		Time myStartLifeTime;
		Time myLifeTimeLeft;
		float myStartSize;
		bool myShouldBeRotatedInDirection;
	};

#pragma endregion

	struct ScheduledParticleCommand
	{
		ScheduledParticleCommand()
		{
		}
		ScheduledParticleCommand(const ParticleDeltaInfo & someDeltaInfo, const ParticleData & someData, const ParticleLogic & someLogic)
		{
			myDeltaInfo = someDeltaInfo;
			myData = someData;
			myLogic = someLogic;
		}

		ParticleDeltaInfo myDeltaInfo;
		ParticleData myData;
		ParticleLogic myLogic;
	};
}
