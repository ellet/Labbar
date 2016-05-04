#pragma once
#include <Timer/Alarm.h>
#include <Vectors/vector3.h>
#include <Matriser/matrix44.h>
#include "..\..\..\Game/BaseGameStructure/Rendering/WorldSpace.h"
#include <Utility/Randomizer/Randomizer.h>
#include <Distribution/BaseDistributionShape.h>
#include "../ForceField/ForceField.h"
#include <GrowingArray/GrowingArray.h>

namespace DX2D
{
	//class CSprite;
	class CSpriteBatch;
}

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	ParticleEmitter(const ParticleEmitter& aParticleEmitter);

	ParticleEmitter& operator=(const ParticleEmitter& aParticleEmitter)
	{
		myID = aParticleEmitter.myID;

		myOrientation = aParticleEmitter.myOrientation;

		myRotationPerSecond = aParticleEmitter.myRotationPerSecond;

		myEmissionRateAlarm = aParticleEmitter.myEmissionRateAlarm;
		myLifeAlarm = aParticleEmitter.myLifeAlarm;

		myImActive = aParticleEmitter.myImActive;
		myLocalSpaceIsActive = aParticleEmitter.myLocalSpaceIsActive;

		myRandomizer = new Randomizer(*aParticleEmitter.myRandomizer);

		/*myMinPos = aParticleEmitter.myMinPos;
		myMaxPos = aParticleEmitter.myMaxPos;*/
		myDistibutionStrategy = aParticleEmitter.myDistibutionStrategy;

		myParticleLifeTimeRange = aParticleEmitter.myParticleLifeTimeRange;

		myParticleMinVelocity = aParticleEmitter.myParticleMinVelocity;
		myParticleMaxVelocity = aParticleEmitter.myParticleMaxVelocity;

		//myParticlesTexture = aParticleEmitter.myParticlesTexture;
		myParticleBatch = aParticleEmitter.myParticleBatch;

		return *this;
	}

	void Update(const float aDeltaTime);

	void Init(const float aEmissionRate, const float aEmitterLiftetime,
		//const Vector3f aMinPos, const Vector3f aMaxPos,
		BaseDistributionShape * const aDistributionShape,
		const Vector2f aParticleLifeTimeRange,
		const Vector3f aRotationInDegreesPerSecond,
		const Vector3f aMinVelocity, const Vector3f aMaxVelocity,
		const Vector3f aColor,
		const Vector3f aGravity,
		const Vector2f aStartAndEndAlpha,
		const Vector2f aStartEndSize,
		const char * aTexturePath,
		//const CU::GrowingArray<ForceField> & aArrayOfForceFields,
		const bool aUseLocalSpace);

	void Rotate(const float aDeltaTime);


	void FireParticle();

	void inline ActiveEmitter();

	inline CU::GrowingArray<ForceField> & GetForceFieldArray();

private:
	unsigned int myID;

	Vector3f GetRandomizedVector(const Vector3f aMinVector, const Vector3f aMaxVector);

	

	WorldSpace myOrientation;

	Vector3f myRotationPerSecond;

	CommonUtilities::Alarm myEmissionRateAlarm;
	CommonUtilities::Alarm myLifeAlarm;

	bool myImActive;
	bool myLocalSpaceIsActive;

	Randomizer * myRandomizer;

	/*Vector3f myMinPos;
	Vector3f myMaxPos;*/

	BaseDistributionShape * myDistibutionStrategy;

	Vector2f myParticleLifeTimeRange;

	Vector3f myParticleMinVelocity;
	Vector3f myParticleMaxVelocity;

	Vector2f myParticleStartEndSize;

	Vector3f myParticleColor;

	Vector3f myParticleGravity;

	float myParticleStartAlpha;
	float myParticleEndAlpha;

	//DX2D::CSprite * myParticlesTexture;
	DX2D::CSpriteBatch * myParticleBatch;

	CU::GrowingArray<ForceField> myLocalForceFields;
};

inline void ParticleEmitter::ActiveEmitter()
{
	myImActive = true;
	myLifeAlarm.Reset();
}

inline CU::GrowingArray<ForceField> & ParticleEmitter::GetForceFieldArray()
{
	return myLocalForceFields;
}