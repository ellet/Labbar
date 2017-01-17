#include "stdafx.h"
#include "CameraShake.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace SB
{
	CameraShake::CameraShake()
	{
		myCameraShake = Vector2f::Zero;
		myShakeTimer = Vector2f(0.f, 1.f);
		myShakeMagnitude = 0.f;
		myRandomShakeAngle = 0.f;
		myRandomizer = new Randomizer;
	}


	CameraShake::~CameraShake()
	{
		//SB::PostMaster::RemoveSubscriber(*this);
		delete myRandomizer;
		myRandomizer = nullptr;
	}

	void CameraShake::UpdateCameraShake(const Time & aDeltaTime, Camera & aCamera)
	{
		if (myShakeTimer.x > 0.f)
		{
			const Quaternion & cameraRot = aCamera.GetOrientation();
			myShakeTimer.x -= aDeltaTime.InSeconds();
			myCameraShake = Vector2f(sin(myRandomShakeAngle), cos(myRandomShakeAngle)) * (myShakeMagnitude * pow(myShakeTimer.x / myShakeTimer.y, 2));

			Vector3f newCamPos = aCamera.GetPosition();
			newCamPos += myCameraShake.x * cameraRot.GetRight();
			newCamPos += myCameraShake.y * cameraRot.GetUpward();
			
			aCamera.SetPosition(newCamPos);
			myRandomShakeAngle += (180 + (rand() % 120) - 60);

			if (myShakeTimer.x <= 0.f)
			{
				myShakeMagnitude = 0;
				myShakeTimer.x = 0.f;
				myShakeTimer.y = 1.f;
			}
		}
	}

	ReceiveResult CameraShake::Receive(const CameraShakeMessage & aMessage)
	{
		ApplyCameraShake(aMessage.myMagnitude, aMessage.myShakeTime);
		return ReceiveResult::eContinue;
	}

	void CameraShake::ApplyCameraShake(const float aMagnitude, const float aShakeTime)
	{
		if (aMagnitude / 1000.f >= myShakeMagnitude * (myShakeTimer.x / myShakeTimer.y))
		{
			myShakeMagnitude = aMagnitude / 1000.f;
			myShakeTimer.x = aShakeTime;
			myShakeTimer.y = aShakeTime;
			myRandomShakeAngle = DEGREES_TO_RADIANSF(myRandomizer->GetRandomValue(0.f, 360.f));
		}
	}
}