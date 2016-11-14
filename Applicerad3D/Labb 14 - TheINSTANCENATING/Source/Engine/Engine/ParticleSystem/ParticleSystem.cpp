#include "stdafx.h"
#include "ParticleSystem.h"
#include "ParticleSystemStructs.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "ParticleEffect.h"
#include "../Game/Game/GenericGameMessages.h"
#include "Engine/ParticleSystem/ParticleEmitter.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"

namespace ENGINE_NAMESPACE
{

	ParticleSystem::ParticleSystem(SB::Scene & aScene/*const unsigned short aMaxAmountOfParticles*//*= 1024 * 8*/)
	{
		LoadParticleEmitterTypes();
		myVertexBuffer = std::make_shared<VertexBuffer<ParticleData>>(nullptr, MaxAmountParticles, false);
		myEffect = std::make_shared<ParticleEffect>();

		myTextureAtlas = Engine::GetInstance().GetResourceManager().Get<Texture>("Assets/Textures/particleAtlas.dds");
		myScene = &aScene;
	}

	ParticleSystem::~ParticleSystem()
	{
	}

	void ParticleSystem::Update(const Time & aDeltaTime)
	{
		//TODO add threading here?, or where this is called.
		for (unsigned short iParticle = 0; iParticle < myParticleInstancesData.Size(); ++iParticle)
		{
			if (UpdateParticle(iParticle, aDeltaTime) == false && iParticle != 0)
			{
				--iParticle; // particle died
			}
		}
	}

	void ParticleSystem::Render() const
	{
		if (myParticleInstancesData.Size() > 0)
		{
			Engine::GetInstance().GetRenderer().DisableDepthWrite();
			myTextureAtlas->BindToPS(0);

			myVertexBuffer->UpdateData(&myParticleInstancesData[0], myParticleInstancesData.Size(), true);

			myVertexBuffer->Bind(0);
			myEffect->Bind();

			Engine::GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			Engine::GetRenderer().GetContext()->Draw(myParticleInstancesData.Size(), 0);
			Engine::GetInstance().GetRenderer().EnableDepth();
		}
	}

	void ParticleSystem::QueueParticle(const ScheduledParticleCommand aCommand)
	{
		myQueuedParticles.Add(aCommand);
	}

	void ParticleSystem::SpawnQueuedParticles()
	{
		if (static_cast<int>(myParticleInstancesData.Size()) + static_cast<int>(myQueuedParticles.Size()) > MaxAmountParticles)
		{
			Error("Particle System Error - System ran out of particles!\nTell a programmer to increase upper limit,\nor use fewer emitters/edit emitters to not spawn so many particles!");
		}

		for (unsigned short iParticle = 0; iParticle < myQueuedParticles.Size(); ++iParticle)
		{
			myParticleInstancesDeltaInfo.Add(myQueuedParticles[iParticle].myDeltaInfo);
			myParticleInstancesData.Add(myQueuedParticles[iParticle].myData);
			myParticleInstancesLogic.Add(myQueuedParticles[iParticle].myLogic);
		}

		myQueuedParticles.RemoveAll();
	}

