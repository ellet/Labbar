#include "stdafx.h"
#include "CameraShake.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace ENGINE_NAMESPACE
{
	CameraShake::CameraShake()
	{
		myCameraShake = Vector2f::Zero;
		myShakeTimer = Vector2f::Zero;
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
			myCameraShake = Vector2f(sin(myRandomShakeAngle), cos(myRandomShakeAngle)) * (myShakeMagnitude * pow(myShakeTimer.x / myShakeTimer.y/*TimeLeftInPercent*/, 2));

			Vector3f newCamPos = aCamera.GetPosition();
			newCamPos += myCameraShake.x * cameraRot.GetRight();
			newCamPos += myCameraShake.y * cameraRot.GetUpward();
			
			aCamera.SetPosition(newCamPos/*Vector3f(camPos.x + myCameraShake.x, camPos.y + myCameraShake.y, camPos.z)*/);
			myRandomShakeAngle += (180 + (rand() % 120) - 60);

			if (myShakeTimer.x <= 0.f)
			{
				myShakeMagnitude = 0;
				myShakeTimer.x = 0.f;
				myShakeTimer.y = 0.f;
			}
		}
	}

	ReceiveResult CameraShake::Receive(const CameraShakeMessage & aMessage)
	{
		ApplyCameraShake(aMessage.myMagnitude, aMessage.myShakeTime);
		return ReceiveResult::eStop;
	}

	void CameraShake::ApplyCameraShake(const float aMagnitude, const float aShakeTime)
	{
		if (aMagnitude >= myShakeMagnitude)
		{
			myShakeMagnitude = aMagnitude / 1000.f;
			myShakeTimer.x = aShakeTime;
			myShakeTimer.y = aShakeTime;
			myRandomShakeAngle = DEGREES_TO_RADIANSF(myRandomizer->GetRandomValue(0.f, 360.f));
		}
	}
}