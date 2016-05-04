#include "stdafx.h"
#include "ParticleSystemManager.h"
#include <Timer/Timer.h>
#include <Distribution/Shapes/BoxDistibution.h>
#include <Distribution/Shapes/SphereDistribution.h>
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
	myEmitters.Init(10);

	picojson::array emitterArray = JSONParser::GetDaArray("Emitters");
	picojson::array forceFieldArray = JSONParser::GetDaArray("ForceFields");
	//picojson::object testderp = JSONParser::GetDaObject("Emitter").get<picojson::object>();

	for (picojson::array::iterator iEmitter = emitterArray.begin(); iEmitter != emitterArray.end(); ++iEmitter)
	{
		SetEmitter(iEmitter->get<picojson::object>());
	}

	/*for (picojson::array::iterator iForceField = forceFieldArray.begin(); iForceField != forceFieldArray.end(); ++iForceField)
	{
		SetGlobalForceFields(iForceField->get<picojson::object>());
	}*/

	SetGlobalForceFields(forceFieldArray);

	//SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	/*SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	/*SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());
	SetEmitter(JSONParser::GetDaObject("Emitter").get<picojson::object>());*/
}


ParticleSystemManager::~ParticleSystemManager()
{
}


void ParticleSystemManager::Setup()
{
	//maybe do other stuff here.
}

void ParticleSystemManager::SetEmitter(picojson::object & aEmitter)
{

	//picojson::object emitter = JSONParser::GetDaObject("Emitter").get<picojson::object>();

	

	Vector3f minVelocity;
	Vector3f maxVelocity;


	

	JSONParser::GetMinMaxRangeVectors(aEmitter["MinMaxVelocity"], minVelocity, maxVelocity);

	//myEmitters.Add(new ParticleEmitter());
	myEmitters.Add(ParticleEmitter());

	myEmitters.GetLast().Init(JSONParser::GetFloatFromValue(aEmitter["EmissionRate"]),
		JSONParser::GetFloatFromValue(aEmitter["EmitterLifeTimeLength"]),
		//minPosition, maxPosition,
		GetEmitterType(aEmitter["EmissionType"].get<picojson::object>()),
		JSONParser::GetVector2FromValue(aEmitter["ParticleLifeTimeRange"]),
		JSONParser::GetVector3FromValue(aEmitter["RotationInDegreesPerSecond"]),
		minVelocity, maxVelocity,
		JSONParser::GetVector3FromValue(aEmitter["Color"]),
		JSONParser::GetVector3FromValue(aEmitter["Gravity"]),
		JSONParser::GetVector2FromValue(aEmitter["StartEndAlpha"]),
		JSONParser::GetVector2FromValue(aEmitter["StartEndSize"]),
		aEmitter["ParticleTexturePath"].get<std::string>().c_str(),
		aEmitter["ParticlesUseEmitterSpace"].get<bool>());

	SetLocalForceFields(aEmitter["LocalForceFields"].get<picojson::array>(), myEmitters.GetLast().GetForceFieldArray());

	myEmitters.GetLast().ActiveEmitter();

	/*myTestEmitter.Init(JSONParser::GetFloatFromValue(emitter["EmissionRate"]),
		JSONParser::GetFloatFromValue(emitter["EmitterLifeTimeLength"]),
		minPosition, maxPosition,
		JSONParser::GetVector2FromValue(emitter["ParticleLifeTimeRange"]),
		JSONParser::GetVector3FromValue(emitter["RotationInDegreesPerSecond"]),
		minVelocity, maxVelocity,
		emitter["ParticleTexturePath"].get<std::string>().c_str(),
		emitter["ParticlesUseEmitterSpace"].get<bool>());
	myTestEmitter.ActiveEmitter();*/

	//SetForceField();
}

ForceField ParticleSystemManager::CreateForceField(picojson::object & forceField)
{
	ForceField temp;

	temp.myPosition = JSONParser::GetVector3FromValue(forceField["Position"]);
	temp.myRadius = JSONParser::GetFloatFromValue(forceField["Radius"]);
	temp.myStrength = JSONParser::GetFloatFromValue(forceField["Strength"]);

	return temp;
}



void ParticleSystemManager::UpdateParticle(const float aDeltaTime, Particle & aParticle)
{
	aParticle.myTimeLeft -= aDeltaTime;
	if (aParticle.myTimeLeft <= 0.f)
	{
		/*aParticle.myIsActive = false;
		aParticle.myTimeLeft = 0.f;*/
		aParticle.ResetParticle();
		return;
	}

	aParticle.myAlpha += aParticle.myAlphaDelta * aDeltaTime;

	aParticle.mySize += aParticle.mySizeDelta * aDeltaTime;

	if (aParticle.myIsAffectedByGravity == true)
	{
		aParticle.myVelocity += aParticle.myGravity * aDeltaTime;
	}

	for (unsigned short i = 0; i < myForceFields.Size(); ++i)
	{
		ApplyForceField(myForceFields[i], aParticle, aDeltaTime);

	}

	for (unsigned short iParticle = 0; iParticle < aParticle.myLocalForceFields->Size(); ++iParticle)
	{
		ApplyForceField((*aParticle.myLocalForceFields)[iParticle], aParticle, aDeltaTime);
	}

	aParticle.myPosition += aParticle.myVelocity * aDeltaTime;

	

	
}

BaseDistributionShape * ParticleSystemManager::GetEmitterType(picojson::object & aDistributionType)
{
	std::string typeName = aDistributionType["Type"].get<std::string>();
	if (typeName == "Box")
	{
		Vector3f minPosition;
		Vector3f maxPosition;

		JSONParser::GetMinMaxRangeVectors(aDistributionType["MinMaxPosArea"], minPosition, maxPosition);
		
		BoxDistibution * tempBox = new BoxDistibution();
		tempBox->SetBoxWithMinMax(minPosition, maxPosition);
		
		return tempBox;
	}
	else if (typeName == "Sphere")
	{
		SphereDistribution * tempSphere = new SphereDistribution();

		Vector3f spherePosition;
		float sphereRadius;

		JSONParser::GetSphereData(aDistributionType["PositionAndRadius"], spherePosition, sphereRadius);

		tempSphere->SetSphere(spherePosition, sphereRadius, JSONParser::GetFloatFromValue(aDistributionType["DistanceFromCenter"]));

		return tempSphere;
	}
}

void ParticleSystemManager::SetGlobalForceFields(picojson::array & aForceField)
{
	for (picojson::array::iterator iForceFields = aForceField.begin(); iForceFields != aForceField.end(); ++iForceFields)
	{
		myForceFields.Add(CreateForceField(iForceFields->get<picojson::object>()));
	}
}

void ParticleSystemManager::SetLocalForceFields(picojson::array& aForceField, CU::GrowingArray<ForceField> & aArrayToSet)
{
	for (picojson::array::iterator iForceFields = aForceField.begin(); iForceFields != aForceField.end(); ++iForceFields)
	{
		aArrayToSet.Add(CreateForceField(iForceFields->get<picojson::object>()));
	}
}

void ParticleSystemManager::InternalUpdate(const float aDeltaTime)
{
	for (size_t iEmitter = 0; iEmitter < myEmitters.Size(); ++iEmitter)
	{
		myEmitters[iEmitter].Update(aDeltaTime);
	}

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
	if ((aParticle.myPosition - aForceField.myPosition).Length2() <= (aForceField.myRadius * aForceField.myRadius))
	{
		Vector3f tempDirection = (aForceField.myPosition - aParticle.myPosition).Normalize();
		
		aParticle.myVelocity += tempDirection * aForceField.myStrength * aDeltaTime;
	}
}
