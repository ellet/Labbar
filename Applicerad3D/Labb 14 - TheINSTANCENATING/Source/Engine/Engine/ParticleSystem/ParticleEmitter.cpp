#include "stdafx.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "ParticleSystemStructs.h"
#include "ParticleComponent.h"

namespace ENGINE_NAMESPACE
{

	ParticleEmitter::ParticleEmitter(const std::shared_ptr<EmitterSettings> & someSettings, ParticleSystem & aSystem)
	{
		myIsPaused = true;
		mySettings = someSettings;
		mySystem = &aSystem;
		myEmittingCoolDown = myRandomizer.GetRandomValue(0.f, mySettings->myEmitCoolDown.InSeconds());
	}

	ParticleEmitter::ParticleEmitter()
	{
		myIsPaused = true;
		mySettings = nullptr;
	}

	ParticleEmitter::~ParticleEmitter()
	{
	}

	void ParticleEmitter::Update(const Time & aDeltaTime, const Vector3f & aPosition)
	{
		if (myIsPaused == false)
		{
			if (mySettings->myIsExplosion == true)
			{
				Explode(aDeltaTime, aPosition);
				return;
			}

			CreateCommands(aDeltaTime, aPosition);
		}
		if (myEditorSpecifics.myIsEditorEmitter == true) // ugly code for particle editor :/ specialcase for explosions
		{
			myEditorSpecifics.myLoopCoolDown -= aDeltaTime;
			if (myEditorSpecifics.myLoopCoolDown <= 0.f)
			{
				myEditorSpecifics.myLoopCoolDown = 2.f;
				myIsPaused = false;
			}
		}
	}

	void ParticleEmitter::SetIsPaused(const bool aTrueOrFalse)
	{
		myIsPaused = aTrueOrFalse;
	}

	void ParticleEmitter::ReturnEmitter()
	{
		myIsPaused = true;
		mySettings = nullptr;
	}

	void ParticleEmitter::SetPositionOffset(const SB::Vector3f & anOffset)
	{
		myPositionOffset = anOffset;
	}

	void ParticleEmitter::SetComponent(SB::ParticleComponent * aComponentPart)
	{
		myComponentPart = aComponentPart;
	}

	std::shared_ptr<EmitterSettings> ParticleEmitter::GetSettingsForEditor()
	{
		myEditorSpecifics.myIsEditorEmitter = true;
		return mySettings;
	}

	void ParticleEmitter::CreateCommands(const Time & aDeltaTime, const Vector3f & aPosition)
	{
		myEmittingCoolDown += aDeltaTime;
		if (myEmittingCoolDown >= mySettings->myEmitCoolDown)
		{
			unsigned short numberOfWrappings = static_cast<unsigned short>(myEmittingCoolDown.InSeconds() / mySettings->myEmitCoolDown.InSeconds());
			for (unsigned short iWrap = 0; iWrap < numberOfWrappings; ++iWrap)
			{
				mySystem->QueueParticle(CreateParticleCommand(aPosition + myPositionOffset));
			}
			myEmittingCoolDown = 0;
		}
	}

	void ParticleEmitter::Explode(const Time & aDeltaTime, const Vector3f & aPosition)
	{
		for (unsigned short iWrap = 0; iWrap < mySettings->myAmountOfParticles; ++iWrap)
		{
			mySystem->QueueParticle(CreateParticleCommand(aPosition + myPositionOffset));
		}

		if (myEditorSpecifics.myIsEditorEmitter == true)
		{
			myIsPaused = true;
		}
		else
		{
			myComponentPart->Kill();
		}
	}

	const ScheduledParticleCommand ParticleEmitter::CreateParticleCommand(const Vector3f & aPosition)
	{
		ParticleDeltaInfo deltaInfo;
		ParticleData data;
		ParticleLogic logic;

		deltaInfo.myStartColor = mySettings->myStartColor;
		deltaInfo.myEndColor = mySettings->myEndColor;
		deltaInfo.myEndSizeInPercent = mySettings->myEndSizeInPercent;
		deltaInfo.myRotationDelta = myRandomizer.GetRandomValue(mySettings->myMinMaxRotationPerSecond.x, mySettings->myMinMaxRotationPerSecond.y);

		data.myPosition = aPosition;
		data.mySize = myRandomizer.GetRandomValue(mySettings->myMinMaxSize.x, mySettings->myMinMaxSize.y);
		data.myColor = mySettings->myStartColor;
		data.myColor.w = 1.f;

		Matrix33f rotationSpace;
		rotationSpace.CreateRotateAroundZ(DEGREES_TO_RADIANSF(myRandomizer.GetRandomValue(mySettings->myMinMaxStartRotation.x, mySettings->myMinMaxStartRotation.y)));
		logic.myRotation = rotationSpace;

		logic.myShouldBeRotatedInDirection = mySettings->myShouldRotateInDirection;

		Vector2f textureSize = mySystem->GetParticleAtlasSize(); 
		//From pixel coords to normalized coords
		data.myUV = Vector4f(
			mySettings->myTextureUV.x / textureSize.x, mySettings->myTextureUV.y / textureSize.y,
			mySettings->myTextureUV.z / textureSize.x, mySettings->myTextureUV.w / textureSize.y);

		logic.myVelocity.x = myRandomizer.GetRandomValue(mySettings->myMinMaxVelocityX.x, mySettings->myMinMaxVelocityX.y);
		logic.myVelocity.y = myRandomizer.GetRandomValue(mySettings->myMinMaxVelocityY.x, mySettings->myMinMaxVelocityY.y);
		logic.myVelocity.z = myRandomizer.GetRandomValue(mySettings->myMinMaxVelocityZ.x, mySettings->myMinMaxVelocityZ.y);
		logic.myStartLifeTime = Time::FromSeconds(myRandomizer.GetRandomValue(mySettings->myMinMaxLifeTime.x, mySettings->myMinMaxLifeTime.y));
		logic.myLifeTimeLeft = logic.myStartLifeTime;
		logic.myStartSize = data.mySize;

		return ScheduledParticleCommand(deltaInfo, data, logic);
	}

}