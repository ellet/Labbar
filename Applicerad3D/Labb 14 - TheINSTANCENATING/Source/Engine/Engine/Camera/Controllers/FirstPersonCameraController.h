#pragma once
#include "Engine\Camera\CameraController.h"

namespace ENGINE_NAMESPACE
{
	class FirstPersonCameraController : public CameraController
	{
	public:
		FirstPersonCameraController(GameObject* aGameObject);
		~FirstPersonCameraController();

		virtual CameraControllerResult Update(const Time& aDeltaTime, Camera& aCamera) override;

	private:
		GameObject* myOwnerObject;
	};
}

