#include "stdafx.h"
#include "ParticleSystem.h"
#include "ParticleSystemStructs.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "ParticleEffect.h"
#include "../Game/Game/GenericGameMessages.h"
#include "Engine/ParticleSystem/ParticleEmitter.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Camera/Camera.h"

namespace SB
{

	ParticleSystem::ParticleSystem(SB::Scene & aScene/*const unsigned short aMaxAmountOfParticles*//*= 1024 * 8*/)
	{
		LoadParticleEmitterTypes();
		myVertexBuffer = std::make_shared<VertexBuffer<ParticleData>>(nullptr, MaxAmountParticles, false);
		myEffect = std::make_shared<ParticleEffect>();

		myTextureAtlas = Engine::GetInstance().GetResourceManager().Get<Texture>("Assets/Textures/particleAtlas.dds");
		myScene = &aScene;

		myLocalForceFields.Resize(EightOfMax);
		for (unsigned short i = EightOfMax; i > 0 ; --i)
		{
			myFreeLocalForceFieldIndexes.Push(i);
		}
		myFreeLocalForceFieldIndexes.Push(0);
	}

	ParticleSystem::~ParticleSystem()
	{
	}

	void ParticleSystem::Update(const Time & aDeltaTime)
	{
		for (unsigned short iParticle = 0; iParticle < myParticleInstancesData.Size(); ++iParticle)
		{
			if (UpdateWorldParticle(iParticle, aDeltaTime) == false && iParticle != 0)
			{
				--iParticle; 
			}
		}
	}

	void ParticleSystem::RenderWorldParticles(const Camera & aCamera) const
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
#ifndef PUBLISH
		if (static_cast<int>(myParticleInstancesData.Size()) + static_cast<int>(myQueuedParticles.Size()) > MaxAmountParticles)
		{
			Error("Particle System Error - System ran out of particles!\nTell a programmer to increase upper limit,\nor use fewer emitters/edit emitters to not spawn so many particles!");
		}
#endif

		for (unsigned short iParticle = 0; iParticle < myQueuedParticles.Size(); ++iParticle)
		{
			if (MaxAmountParticles <= myParticleInstancesData.Size())
			{
				break;
			}

			switch (myQueuedParticles[iParticle].myLayer)
			{
			case eParticleLayer::eWorld:
				myParticleInstancesDeltaInfo.Add(myQueuedParticles[iParticle].myDeltaInfo);
				myParticleInstancesData.Add(myQueuedParticles[iParticle].myData);
				myParticleInstancesLogic.Add(myQueuedParticles[iParticle].myLogic);
				break;
			case eParticleLayer::eBelowGUI:
				Error("You tried to add above GUI particles, but I disabled them since we're not using any and it takes up a lot of space to potentially have them c:");
				break;
			case eParticleLayer::eAboveGUI:
				Error("You tried to add above GUI particles, but I disabled them since we're not using any and it takes up a lot of space to potentially have them c:");
				break;
			default:
				Error("Particle System Error - contact Ylf");
			}
		}