	bool ParticleSystem::UpdateParticle(const unsigned short anIndex, const Time & aDeltaTime)
	{
		float progress = myParticleInstancesLogic[anIndex].myLifeTimeLeft.InSeconds() / myParticleInstancesLogic[anIndex].myStartLifeTime.InSeconds();
		float reverseProgress = (1.f - progress);

		myParticleInstancesLogic[anIndex].myLifeTimeLeft -= aDeltaTime;

		if (myParticleInstancesLogic[anIndex].myLifeTimeLeft.InSeconds() <= 0.f)
		{
			myParticleInstancesDeltaInfo.RemoveCyclicAtIndex(anIndex);
			myParticleInstancesData.RemoveCyclicAtIndex(anIndex);
			myParticleInstancesLogic.RemoveCyclicAtIndex(anIndex);

			return false;
		}

		bool derpyMode = false;
		if (derpyMode == true) // Saved because it looks funny. Who know, might be useful :D
		{
			Vector4f newPos =myParticleInstancesLogic[anIndex].myVelocity;
			newPos = newPos * myScene->GetCamera().GetTransformation().GetInverse();
			newPos = newPos * myScene->GetCamera().GetProjectionMatrix();

			Vector2f actualVelocity(newPos.x, newPos.y);
			actualVelocity.Normalize();
			float angle = acos(actualVelocity.x);
			if (actualVelocity.y > 0.f)
			{
				angle *= -1.f;
			}
			float testy = RADIANS_TO_DEGREESF(angle);
			Matrix33f temp;

			myParticleInstancesLogic[anIndex].myRotation = temp.Rotate2D(angle);
		}

		else if (myParticleInstancesLogic[anIndex].myShouldBeRotatedInDirection == true)
		{
			Vector2f oldPos = myScene->GetCamera().WorldToScreen(myParticleInstancesData[anIndex].myPosition);
			Vector2f newPos = myScene->GetCamera().WorldToScreen(myParticleInstancesData[anIndex].myPosition + myParticleInstancesLogic[anIndex].myVelocity);

			Vector2f actualVelocity = newPos - oldPos;
			actualVelocity.Normalize();
			float angle = acos(actualVelocity.x);
			if (actualVelocity.y > 0.f)
			{
				angle *= -1.f;
			}
			float testy = RADIANS_TO_DEGREESF(angle);
			Matrix33f temp;

			myParticleInstancesLogic[anIndex].myRotation = temp.Rotate2D(angle);//Matrix33f::CreateRotateAroundZ(angle);
		}
		else
		{
			myParticleInstancesLogic[anIndex].myRotation.Rotate2D(DEGREES_TO_RADIANSF(myParticleInstancesDeltaInfo[anIndex].myRotationDelta * aDeltaTime.InSeconds()));
		}

		myParticleInstancesData[anIndex].myRotation = Vector4f(
			myParticleInstancesLogic[anIndex].myRotation.m11, 
			myParticleInstancesLogic[anIndex].myRotation.m12, 
			myParticleInstancesLogic[anIndex].myRotation.m21, 
			myParticleInstancesLogic[anIndex].myRotation.m22);

		myParticleInstancesData[anIndex].myPosition += myParticleInstancesLogic[anIndex].myVelocity * aDeltaTime.InSeconds();
		Vector4f endSample = (myParticleInstancesDeltaInfo[anIndex].myEndColor * reverseProgress);
		Vector4f startSample = (myParticleInstancesDeltaInfo[anIndex].myStartColor * progress);

		Vector4f currentColor = startSample + endSample;

		myParticleInstancesData[anIndex].myColor = currentColor;

		float endSize = myParticleInstancesLogic[anIndex].myStartSize * myParticleInstancesDeltaInfo[anIndex].myEndSizeInPercent;

		float size = myParticleInstancesLogic[anIndex].myStartSize + ((endSize - myParticleInstancesLogic[anIndex].myStartSize) * reverseProgress);

		myParticleInstancesData[anIndex].mySize = size;

		return true;
	}

	void ParticleSystem::ShutDownCleanUp()
	{
		myParticleInstancesData.RemoveAll();
		myParticleInstancesData.RemoveAll();
		myParticleInstancesLogic.RemoveAll();

		myEmittersInstances.RemoveAll();

		myVertexBuffer = nullptr;
		myEffect = nullptr;
	}

	std::shared_ptr<ParticleEmitter> ParticleSystem::CreateEmitter(const std::string & aEmitterType)
	{
		if (myEmitterTypes.find(aEmitterType) == myEmitterTypes.end())
		{
			Error("\nParticle System Error - Tried to create an emitter which we don't have!\n\nEmitterType :  " + aEmitterType + "\nDid you spell the emitter type name wrong?\n\nAssets/Data/ParticleEmitters/particleEmitters.json contains all possible emitter types.\n");
		}

		std::shared_ptr<EmitterSettings> settings = myEmitterTypes[aEmitterType];

		std::shared_ptr<ParticleEmitter> emitter = std::make_shared<ParticleEmitter>(settings, *this);

		return emitter;
	}

	std::shared_ptr<ParticleEmitter> ParticleSystem::CreateEmptyEmitter()
	{
		std::shared_ptr<EmitterSettings> settings = myEmitterTypes["Template"];
		std::shared_ptr<ParticleEmitter> emitter = std::make_shared<ParticleEmitter>(settings, *this);
		return emitter;
	}

	ReceiveResult ParticleSystem::Receive(const EndOfFrameMessage & aMessage)
	{
		SpawnQueuedParticles();
		return ReceiveResult::eContinue;
	}

	Vector2f ParticleSystem::GetParticleAtlasSize() const
	{
		return myTextureAtlas->GetSize();
	}

	void ParticleSystem::RemoveEmitterType(const std::string & aName)
	{
		if (myEmitterTypes.find(aName) == myEmitterTypes.end())
		{
			Error("\nParticle System Error - Tried to remove an emitter which we don't have!\n\nEmitterType :  " + aName + "\nDid you spell the emitter type name wrong?\n\nAssets/Data/ParticleEmitters/particleEmitters.json contains all possible emitter types.\n");
		}
		myEmitterTypes.erase(aName);
	}

	void ParticleSystem::AddEmitterType(const EmitterSettings & someSettings, const std::string & aName)
	{
		std::shared_ptr<EmitterSettings> emitter = std::make_shared<EmitterSettings>();
		*emitter = someSettings;
		std::pair<std::string, std::shared_ptr<EmitterSettings>> prettyEmitter(aName, emitter);
		myEmitterTypes.insert(prettyEmitter);
	}

