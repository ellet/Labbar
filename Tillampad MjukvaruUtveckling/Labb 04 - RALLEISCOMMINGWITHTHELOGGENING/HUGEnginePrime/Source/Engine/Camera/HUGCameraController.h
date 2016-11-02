#pragma once
class CHUGCameraController
{
public:
	CHUGCameraController();
	~CHUGCameraController();

	void IncreasePosition(CU::Vector3f aPosition);

	void IncreaseYaw(float aRadian);

	void IncreasePitch(float aRadian);

	void IncreaseRoll(float aRadian);

	void IncreaseForward(float aDelta);

	void IncreaseRight(float aDelta);

	void SetPosition(CU::Vector3f aPosition);

private:
	unsigned short myCameraIndex;
};

