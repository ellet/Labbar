#include "stdafx.h"
#include "StreakEmitterInstance.h"
#include "..\Effect\StreakEffect.h"


namespace ENGINE_NAMESPACE
{
	StreakEmitterInstance::StreakEmitterInstance(const Vector3f& aPosition)
	{
		SetPosition(aPosition);

		AddStreak();

		myVertexBuffer = std::make_unique<VertexBuffer<Streak>>(&myStreaks[0], myStreaks.Size(), false);

		myTopology = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
		myParticleEffect = std::make_unique<StreakEffect>();
	}


	StreakEmitterInstance::~StreakEmitterInstance()
	{
	}

	void StreakEmitterInstance::AddStreak()
	{
		float tempStartSize = 0.2f;
		float tempEndSize = 0.05f;

		float tempLifeTime = 5.f;
		float tempSizeDelta = (tempEndSize - tempStartSize ) / tempLifeTime;

		myStreaks.Add(Streak(GetPosition(), 0.2f, 1.f));
		myStreakLogic.Add(StreakLogic(tempLifeTime, tempSizeDelta));
	}

	void StreakEmitterInstance::RemoveStreak(const unsigned short aIndex)
	{
		myStreaks.RemoveAtIndex(aIndex);
		myStreakLogic.RemoveAtIndex(aIndex);
	}

	void StreakEmitterInstance::Update(SB::Time aDeltaTime)
	{
		if (myStopWatch.GetElapsedTime() > 0.05f)
		{
			AddStreak();
			myStopWatch.Restart();
		}


		for (unsigned short iStreak = 0; iStreak < myStreakLogic.Size(); ++iStreak)
		{
			const float LifeDelta = aDeltaTime.InSeconds();
			myStreakLogic[iStreak].myLifetime -= LifeDelta;

			if (myStreakLogic[iStreak].myLifetime <= 0.f)
			{
				RemoveStreak(iStreak);
				continue;
			}

			const float SizeDelta = myStreakLogic[iStreak].mySizeDelta * aDeltaTime.InSeconds();
			const float SizefsdflsdkjflksdjfDelta = myStreakLogic[iStreak].mySizeDelta;
			myStreaks[iStreak].mySize += SizeDelta;

		}
		
		if (myStreaks.Size() > 0)
		{
			myVertexBuffer->UpdateData(&myStreaks[0], myStreaks.Size(), true);
		}
	}

	void StreakEmitterInstance::Render()
	{
		if (myStreaks.Size() > 0)
		{
			myParticleEffect->Bind();

			myVertexBuffer->Bind(0);
			Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(myTopology);

			Engine::GetInstance().GetRenderer().GetContext()->Draw(myStreaks.Size(), 0);
		}
	}

	Vector3f StreakEmitterInstance::GetRandomizedVector(const Vector3f aMinVector, const Vector3f aMaxVector)
	{
		const float x = myRandomizer.GetRandomValue(aMinVector.x, aMaxVector.x);
		const float y = myRandomizer.GetRandomValue(aMinVector.y, aMaxVector.y);
		const float z = myRandomizer.GetRandomValue(aMinVector.z, aMaxVector.z);
		return Vector3f(x, y, z);
	}

}
