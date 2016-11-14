#include "stdafx.h"
#include "SpaceGameCameraController.h"
#include <Engine/Camera/CameraShake.h>

SpaceGameCameraController::SpaceGameCameraController(SB::GameObject* aGameObject)
	: FirstPersonCameraController(aGameObject)
{
	myFoV = 60.f;
	mySquishFactor = 1.f;
	myFoVFactor = 1.f;
	myCameraShake = std::make_shared<SB::CameraShake>();
}

SB::CameraControllerResult SpaceGameCameraController::Update(const SB::Time& aDeltaTime, SB::Camera& aCamera)
{
	aCamera.SetPerspective(SB::Matrix44f::CreateScale(1.f, 1.f, 1.f * mySquishFactor) * SB::Matrix44f::CreateProjection(myFoV * myFoVFactor, SB::Engine::GetRenderer().GetRenderTargetResolution().x, SB::Engine::GetRenderer().GetRenderTargetResolution().y, 0.1f, 7500.f));
	auto result = FirstPersonCameraController::Update(aDeltaTime, aCamera);
	aCamera.SetScale(SB::Vector3f(1.f, 1.f, mySquishFactor));
	aCamera.AddPosition(myPlayerControllerDynamicOffset);
	myCameraShake->UpdateCameraShake(aDeltaTime, aCamera);
	return result;
}

void SpaceGameCameraController::SetSquish(float aSquishFactor)
{
	mySquishFactor = aSquishFactor;
}

void SpaceGameCameraController::SetFoVFactor(float aFoVFactor)
{
	myFoVFactor = aFoVFactor;
}

void SpaceGameCameraController::SetPlayerControllerDynamicOffset(const SB::Vector3f & aOffset)
{
	myPlayerControllerDynamicOffset = aOffset;
}
