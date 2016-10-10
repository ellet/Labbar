#pragma once
#include "..\Buffer\VertexBuffer.h"
#include "..\..\..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace ENGINE_NAMESPACE
{

	class StreakEffect;

	struct Streak
	{
		Streak()
		{
			myPosition = Vector4f::Zero;
			mySize = 1.f;
			myAlpha = 1.f;
		}
		Streak(const Vector3f& aPosition, const float aSize, const float aAlpha)
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

	struct StreakLogic
	{
		StreakLogic()
		{
			myLifetime = 1.f;
		}
		StreakLogic(const float aLifetime, const float aSizeDelta)
		{
			myLifetime = aLifetime;
			mySizeDelta = aSizeDelta;
		}
		float myLifetime;
		float mySizeDelta;
	};


	class StreakEmitterInstance
	{
	public:
		StreakEmitterInstance(const Vector3f& aPosition);
		~StreakEmitterInstance();

		void AddStreak();
		void RemoveStreak(const unsigned short aIndex);

		void Update(Time aDeltaTime);
		void Render();

		inline const Vector3f& GetPosition() const
		{
			return myPosition;
		}
		inline void SetPosition(const Vector3f& aValue)
		{
			myPosition = aValue;
		}
	private:
		Vector3f GetRandomizedVector(const Vector3f aMinVector = Vector3f(-1.f, -1.f, -1.f), const Vector3f aMaxVector = Vector3f(1.f, 1.f, 1.f));

		GrowingArray<Streak> myStreaks;
		GrowingArray<StreakLogic> myStreakLogic;

		Vector3f myPosition;

		std::unique_ptr<VertexBuffer<Streak>> myVertexBuffer;
		D3D_PRIMITIVE_TOPOLOGY myTopology;
		std::unique_ptr<StreakEffect> myParticleEffect;

		Randomizer myRandomizer;
		Stopwatch myStopWatch;
	};
}

