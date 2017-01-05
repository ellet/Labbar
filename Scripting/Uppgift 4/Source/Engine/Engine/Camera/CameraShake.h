#pragma once
#include "Engine/Camera/Camera.h"
#include "CameraShakeMessage.h"
namespace SB
{
	class Randomizer;
	class CameraShake : public Subscriber<CameraShakeMessage>
	{
	public:
		CameraShake();
		~CameraShake();
		void UpdateCameraShake(const Time & aDeltaTime, Camera & aCamera);

		virtual ReceiveResult CameraShake::Receive(const CameraShakeMessage & aMessage) override;

	private:
		void ApplyCameraShake(const float aMagnitude, const float aShakeTime);

		Vector2f myCameraShake;
		Vector2f myShakeTimer;
		float myShakeMagnitude;
		float myRandomShakeAngle;
		Randomizer* myRandomizer;
	};
}