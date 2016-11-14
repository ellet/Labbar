#include "stdafx.h"
#include "Engine\Camera\Camera.h"
#include "Engine\Buffer\ConstantBuffer.h"

namespace ENGINE_NAMESPACE
{
	Camera::Camera()
	{
		myCameraCB = std::make_unique<ConstantBuffer<CameraCB>>();
		myScale = Vector3f::One;
		CreatePerspective(60.f, 16.f, 9.f, 1000.f, 0.1f);
	}

	Camera::~Camera()
	{
	}

	void Camera::CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane)
	{
		myProjection = Matrix44f::CreateProjection(aVerticalFoVInDegrees, aProjectionWidth, aProjectionHeight, aFarPlane, aNearPlane);
	}

	void Camera::SetPerspective(const Matrix44f & aProjectionMatrix)
	{
		myProjection = aProjectionMatrix;
	}

	const ConstantBuffer<CameraCB> & Camera::GetCameraConstantBuffer() const
	{
		return *myCameraCB;
	}

	void Camera::ApplyToVS() const
	{
		UpdateCB();

		myCameraCB->BindToVS(0);
		myCameraCB->BindToGS(0);
		myCameraCB->BindToPS(0);
	}

	void Camera::UpdateCB() const
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		CameraCB cb;
		cb.projection = myProjection;
		cb.view = Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		cb.view.Inverse();
		cb.cameraPosition = myPosition;

		cb.previousView = myPreviousView;
		cb.previousProjection = myPreviousProjection;

		myCameraCB->UpdateData(cb);
	}

	Vector2f Camera::WorldToScreen(const Vector3f& aWorldPosition) const
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		CameraCB cb;
		cb.projection = myProjection;
		cb.view = Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		cb.view.Inverse();
		cb.cameraPosition = myPosition;

		Vector4f pos = Vector4f(aWorldPosition, 1.f) * cb.view;
		pos = Vector4f(pos, 1.f) * cb.projection;
		pos /= pos.w;
		return Vector2f(pos.x, pos.y);
	}

	Vector3f Camera::ScreenToWorld(const Vector3f& aScreenPosition) const
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		CameraCB cb;
		cb.projection = myProjection;
		cb.projection.Inverse();
		cb.view = Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		cb.cameraPosition = myPosition;

		Vector4f pos = Vector4f(aScreenPosition, 1.f) * cb.projection;
		pos /= pos.w;
		pos = Vector4f(pos, 1.f) * cb.view;
		return Vector3f(pos.x, pos.y, pos.z);
	}

	const Matrix44f& Camera::GetProjectionMatrix() const
	{
		return myProjection;
	}

	const Matrix44f Camera::GetTransformation() const
	{
		Matrix44f transformation = myRotation.GenerateMatrix();
		transformation.SetPosition(myPosition);
		return transformation;
	}

	void Camera::SetScale(const Vector3f& aScale)
	{
		myScale = aScale;
	}

	ReceiveResult Camera::Receive(const EndOfFrameMessage & aMessage)
	{
		Quaternion rotation = myRotation;
		rotation.Normalize();
		auto rotationMatrix = rotation.GenerateMatrix();

		myPreviousView = Matrix44f::CreateScale(myScale.x, myScale.y, myScale.z) * rotationMatrix * Matrix44f::CreateTranslation(myPosition);
		myPreviousView.Inverse();

		myPreviousProjection = myProjection;

		return ReceiveResult::eContinue;
	}

	void Camera::LookAt(const Vector3f & aLookAt)
	{
		Vector3f forwardVector = Vector3f(aLookAt - myPosition).GetNormalized();

		float dot = Vector3f::Dot(Vector3f(0.f, 0.f, 1.f), forwardVector);

		if (abs(dot - (-1.0f)) < 0.000001f)
		{
			myRotation = Quaternion(0.f, 1.f, 0.f, Pi);
			return;
		}
		if (abs(dot - (1.0f)) < 0.000001f)
		{
			myRotation = Quaternion();
			return;
		}

		float rotAngle = acosf(dot);
		Vector3f rotAxis = Vector3f::Cross(Vector3f(0.f, 0.f, 1.f), forwardVector);
		rotAxis.Normalize();
		myRotation = Quaternion();
		myRotation.RotateAlongAxis(rotAxis, rotAngle);
	}
}
