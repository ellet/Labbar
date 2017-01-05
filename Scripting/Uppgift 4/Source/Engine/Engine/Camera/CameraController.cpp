#include "stdafx.h"
#include "CameraController.h"

namespace SB
{
	CameraController::CameraController()
	{
	}


	CameraControllerResult CameraController::Update(const Time & aDeltaTime, Camera & aCamera)
	{

		return CameraControllerResult::eKeepControl;
	}


	CameraController::~CameraController()
	{
	}
}
