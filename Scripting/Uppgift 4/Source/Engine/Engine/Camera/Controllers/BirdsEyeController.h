#pragma once
#include "Engine/Camera/CameraController.h"

namespace SB
{
	class BirdsEyeController : public CameraController
	{
	public:
		BirdsEyeController(const ObjectPtr & aObjectToFollow, const float aDistance, const float aYaw = 0.f, const float aPitch = 0.f, const float aRoll = 0.f);
		CameraControllerResult Update(const Time & aDeltaTime, Camera & aCamera) override;

	private:
		ObjectPtr myObjectToFollow;
		Quaternion myCameraRotation;
		Vector3f myLookDirection;
		float myDistanceToObject;
	};
}
