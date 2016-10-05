#include "stdafx.h"
#include "ParticleEmitterInstance.h"
#include "..\Effect\ParticleEffect.h"


namespace ENGINE_NAMESPACE
{
	ParticleEmitterInstance::ParticleEmitterInstance()
	{
		AddParticle();

		myVertexBuffer = std::make_unique<VertexBuffer<Particle>>(&myParticles[0], myParticles.Size(), false);

		myTopology = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
		myParticleEffect = std::make_unique<ParticleEffect>();
	}


	ParticleEmitterInstance::~ParticleEmitterInstance()
	{
	}

	void ParticleEmitterInstance::AddParticle()
	{
		myParticles.Add(Particle(GetRandomizedVector(), myRandomizer.GetRandomValue(0.5f, 3.f), 7.f));
		

		myParticleLogic.Add(ParticleLogic(GetRandomizedVector(), myRandomizer.GetRandomValue(1.f, 50.f)));
		
	}

	void ParticleEmitterInstance::RemoveParticle(const unsigned short aIndex)
	{
		myParticles.RemoveCyclicAtIndex(aIndex);
		myParticleLogic.RemoveCyclicAtIndex(aIndex);
	}

	void ParticleEmitterInstance::Update(SB::Time aDeltaTime)
	{
		if (myStopWatch.GetElapsedTime() > 1.f)
		{
			AddParticle();
			myStopWatch.Restart();
		}


		for (unsigned short iParticle = 0; iParticle < myParticleLogic.Size(); ++iParticle)
		{
			const Vector3f SpeedDelta = myParticleLogic[iParticle].myVelocity * aDeltaTime.InSeconds();
			const float LifeDelta = aDeltaTime.InSeconds();

			
			myParticles[iParticle].myPosition += SpeedDelta;
			myParticleLogic[iParticle].myLifetime -= LifeDelta;

			if (myParticleLogic[iParticle].myLifetime <= 0.f)
			{
				RemoveParticle(iParticle);
			}
		}
		
		if (myParticles.Size() > 0)
		{
			myVertexBuffer->UpdateData(&myParticles[0], myParticles.Size(), true);
		}
	}

	void ParticleEmitterInstance::Render()
	{
		if (myParticles.Size() > 0)
		{
			myParticleEffect->Bind();

			myVertexBuffer->Bind(0);
			Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(myTopology);

			Engine::GetInstance().GetRenderer().GetContext()->Draw(myParticles.Size(), 0);
		}
	}

	Vector3f ParticleEmitterInstance::GetRandomizedVector(const Vector3f aMinVector, const Vector3f aMaxVector)
	{
		const float x = myRandomizer.GetRandomValue(aMinVector.x, aMaxVector.x);
		const float y = myRandomizer.GetRandomValue(aMinVector.y, aMaxVector.y);
		const float z = myRandomizer.GetRandomValue(aMinVector.z, aMaxVector.z);
		return Vector3f(x, y, z);
	}

}
