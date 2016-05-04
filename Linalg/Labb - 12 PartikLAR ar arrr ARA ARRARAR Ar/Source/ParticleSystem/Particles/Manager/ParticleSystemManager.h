#pragma once
#include <DLDebug/DL_Debug.h>
#include "../Particle.h"
#include <array>
#include "../../../Game/BaseGameStructure/GameObjectsManager.h"
#include "../Emitter/ParticleEmitter.h"
#include "../ForceField/ForceField.h"
#include <GrowingArray/GrowingArray.h>

class ParticleSystemManager
{
public:
	static void Create();
	static void Destroy();

	inline static Particle * ActivateParticle();

	

	inline static void Update(const float aDeltaTime);

	inline static void Draw();

private:
	void Setup();

	inline Particle * InternalActivateParticle();

	void UpdateParticle(const float aDeltaTime, Particle & aParticle);

	void SetEmitter();
	void SetForceField();

	void InternalUpdate(const float aDeltaTime);
	void InternalDraw();

	void ApplyForceField(const ForceField & aForceField,Particle & aParticle, const float aDeltaTime);

	static ParticleSystemManager * ourInstance;
	
	static inline ParticleSystemManager & GetInstance();

	std::array <Particle, 100> myParticles;
	CommonUtilities::GrowingArray<ForceField> myForceFields;

	ParticleEmitter myTestEmitter;

	ParticleSystemManager();
	~ParticleSystemManager();
};

ParticleSystemManager & ParticleSystemManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "Particle system pointer is nullptr");
	return *ourInstance;
}

Particle * ParticleSystemManager::ActivateParticle()
{
	return GetInstance().InternalActivateParticle();
}

void ParticleSystemManager::Update(const float aDeltaTime)
{
	GetInstance().InternalUpdate(aDeltaTime);
}

void ParticleSystemManager::Draw()
{
	GetInstance().InternalDraw();
}

Particle * ParticleSystemManager::InternalActivateParticle()
{
	for (size_t iParticles = 0; iParticles < myParticles.size(); ++iParticles)
	{
		if (myParticles[iParticles].myIsActive == false)
		{
			myParticles[iParticles].myIsActive = true;
			return &myParticles[iParticles];
		}
	}

	return nullptr;
}

