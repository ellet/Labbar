#include "stdafx.h"
#include "Feedback.h"
#include "Utilities/Container/GrowingArray.h"
#include "Engine/ParticleSystem/ParticleEmitter.h"

namespace SB
{
	Feedback::Feedback(const std::string & aFeedbackType)
	{
		myIsPaused = false;
		myIsLooping = false;
	}

	Feedback::~Feedback()
	{
	}

	void Feedback::Update(const Time & aDeltaTime, const Matrix44f & aTransformation)
	{
		if (myIsPaused == false)
		{
			InternalUpdate(aDeltaTime, aTransformation);

			if (myIsLooping == false && myCurrentTime >= myTotalLifeTime)
			{
				myIsPaused = true;
			}
		}
	}

	void Feedback::InternalUpdate(const Time & aDeltaTime, const Matrix44f & aTransformation)
	{
		for (unsigned short i = 0; i < mySettings->myParticleEmitters.Size(); ++i)
		{
			Matrix44f transform = aTransformation;
			transform.SetPosition(mySettings->myParticleEmitters[i].myOffset + transform.GetPosition());
			mySettings->myParticleEmitters[i].myEmitter->Update(aDeltaTime, transform);
		}
	}

	void Feedback::SetIsPaused(const bool aTrueOrFalse)
	{
		myIsPaused = aTrueOrFalse;
	}

	void Feedback::LoadFeedbackTypes()
	{

	}
}