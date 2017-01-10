#include "stdafx.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "ParticleSystemStructs.h"
#include "ParticleComponent.h"
//#include <Utilities/Randomizer/DistributionShapes/RandomDistributionMantle.h>
//#include <Utilities/Randomizer/DistributionShapes/RandomDistributionSphere.h>
#include <Utilities/Randomizer/DistributionShapes/RandomDistributionRectangle.h>

namespace SB
{

	ParticleEmitter::ParticleEmitter(const std::shared_ptr<EmitterSettings> & someSettings, ParticleSystem & aSystem, const unsigned short aForceFieldsInstanceIndex)
	{
		myIsPaused = true;
		mySettings = someSettings;
		mySystem = &aSystem;
		myEmittingCoolDown = myRandomizer.GetRandomValue(0.f, mySettings->myEmitCoolDown.InSeconds());
		myShape = nullptr;
		myLayer = eParticleLayer::eWorld;
		myDynamicSizeMultiplier = 1.f;
		myComponentPart = nullptr;
		myForceFieldInstanceIndex = aForceFieldsInstanceIndex;
	}

	ParticleEmitter::ParticleEmitter()
	{
		myForceFieldInstanceIndex = USHRT_MAX;
		myIsPaused = true;
		mySettings = nullptr;
		myShape = nullptr;
	}

	ParticleEmitter::~ParticleEmitter()
	{
	}

	void ParticleEmitter::Update(const Time & aDeltaTime, const Matrix44f & aTransformation)
	{
		if (myIsPaused == false)
		{
			if (mySettings->myIsExplosion == true)
			{
				Explode(aDeltaTime, aTransformation);
				return;
			}

			CreateCommands(aDeltaTime, aTransformation);
		}
		if (myEditorSpecifics.myIsEditorEmitter == true) // ugly code for particle editor :/ special case for explosions
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
		mySystem->RemoveLocalForceAfterTime(myForceFieldInstanceIndex, mySettings->myMinMaxLifeTime.y);
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

	void ParticleEmitter::SetParticleLayer(const eParticleLayer & aLayer)
	{
		myLayer = aLayer;
	}

	void ParticleEmitter::SetDynamicSizeMultiplier(const float & aSize)
	{
		myDynamicSizeMultiplier = aSize;
	}

	void ParticleEmitter::CreateCommands(const Time & aDeltaTime, const Matrix44f & aTransformation)
	{
		if (myDynamicSizeMultiplier <= 0.05f)
		{
			return;
		}

		myEmittingCoolDown += aDeltaTime;
		if (myEmittingCoolDown >= mySettings->myEmitCoolDown)
		{
			Vector3f particlePosition = aTransformation.GetPosition() + (myPositionOffset * aTransformation);
			unsigned short numberOfWrappings = static_cast<unsigned short>(myEmittingCoolDown.InSeconds() / mySettings->myEmitCoolDown.InSeconds());
			MakeNumberOfCommands(aTransformation, particlePosition, numberOfWrappings);
			myEmittingCoolDown = 0;
		}
	}

	void ParticleEmitter::MakeNumberOfCommands(const Matrix44f & aTransformation, const Vector3f & aPosition, const unsigned short aNumberOfCommands)
	{
		Vector3f particlePosition = aPosition;
		for (unsigned short iWrap = 0; iWrap < aNumberOfCommands; ++iWrap)
		{
			if (myShape != nullptr)
			{
				particlePosition += (myShape->GetRandomPoint() * aTransformation);
			}
			mySystem->QueueParticle(CreateParticleCommand(particlePosition));
		}
	}

	void ParticleEmitter::Explode(const Time & aDeltaTime, const Matrix44f & aTransformation)
	{
		MakeNumberOfCommands(aTransformation, aTransformation.GetPosition() + (myPositionOffset * aTransformation), mySettings->myAmountOfParticles);
		
		if (myComponentPart == nullptr) //an explosion on a component should remove its object
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
		data.mySize = myRandomizer.GetRandomValue(mySettings->myMinMaxSize.x, mySettings->myMinMaxSize.y) * myDynamicSizeMultiplier;
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

		logic.myGravity = mySettings->myGravity;
		logic.myVelocity.x = myRandomizer.GetRandomValue(mySettings->myMinMaxVelocityX.x, mySettings->myMinMaxVelocityX.y);
		logic.myVelocity.y = myRandomizer.GetRandomValue(mySettings->myMinMaxVelocityY.x, mySettings->myMinMaxVelocityY.y);
		logic.myVelocity.z = myRandomizer.GetRandomValue(mySettings->myMinMaxVelocityZ.x, mySettings->myMinMaxVelocityZ.y);
		logic.myStartLifeTime = Time::FromSeconds(myRandomizer.GetRandomValue(mySettings->myMinMaxLifeTime.x, mySettings->myMinMaxLifeTime.y));
		logic.myLifeTimeLeft = logic.myStartLifeTime;
		logic.myStartSize = data.mySize;

		logic.myForceFieldInstanceIndex = myForceFieldInstanceIndex;

		return ScheduledParticleCommand(deltaInfo, data, logic, myLayer);
	}
}