#pragma once
#include <Engine/Camera/Controllers/FirstPersonCameraController.h>

namespace ENGINE_NAMESPACE
{
	class CameraShake;
}
class SpaceGameCameraController : public SB::FirstPersonCameraController
{
public:
	SpaceGameCameraController(SB::GameObject* aGameObject);
	SB::CameraControllerResult Update(const SB::Time& aDeltaTime, SB::Camera& aCamera) override;

	void SetSquish(float aSquishFactor);
	void SetFoVFactor(float aFoVFactor);
	void SetPlayerControllerDynamicOffset(const SB::Vector3f& aOffset);

private:
	SB::Vector3f myPlayerControllerDynamicOffset;
	std::shared_ptr<SB::CameraShake> myCameraShake;
	float mySquishFactor;
	float myFoVFactor;
	float myFoV;
};
