#pragma once

namespace ENGINE_NAMESPACE
{

	struct CameraShakeMessage
	{
		CameraShakeMessage(const float aMagnitude, const float aShakeTime)
		{
			myMagnitude = aMagnitude;
			myShakeTime = aShakeTime;
		}
		float myMagnitude;
		float myShakeTime;
	};
}