		myQueuedParticles.RemoveAll();
	}

	bool ParticleSystem::UpdateWorldParticle(const unsigned short anIndex, const Time & aDeltaTime)
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

		Vector3f forceFieldInfluence;
		GrowingArray<ParticleForceField> & localFFs = myLocalForceFields[myParticleInstancesLogic[anIndex].myForceFieldInstanceIndex];
		for (unsigned short iFF = 0; iFF < localFFs.Size(); ++iFF)
		{
			Vector3f direction = (localFFs[iFF].myForceField.myPosition - myParticleInstancesData[anIndex].myPosition);
			if (direction.Length() < localFFs[iFF].myForceField.myRadius)
			{
				forceFieldInfluence += direction.GetNormalized() * localFFs[iFF].myGravity;
			}
		}

		myParticleInstancesLogic[anIndex].myVelocity += myParticleInstancesLogic[anIndex].myGravity * aDeltaTime.InSeconds();
		myParticleInstancesLogic[anIndex].myVelocity += forceFieldInfluence * aDeltaTime.InSeconds();
		Vector3f movement = myParticleInstancesLogic[anIndex].myVelocity * aDeltaTime.InSeconds();

		if (myParticleInstancesLogic[anIndex].myShouldBeRotatedInDirection == true)
		{

			Vector2f oldPos = myScene->GetCamera().WorldToScreen(myParticleInstancesData[anIndex].myPosition);
			Vector2f newPos = myScene->GetCamera().WorldToScreen(myParticleInstancesData[anIndex].myPosition + movement);

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

		myParticleInstancesData[anIndex].myPosition += movement;
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

		myLocalForceFields.RemoveAll();

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
		unsigned short forceInstanceIndex = myFreeLocalForceFieldIndexes.Pop();
		std::shared_ptr<ParticleEmitter> emitter = std::make_shared<ParticleEmitter>(settings, *this, forceInstanceIndex);
		myLocalForceFields[forceInstanceIndex] = settings->myForceFieldsSettings;

		return emitter;
	}


	std::shared_ptr<ParticleEmitter> ParticleSystem::CreateEmptyEmitter()
	{
		std::shared_ptr<EmitterSettings> settings = myEmitterTypes["Template"];
		std::shared_ptr<ParticleEmitter> emitter = std::make_shared<ParticleEmitter>(settings, *this, myFreeLocalForceFieldIndexes.Pop());
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
		myQueuedParticles.RemoveAll();
		myParticleInstancesDeltaInfo.RemoveAll();
		myParticleInstancesData.RemoveAll();
		myParticleInstancesLogic.RemoveAll();

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

	void ParticleSystem::ModifyEmitterType(const EmitterSettings & someSettings, const std::string & aNewName, const std::string & anOldName)
	{
		RemoveEmitterType(anOldName);
		AddEmitterType(someSettings, aNewName);
	}

	void ParticleSystem::SaveEmitterTypes(const std::string & aFile) const
	{
		JsonSerializer saveWriter(aFile.c_str());

		saveWriter.WriteArray("emitters");

		for (auto iEmitter = myEmitterTypes.begin(); iEmitter != myEmitterTypes.end(); iEmitter++)
		{
			saveWriter.WriteObject();

			saveWriter.WriteNode("name", iEmitter->first);

			saveWriter.WriteNode("eEmitterShape", 0);//TODO, us ereal emitter shape enum
			saveWriter.WriteObject("particle");

			saveWriter.WriteArray("startColor");
			saveWriter.WriteArrayValue(iEmitter->second->myStartColor.x);
			saveWriter.WriteArrayValue(iEmitter->second->myStartColor.y);
			saveWriter.WriteArrayValue(iEmitter->second->myStartColor.z);
			saveWriter.WriteArrayValue(iEmitter->second->myStartColor.w);
			saveWriter.StepOut();

			saveWriter.WriteArray("endColor");
			saveWriter.WriteArrayValue(iEmitter->second->myEndColor.x);
			saveWriter.WriteArrayValue(iEmitter->second->myEndColor.y);
			saveWriter.WriteArrayValue(iEmitter->second->myEndColor.z);
			saveWriter.WriteArrayValue(iEmitter->second->myEndColor.w);
			saveWriter.StepOut();

			saveWriter.StepOut();

			saveWriter.WriteArray("textureUV");
			saveWriter.WriteArrayValue(iEmitter->second->myTextureUV.x);
			saveWriter.WriteArrayValue(iEmitter->second->myTextureUV.y);
			saveWriter.WriteArrayValue(iEmitter->second->myTextureUV.z);
			saveWriter.WriteArrayValue(iEmitter->second->myTextureUV.w);
			saveWriter.StepOut();

			saveWriter.WriteObject("velocity");

			saveWriter.WriteArray("gravity");
			saveWriter.WriteArrayValue(iEmitter->second->myGravity.x);
			saveWriter.WriteArrayValue(iEmitter->second->myGravity.y);
			saveWriter.WriteArrayValue(iEmitter->second->myGravity.z);
			saveWriter.StepOut();

			saveWriter.WriteObject("x");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxVelocityX.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxVelocityX.y);
			saveWriter.StepOut();

			saveWriter.WriteObject("y");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxVelocityY.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxVelocityY.y);
			saveWriter.StepOut();

			saveWriter.WriteObject("z");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxVelocityZ.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxVelocityZ.y);
			saveWriter.StepOut();
			saveWriter.StepOut();

			saveWriter.WriteObject("rotationPerSecond");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxRotationPerSecond.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxRotationPerSecond.y);
			saveWriter.StepOut();

			saveWriter.WriteObject("startRotation");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxStartRotation.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxStartRotation.y);
			saveWriter.StepOut();


			saveWriter.WriteObject("lifeTime");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxLifeTime.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxLifeTime.y);
			saveWriter.StepOut();

			saveWriter.WriteObject("size");
			saveWriter.WriteNode("min", iEmitter->second->myMinMaxSize.x);
			saveWriter.WriteNode("max", iEmitter->second->myMinMaxSize.y);
			saveWriter.StepOut();

			saveWriter.WriteNode("endSizeInPercent", iEmitter->second->myEndSizeInPercent);

			saveWriter.WriteNode("shouldRotateInDirection", iEmitter->second->myShouldRotateInDirection);
			saveWriter.WriteNode("isExplosion", iEmitter->second->myIsExplosion);

			saveWriter.WriteNode("emitCooldown", iEmitter->second->myEmitCoolDown.InSeconds());
			saveWriter.WriteNode("amountOfParticles", iEmitter->second->myAmountOfParticles);

			saveWriter.WriteArray("localForceFields");
			for (unsigned short i = 0; i <  iEmitter->second->myForceFieldsSettings.Size(); ++i)
			{
				saveWriter.WriteObject();
				saveWriter.WriteArray("offsetFromEmitter");
				saveWriter.WriteArrayValue( iEmitter->second->myForceFieldsSettings[i].myForceField.myPosition.x);
				saveWriter.WriteArrayValue( iEmitter->second->myForceFieldsSettings[i].myForceField.myPosition.y);
				saveWriter.WriteArrayValue( iEmitter->second->myForceFieldsSettings[i].myForceField.myPosition.z);
				saveWriter.StepOut();
				saveWriter.WriteNode("radius", iEmitter->second->myForceFieldsSettings[i].myForceField.myRadius);
				saveWriter.WriteNode("gravity", iEmitter->second->myForceFieldsSettings[i].myGravity);
				saveWriter.StepOut();
			}
			saveWriter.StepOut();

			saveWriter.StepOut();
		}

		//saveWriter.WriteArray("globalForceFields");
		//for (unsigned short i = 0; i < iEmitter->second->myLocalForceFields.Size(); ++i)
		//{
		//	saveWriter.WriteObject();
		//	saveWriter.WriteArray("offsetFromEmitter");
		//	saveWriter.WriteArrayValue(iEmitter->second->myLocalForceFields[i].myForceField.myPosition.x);
		//	saveWriter.WriteArrayValue(iEmitter->second->myLocalForceFields[i].myForceField.myPosition.y);
		//	saveWriter.WriteArrayValue(iEmitter->second->myLocalForceFields[i].myForceField.myPosition.z);
		//	saveWriter.StepOut();
		//	saveWriter.WriteNode("radius", iEmitter->second->myLocalForceFields[i].myForceField.myRadius);
		//	saveWriter.WriteNode("gravity", iEmitter->second->myLocalForceFields[i].myGravity);
		//	saveWriter.StepOut();
		//}
		//saveWriter.StepOut();
	}

	SB::GrowingArray<std::string> ParticleSystem::GetEmitterNames() const
	{
		SB::GrowingArray<std::string> temp;

		for (auto iString = myEmitterTypes.begin(); iString != myEmitterTypes.end(); ++iString)
		{
			temp.Add(iString->first.c_str());
		}

		return temp;
	}

	std::shared_ptr<Texture> ParticleSystem::GetAtlas()
	{
		return myTextureAtlas;
	}

	void ParticleSystem::RemoveLocalForceAfterTime(const unsigned short aIndex, const Time & aDyingTimer)
	{
		ForceFieldDying temp;
		temp.myForceFieldInstanceIndex = aIndex;
		temp.myDyingTimer = aDyingTimer;
		myQueuedForceFieldDeaths.Add(temp);
	}



	void ParticleSystem::UpdateForceFieldDeaths(const Time & aDeltaTime)
	{
		for (unsigned short i = 0; i < myQueuedForceFieldDeaths.Size(); ++i)
		{
			myQueuedForceFieldDeaths[i].myDyingTimer -= aDeltaTime;
			if (myQueuedForceFieldDeaths[i].myDyingTimer.InSeconds() <= 0.f)
			{
				myFreeLocalForceFieldIndexes.Push(myQueuedForceFieldDeaths[i].myForceFieldInstanceIndex);
				myQueuedForceFieldDeaths.RemoveCyclicAtIndex(i);
				--i;
			}
		}
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

			emitter->myShape = static_cast<eEmitterShape>(emittersRoot[i]["eEmitterShape"].GetInt());
			if (emitter->myShape >= eEmitterShape::eEnumLength)
			{
				Error("Particle Settings error - " + emitterName +
					" Emitter using undefined emitter shape!\nLook in ParticleSystemStructs.h for types. \n\n0 is point shape, you can always use that.");
			}
			
			SB::DataNode velocities = emittersRoot[i]["velocity"];

			emitter->myGravity.x = velocities["gravity"][0].GetFloat();
			emitter->myGravity.y = velocities["gravity"][1].GetFloat();
			emitter->myGravity.z = velocities["gravity"][2].GetFloat();

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
			emitter->myIsExplosion = emittersRoot[i]["isExplosion"].GetBool();

			SB::DataNode localForceFields = emittersRoot[i]["localForceFields"];
			unsigned short objectCount = static_cast<unsigned short>(localForceFields.Capacity());
			for (unsigned short iFF = 0; iFF < objectCount; ++iFF)
			{
				ParticleForceField ff;
				ff.myForceField.myPosition.x = localForceFields[i]["offsetFromEmitter"][0].GetFloat();
				ff.myForceField.myPosition.y = localForceFields[i]["offsetFromEmitter"][1].GetFloat();
				ff.myForceField.myPosition.z = localForceFields[i]["offsetFromEmitter"][2].GetFloat();

				ff.myForceField.myRadius = localForceFields[i]["radius"].GetFloat();
				ff.myGravity = localForceFields[i]["gravity"].GetFloat();
				
				emitter->myForceFieldsSettings.Add(ff);
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