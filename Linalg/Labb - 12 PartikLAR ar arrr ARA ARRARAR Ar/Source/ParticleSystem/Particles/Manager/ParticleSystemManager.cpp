#include "stdafx.h"
#include "ParticleSystemManager.h"
#include <Timer/Timer.h>
#include <JSONParser/JSONParser.h>
//#include <JSONParser/picojson-master/picojson.h>




ParticleSystemManager * ParticleSystemManager::ourInstance = nullptr;;



void ParticleSystemManager::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new ParticleSystemManager();
	}
}

void ParticleSystemManager::Destroy()
{
	if (ourInstance != nullptr)
	{
		delete ourInstance;
		ourInstance = nullptr;
	}
}








ParticleSystemManager::ParticleSystemManager()
{
	Setup();
	myForceFields.Init(10);
	SetEmitter();
}


ParticleSystemManager::~ParticleSystemManager()
{
}


void ParticleSystemManager::Setup()
{
	//maybe do other stuff here.
}

void ParticleSystemManager::SetEmitter()
{

	picojson::object emitter = JSONParser::GetDaObject("Emitter").get<picojson::object>();

	Vector3f minPosition;
	Vector3f maxPosition;

	Vector3f minVelocity;
	Vector3f maxVelocity;

	JSONParser::GetMinMaxRangeVectors(emitter["MinMaxPosArea"], minPosition, maxPosition);
	JSONParser::GetMinMaxRangeVectors(emitter["MinMaxVelocity"], minVelocity, maxVelocity);

	myTestEmitter.Init(JSONParser::GetFloatFromValue(emitter["EmissionRate"]),
		JSONParser::GetFloatFromValue(emitter["EmitterLifeTimeLength"]),
		minPosition, maxPosition,
		JSONParser::GetVector2FromValue(emitter["ParticleLifeTimeRange"]),
		JSONParser::GetVector3FromValue(emitter["RotationInDegreesPerSecond"]),
		minVelocity, maxVelocity,
		emitter["ParticleTexturePath"].get<std::string>().c_str(),
		emitter["ParticlesUseEmitterSpace"].get<bool>());
	myTestEmitter.ActiveEmitter();

	SetForceField();
}

void ParticleSystemManager::SetForceField()
{
	picojson::object forceField = JSONParser::GetDaObject("ForceField").get<picojson::object>();

	ForceField temp;

	temp.myPosition = JSONParser::GetVector3FromValue(forceField["Position"]);
	temp.myRadius = JSONParser::GetFloatFromValue(forceField["Radius"]);
	temp.myStrength = JSONParser::GetFloatFromValue(forceField["Strength"]);

	myForceFields.Add(temp);

}

void ParticleSystemManager::UpdateParticle(const float aDeltaTime, Particle & aParticle)
{
	aParticle.myTimeLeft -= aDeltaTime;
	if (aParticle.myTimeLeft <= 0.f)
	{
		aParticle.myIsActive = false;
		aParticle.myTimeLeft = 0.f;
		return;
	}

	aParticle.myAlpha += aParticle.myAlphaDelta * aDeltaTime;

	aParticle.mySize += aParticle.mySizeDelta * aDeltaTime;

	if (aParticle.myIsAffectedByGravity == true)
	{
		aParticle.myVelocity += aParticle.myGravity * aDeltaTime;
	}

	aParticle.myPosition += aParticle.myVelocity * aDeltaTime;

	for (unsigned short i = 0; i < myForceFields.Size(); ++i)
	{
		ApplyForceField(myForceFields[i], aParticle, aDeltaTime);

	}
}

void ParticleSystemManager::InternalUpdate(const float aDeltaTime)
{
	myTestEmitter.Update(aDeltaTime);

	for (size_t iParticles = 0; iParticles < myParticles.size(); ++iParticles)
	{
		if (myParticles[iParticles].myIsActive == true)
		{
			UpdateParticle(aDeltaTime, myParticles[iParticles]);
		}
	}
}

void ParticleSystemManager::InternalDraw()
{
	for (size_t iParticles = 0; iParticles < myParticles.size(); ++iParticles)
	{
		if (myParticles[iParticles].myIsActive == true)
		{
			GameObjectsManager::AddRenderToQue(myParticles[iParticles].Draw());
		}
	}
}

void ParticleSystemManager::ApplyForceField(const ForceField & aForceField, Particle & aParticle, const float aDeltaTime)
{
	if ((aParticle.myPosition - aForceField.myPosition).Length2() < (aForceField.myRadius * aForceField.myRadius))
	{
		Vector3f tempDirection = (aForceField.myPosition - aParticle.myPosition).Normalize();
		
		aParticle.myVelocity += tempDirection * aForceField.myStrength * aDeltaTime;
	}
}
