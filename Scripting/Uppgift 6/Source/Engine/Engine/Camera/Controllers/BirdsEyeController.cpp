#include "stdafx.h"
#include "BirdsEyeController.h"

namespace SB
{
	BirdsEyeController::BirdsEyeController(const ObjectPtr & aObjectToFollow, const float aDistanceToObject, const float aYaw, const float aPitch, const float aRoll)
	{
		myObjectToFollow = aObjectToFollow;
		myDistanceToObject = aDistanceToObject;
		Quaternion q;
		q.RotateAroundWorldY(aYaw);
		q.RotateAroundLocalX(aPitch);
		q.RotateAroundLocalZ(aRoll);
		myLookDirection = q.GetForward();
		myCameraRotation = q;
	}

	CameraControllerResult BirdsEyeController::Update(const Time& aDeltaTime, Camera& aCamera)
	{
		aCamera.SetPosition(myObjectToFollow->GetWorldPosition() - myLookDirection * myDistanceToObject);
		aCamera.SetOrientation(myCameraRotation);
		return CameraControllerResult::eKeepControl;
	}
}
