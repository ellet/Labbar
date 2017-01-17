#pragma once

namespace SB
{
	enum class eEmitterShape
	{
		ePoint,
		eLine,

		eCircle,
		eSphere,
		eCylinder,
		eCone,
		eRing,
		eTorus,
		ePlane,
		eBox,

		eEnumLength
	};

	struct ForceFieldDying
	{
		unsigned short myForceFieldInstanceIndex;
		Time myDyingTimer;
	};

	struct ParticleForceField
	{
		SphereShape myForceField;
		float myGravity = 1.f;
	};

	struct EmitterSettings
	{
		SB::GrowingArray<ParticleForceField> myForceFieldsSettings;

		//in pixels!
		Vector4f myTextureUV;

		//randomized particle behavior
		Vector4f myStartColor;
		Vector4f myEndColor;

		Vector3f myGravity;
		
		Vector2f myMinMaxVelocityX;
		Vector2f myMinMaxVelocityY;
		Vector2f myMinMaxVelocityZ;
		Vector2f myMinMaxRotationPerSecond;
		Vector2f myMinMaxStartRotation;
		Vector2f myMinMaxLifeTime;
		Vector2f myMinMaxSize;
	
		float myEndSizeInPercent;

		//emitter behavior
		eEmitterShape myShape = eEmitterShape::ePoint;

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
		Vector3f myGravity;
		unsigned short myForceFieldInstanceIndex;
		Time myStartLifeTime;
		Time myLifeTimeLeft;
		float myStartSize;
		bool myShouldBeRotatedInDirection;
	};

#pragma endregion

	enum class eParticleLayer
	{
		eWorld,
		eBelowGUI,
		eAboveGUI
	};

	struct ScheduledParticleCommand
	{
		ScheduledParticleCommand()
		{
		}

		ScheduledParticleCommand(const ParticleDeltaInfo & someDeltaInfo, const ParticleData & someData, const ParticleLogic & someLogic, const eParticleLayer aLayer)
		{
			myDeltaInfo = someDeltaInfo;
			myData = someData;
			myLogic = someLogic;
			myLayer = aLayer;
		}

		ParticleDeltaInfo myDeltaInfo;
		ParticleData myData;
		ParticleLogic myLogic;
		eParticleLayer myLayer;
	};
}
