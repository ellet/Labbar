#pragma once
#include <Timer/Alarm.h>
#include <Vectors/vector3.h>
#include <Matriser/matrix44.h>
#include "..\..\..\Game/BaseGameStructure/Rendering/WorldSpace.h"


class Randomizer;

namespace DX2D
{
	class CSprite;
}

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	void Update(const float aDeltaTime);

	void Init(const float aEmissionRate, const float aEmitterLiftetime,
		const Vector3f aMinPos, const Vector3f aMaxPos,
		const Vector2f aParticleLifeTimeRange,
		const Vector3f aRotationInDegreesPerSecond,
		const Vector3f aMinVelocity, const Vector3f aMaxVelocity,
		const char * aTexturePath, 
		const bool aUseLocalSpace);

	void Rotate(const float aDeltaTime);


	void FireParticle();

	void inline ActiveEmitter();

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

	Vector3f myMinPos;
	Vector3f myMaxPos;

	Vector2f myParticleLifeTimeRange;

	Vector3f myParticleMinVelocity;
	Vector3f myParticleMaxVelocity;

	DX2D::CSprite * myParticlesTexture;

	//-----------
	// my particles info

	/*float myParticlesMinLifeTime;
	float myParticlesMaxLifeTime;

	float myParticlesAlphaStart;
	float myParticlesAlphaEnd;
	*/
	
};

inline void ParticleEmitter::ActiveEmitter()
{
	myImActive = true;
	myLifeAlarm.Reset();
}