	void ParticleSystem::SaveEmitterTypes() const
	{

	}

	std::shared_ptr<Texture> ParticleSystem::GetAtlas()
	{
		return myTextureAtlas;
	}

	void ParticleSystem::LoadParticleEmitterTypes()
	{
		SB::DataDocument doc;
		SB::Data::Open("Assets/Data/ParticleEmitters/particleEmitters.json", doc);

		SB::DataNode emittersRoot = doc["emitters"];

		for (unsigned short i = 0; i < emittersRoot.Capacity(); ++i)
		{
			std::shared_ptr<EmitterSettings> emitter = std::make_shared<EmitterSettings>();

			std::string emitterName = emittersRoot[i]["name"].GetString();

			SB::DataNode particle = emittersRoot[i]["particle"];

			emitter->myStartColor.x = particle["startColor"][0].GetFloat();
			emitter->myStartColor.y = particle["startColor"][1].GetFloat();
			emitter->myStartColor.z = particle["startColor"][2].GetFloat();
			emitter->myStartColor.w = particle["startColor"][3].GetFloat();

			emitter->myEndColor.x = particle["endColor"][0].GetFloat();
			emitter->myEndColor.y = particle["endColor"][1].GetFloat();
			emitter->myEndColor.z = particle["endColor"][2].GetFloat();
			emitter->myEndColor.w = particle["endColor"][3].GetFloat();
			
			SB::DataNode velocities = emittersRoot[i]["velocity"];

			SB::DataNode xVelocity = velocities["x"];
			emitter->myMinMaxVelocityX = Vector2f(xVelocity["min"].GetFloat(), xVelocity["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxVelocityX, emitterName + " ~ velocity X");

			SB::DataNode yVelocity = velocities["y"];
			emitter->myMinMaxVelocityY = Vector2f(yVelocity["min"].GetFloat(), yVelocity["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxVelocityY, emitterName + " ~ velocity y");
			
			SB::DataNode zVelocity = velocities["z"];
			emitter->myMinMaxVelocityZ = Vector2f(zVelocity["min"].GetFloat(), zVelocity["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxVelocityZ, emitterName + " ~ velocity z");

			SB::DataNode rotationPerSecond = emittersRoot[i]["rotationPerSecond"];
			emitter->myMinMaxRotationPerSecond = Vector2f(rotationPerSecond["min"].GetFloat(), rotationPerSecond["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxRotationPerSecond, emitterName + " ~ rotation per second");

			SB::DataNode startRotation = emittersRoot[i]["startRotation"];
			emitter->myMinMaxStartRotation = Vector2f(startRotation["min"].GetFloat(), startRotation["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxStartRotation, emitterName + " ~ start rotation");

			emitter->myShouldRotateInDirection = emittersRoot[i]["shouldRotateInDirection"].GetBool();

			SB::DataNode lifeTime = emittersRoot[i]["lifeTime"];
			emitter->myMinMaxLifeTime = Vector2f(lifeTime["min"].GetFloat(), lifeTime["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxLifeTime, emitterName + " ~ lifetime");

			SB::DataNode size = emittersRoot[i]["size"];
			emitter->myMinMaxSize = Vector2f(size["min"].GetFloat(), size["max"].GetFloat());
			ErrorCheckMinMaxValues(emitter->myMinMaxSize, emitterName + " ~ size");

			emitter->myEndSizeInPercent = emittersRoot[i]["endSizeInPercent"].GetFloat();

			if (emittersRoot[i].HasMember("isExplosion") == true)
			{
				emitter->myIsExplosion = emittersRoot[i]["isExplosion"].GetBool();
			}
			else
			{
				emitter->myIsExplosion = false;
			}

			emitter->myTextureUV.x = emittersRoot[i]["textureUV"][0].GetFloat();
			emitter->myTextureUV.y = emittersRoot[i]["textureUV"][1].GetFloat();
			emitter->myTextureUV.z = emittersRoot[i]["textureUV"][2].GetFloat();
			emitter->myTextureUV.w = emittersRoot[i]["textureUV"][3].GetFloat();

			emitter->myEmitCoolDown = emittersRoot[i]["emitCooldown"].GetFloat();
			emitter->myAmountOfParticles = emittersRoot[i]["amountOfParticles"].GetUnsignedShort();

			std::pair<std::string, std::shared_ptr<EmitterSettings>> prettyEmitter(emitterName, emitter);
			myEmitterTypes.insert(prettyEmitter);
		}
	}

	void ParticleSystem::ErrorCheckMinMaxValues(const Vector2f & aMinMaxVector, const std::string & anErrorMessage) const
	{
		if (aMinMaxVector.x > aMinMaxVector.y)
		{
			Error("Particle Emitter settings error! - " + anErrorMessage + " - minimum value is greater than maximum value!");
		}
	}
}