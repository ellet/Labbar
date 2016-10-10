#pragma once
#include "..\Buffer\VertexBuffer.h"
#include "..\..\..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace ENGINE_NAMESPACE
{

	class ParticleEffect;

	struct Particle
	{
		Particle()
		{
			myPosition = Vector4f::Zero;
			mySize = 1.f;
			myAlpha = 1.f;
		}
		Particle(const Vector3f& aPosition, const float aSize, const float aAlpha)
		{
			myPosition = aPosition;
			myPosition.w = 1.f;
			mySize = aSize;
			myAlpha = aAlpha;
		}
		Vector4f myPosition;
		float mySize;
		float myAlpha;
		float myFiller1;
		float myFiller2;
	};

	struct ParticleLogic
	{
		ParticleLogic()
		{
			myVelocity = Vector3f::Zero;
			myLifetime = 1.f;
		}
		ParticleLogic(const Vector3f& aVelocity, const float aLifetime)
		{
			myVelocity = aVelocity;
			myLifetime = aLifetime;
		}
		Vector3f myVelocity;
		float myLifetime;
	};


	class ParticleEmitterInstance
	{
	public:
		ParticleEmitterInstance();
		~ParticleEmitterInstance();

		void AddParticle();
		void RemoveParticle(const unsigned short aIndex);

		void Update(Time aDeltaTime);
		void Render();

	private:
		Vector3f GetRandomizedVector(const Vector3f aMinVector = Vector3f(-1.f, -1.f, -1.f), const Vector3f aMaxVector = Vector3f(1.f, 1.f, 1.f));

		GrowingArray<Particle> myParticles;
		GrowingArray<ParticleLogic> myParticleLogic;

		std::unique_ptr<VertexBuffer<Particle>> myVertexBuffer;
		D3D_PRIMITIVE_TOPOLOGY myTopology;
		std::unique_ptr<ParticleEffect> myParticleEffect;

		Randomizer myRandomizer;
		Stopwatch myStopWatch;
	};
}

