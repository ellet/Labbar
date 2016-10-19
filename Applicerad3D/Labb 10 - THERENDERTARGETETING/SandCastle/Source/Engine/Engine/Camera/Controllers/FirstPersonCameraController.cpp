#include "stdafx.h"
#include "FirstPersonCameraController.h"
#include "Engine/GameObject/GameObject.h"


namespace ENGINE_NAMESPACE
{
	FirstPersonCameraController::FirstPersonCameraController(GameObject* aGameObject)
	{
		myOwnerObject = aGameObject;
	}

	FirstPersonCameraController::~FirstPersonCameraController()
	{
	}

	CameraControllerResult FirstPersonCameraController::Update(const Time& aDeltaTime, Camera& aCamera)
	{
		if (myOwnerObject != nullptr)
		{
			aCamera.SetPosition(myOwnerObject->GetTransformation().GetPosition());	
			aCamera.SetOrientation(myOwnerObject->GetWorldRotation());
			return CameraControllerResult::eKeepControl;
		}

		return CameraControllerResult::ePassControl;
	}

}
