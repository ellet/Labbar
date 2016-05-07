#include "stdafx.h"
#include "ParticleEmitter.h"
#include "../Manager/ParticleSystemManager.h"
#include <tga2d/sprite/sprite.h>
#include <Utility/Randomizer/Randomizer.h>
#include <tga2d/sprite/sprite_batch.h>

ParticleEmitter::ParticleEmitter()
{
	myEmissionRateAlarm.SetAlarmTimeLength(15.f);
	myEmissionRateAlarm.SetResetBool(true);
	myLifeAlarm.SetResetBool(false);
	myImActive = false;
	myLocalSpaceIsActive = false;

	myParticleEndAlpha = 1.0f;
	myParticleStartAlpha = 1.0f;
	myRandomizer = new Randomizer(1.f, 1.f);

	myRotationPerSecond = Vector3f::Zero;
	myOrientation.SetSpaceData(Matrix44f::Identity);

	myParticleStartEndSize.x = 0.1f;
	myParticleStartEndSize.y = 1.0f;

	myParticleColor = Vector3f::One;

	//myParticlesTexture = nullptr;
	myParticleBatch = nullptr;
	myDistibutionStrategy = nullptr;

	myLocalForceFields.Init(1);
}


ParticleEmitter::ParticleEmitter(const ParticleEmitter& aParticleEmitter)
{
	*this = aParticleEmitter;
}

ParticleEmitter::~ParticleEmitter()
{
	delete myRandomizer;
	myRandomizer = nullptr;

	/*if (myParticlesTexture != nullptr)
	{
	delete myParticlesTexture;
	myParticlesTexture = nullptr;
	}*/


}

void ParticleEmitter::Update(const float aDeltaTime)
{

	float tempCheckProgress = myLifeAlarm.GetProgress();

	if ((myImActive == true)  && 
		(tempCheckProgress < 1.f))
	{

		Rotate(aDeltaTime);

		while (myEmissionRateAlarm.GetProgress() == 1.f)
		{
			FireParticle();
		}
	}
	else
	{
		if (myLifeAlarm.GetResetBool() == false)
		{
			myImActive = false;
		}
	}
}

void ParticleEmitter::Init(const float aEmissionRate,
	const float aEmitterLiftetime,
	//const Vector3f aMinPos, const Vector3f aMaxPos,
	BaseDistributionShape * const aDistributionShape,
	const Vector2f aParticleLifeTimeRange,
	const Vector3f aRotationInDegreesPerSecond,
	const Vector3f aMinVelocity,
	const Vector3f aMaxVelocity,
	const Vector3f aColor,
	const Vector3f aGravity,
	const Vector2f aStartAndEndAlpha,
	const Vector2f aStartEndSize,
	const char * aTexturePath,
	//const CU::GrowingArray<ForceField> & aArrayOfForceFields,
	const bool aUseLocalSpace)
{
	myEmissionRateAlarm.SetAlarmTimeLength(1.f / aEmissionRate);

	if (aEmitterLiftetime < 0.f)
	{
		myLifeAlarm.SetAlarmTimeLength(100.f);
		myLifeAlarm.SetResetBool(true);
	}
	else
	{
		myLifeAlarm.SetAlarmTimeLength(aEmitterLiftetime);
	}

	myParticleColor = aColor;

	myParticleStartAlpha = aStartAndEndAlpha.x;
	myParticleEndAlpha = aStartAndEndAlpha.y;

	myParticleStartEndSize = aStartEndSize;

	myParticleGravity = aGravity;
	/*myMaxPos = aMaxPos;
	myMinPos = aMinPos;*/

	myDistibutionStrategy = aDistributionShape;

	myParticleLifeTimeRange = aParticleLifeTimeRange;

	myParticleMinVelocity = aMinVelocity;
	myParticleMaxVelocity = aMaxVelocity;

	//myParticlesTexture = new DX2D::CSprite(aTexturePath);
	myParticleBatch = new DX2D::CSpriteBatch(false);
	myParticleBatch->Init(aTexturePath);

	myLocalSpaceIsActive = aUseLocalSpace;

	//myLocalForceFields = aArrayOfForceFields;

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
		tempParticle1->myPosition = myDistibutionStrategy->GetPositionInDistribution(); //GetRandomizedVector(myMinPos, myMaxPos) *  myOrientation.GetSpaceData();

		//tempParticle1->myTexture = myParticlesTexture;
		tempParticle1->mySpriteBatch = myParticleBatch;

		tempParticle1->myVelocity = GetRandomizedVector(myParticleMinVelocity, myParticleMaxVelocity) *  myOrientation.GetSpaceData();

		tempParticle1->myTimeLeft = myRandomizer->GetRandomValue(myParticleLifeTimeRange.x, myParticleLifeTimeRange.y);

		tempParticle1->myAlpha = myParticleStartAlpha;
		tempParticle1->myAlphaDelta = (myParticleEndAlpha - myParticleStartAlpha) / tempParticle1->myTimeLeft;

		tempParticle1->mySize = myParticleStartEndSize.x;
		tempParticle1->mySizeDelta = ((myParticleStartEndSize.y - myParticleStartEndSize.x) / tempParticle1->myTimeLeft);

		tempParticle1->myColor = myParticleColor;

		tempParticle1->myLocalForceFields = &myLocalForceFields;

		if (myLocalSpaceIsActive == true)
		{
			tempParticle1->myEmitterSpace = &myOrientation;
		}
		
		if (myParticleGravity != Vector3f::Zero)
		{
			tempParticle1->myIsAffectedByGravity = true;
			tempParticle1->myGravity = myParticleGravity;
		}
		/*tempParticle1->myIsAffectedByGravity = true;
		tempParticle1->myGravity = Vector3f(0.f, -0.05f, 0.f);*/
	}
}



Vector3f ParticleEmitter::GetRandomizedVector(const Vector3f aMinVector, const Vector3f aMaxVector)
{
	const float x = myRandomizer->GetRandomValue(aMinVector.x, aMaxVector.x);
	const float y = myRandomizer->GetRandomValue(aMinVector.y, aMaxVector.y);
	const float z = myRandomizer->GetRandomValue(aMinVector.z, aMaxVector.z);
	return Vector3f(x, y, z);
}