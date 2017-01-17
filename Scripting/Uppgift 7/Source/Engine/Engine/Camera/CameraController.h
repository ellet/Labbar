#pragma once
#include "Engine/Camera/Camera.h"

namespace SB
{
	enum class CameraControllerResult
	{
		eKeepControl,
		ePassControl
	};

	class Randomizer;
	class CameraController
	{
	public:
		virtual CameraControllerResult Update(const Time & aDeltaTime, Camera & aCamera) = 0;
		virtual ~CameraController();

	protected:
		CameraController();
	};
}
