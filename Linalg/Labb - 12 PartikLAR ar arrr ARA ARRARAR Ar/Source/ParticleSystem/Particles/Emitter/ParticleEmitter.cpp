#include "stdafx.h"
#include "ParticleEmitter.h"
#include "../Manager/ParticleSystemManager.h"
#include <tga2d/sprite/sprite.h>
#include <Utility/Randomizer/Randomizer.h>

ParticleEmitter::ParticleEmitter()
{
	myEmissionRateAlarm.SetAlarmTimeLength(15.f);
	myEmissionRateAlarm.SetResetBool(true);
	myLifeAlarm.SetResetBool(false);
	myImActive = false;
	myLocalSpaceIsActive = false;

	myRandomizer = new Randomizer(1.f, 1.f);

	myRotationPerSecond = Vector3f::Zero;
	myOrientation.SetSpaceData(Matrix44f::Identity);
}


ParticleEmitter::~ParticleEmitter()
{
	delete myRandomizer;
	myRandomizer = nullptr;

	delete myParticlesTexture;
	myParticlesTexture = nullptr;
}

void ParticleEmitter::Update(const float aDeltaTime)
{
	if ((myImActive == true)  && 
		(myLifeAlarm.GetProgress() < 1.f))
	{

		Rotate(aDeltaTime);

		if (myEmissionRateAlarm.GetProgress() == 1.f)
		{
			FireParticle();
		}
	}
	else
	{
		myImActive = false;
	}
}

void ParticleEmitter::Init(const float aEmissionRate, 
	const float aEmitterLiftetime, 
	const Vector3f aMinPos, 
	const Vector3f aMaxPos, 
	const Vector2f aParticleLifeTimeRange,
	const Vector3f aRotationInDegreesPerSecond,
	const Vector3f aMinVelocity, 
	const Vector3f aMaxVelocity, 
	const char * aTexturePath, 
	const bool aUseLocalSpace)
{
	myEmissionRateAlarm.SetAlarmTimeLength(1.f / aEmissionRate);
	myLifeAlarm.SetAlarmTimeLength(aEmitterLiftetime);

	myMaxPos = aMaxPos;
	myMinPos = aMinPos;

	myParticleLifeTimeRange = aParticleLifeTimeRange;

	myParticleMinVelocity = aMinVelocity;
	myParticleMaxVelocity = aMaxVelocity;

	myParticlesTexture = new DX2D::CSprite(aTexturePath);

	myLocalSpaceIsActive = aUseLocalSpace;

	myRotationPerSecond = aRotationInDegreesPerSecond;
	//
}

void ParticleEmitter::Rotate(const float aDeltaTime)
{
	Vector3f tempPos = myOrientation.GetSpaceData().GetPosition();
	myOrientation.SetWorldPosition(Vector3f::Zero);
	myOrientation.RotateX(DEGRESS_TO_RADIANSF(myRotationPerSecond.x * aDeltaTime));
	myOrientation.RotateY(DEGRESS_TO_RADIANSF(myRotationPerSecond.y * aDeltaTime));
	myOrientation.RotateZ(DEGRESS_TO_RADIANSF(myRotationPerSecond.z * aDeltaTime));
	
	myOrientation.SetWorldPosition(tempPos);
}
void ParticleEmitter::FireParticle()
{
	Particle * tempParticle1 = ParticleSystemManager::ActivateParticle();

	if (tempParticle1 != nullptr)
	{
		tempParticle1->myPosition = GetRandomizedVector(myMinPos, myMaxPos) *  myOrientation.GetSpaceData();
		tempParticle1->myTexture = myParticlesTexture;
		tempParticle1->myVelocity = GetRandomizedVector(myParticleMinVelocity, myParticleMaxVelocity) *  myOrientation.GetSpaceData();
		tempParticle1->myTimeLeft = myRandomizer->GetRandomValue(myParticleLifeTimeRange.x, myParticleLifeTimeRange.y);
		tempParticle1->myAlpha = 0.1f;
		tempParticle1->myAlphaDelta = 0.4f;
		if (myLocalSpaceIsActive == true)
		{
			tempParticle1->myEmitterSpace = &myOrientation;
		}
					 
		tempParticle1->myIsAffectedByGravity = true;
		tempParticle1->myGravity = Vector3f(0.f, -0.05f, 0.f);
	}
}

Vector3f ParticleEmitter::GetRandomizedVector(const Vector3f aMinVector, const Vector3f aMaxVector)
{
	const float x = myRandomizer->GetRandomValue(aMinVector.x, aMaxVector.x);
	const float y = myRandomizer->GetRandomValue(aMinVector.y, aMaxVector.y);
	const float z = myRandomizer->GetRandomValue(aMinVector.z, aMaxVector.z);
	return Vector3f(x, y, z);
}