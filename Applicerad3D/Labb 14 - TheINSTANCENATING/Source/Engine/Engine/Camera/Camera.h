#pragma once
#include "..\GenericEngineMessages.h"

namespace ENGINE_NAMESPACE
{
	template<typename T>
	class ConstantBuffer;

	struct CameraCB
	{
		Matrix44f view;
		Matrix44f projection;

		Matrix44f previousView;
		Matrix44f previousProjection;

		Vector4f cameraPosition;

		
	};

	class Camera : public Subscriber<EndOfFrameMessage>
	{
	public:
		Camera();
		~Camera();

		void CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane);
		void SetPerspective(const Matrix44f& aProjectionMatrix);
		void SetPosition(const Vector3f & aPosition);
		void AddPosition(const Vector3f & aPositionToAdd);
		const Vector3f & GetPosition() const;

		void LookAt(const Vector3f & aLookAt);

		void SetOrientation(const Quaternion& aOrientation);
		Quaternion& GetOrientation();
		const Quaternion& GetOrientation() const;

		const ConstantBuffer<CameraCB> & GetCameraConstantBuffer() const;

		void ApplyToVS() const;

		void UpdateCB() const;
		
		Vector2f WorldToScreen(const Vector3f& aWorldPosition) const;
		Vector3f ScreenToWorld(const Vector3f& aScreenPosition) const;

		const Matrix44f & GetProjectionMatrix() const;
		const Matrix44f GetTransformation() const;

		void SetScale(const Vector3f& aScale);


		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;

	private:
		std::unique_ptr<ConstantBuffer<CameraCB>> myCameraCB;
		Vector3f myPosition;
		Vector3f myScale;
		Quaternion myRotation;

		Matrix44f myProjection;

		Matrix44f myPreviousProjection;
		Matrix44f myPreviousView;

	};


	inline void Camera::SetPosition(const Vector3f & aPosition)
	{
		myPosition = aPosition;
	}

	inline void Camera::AddPosition(const Vector3f & aPositionToAdd)
	{
		myPosition += aPositionToAdd;
	}

	inline void Camera::SetOrientation(const Quaternion& aOrientation)
	{
		myRotation = aOrientation;
	}

	inline const Vector3f & Camera::GetPosition() const
	{
		return myPosition;
	}

	inline Quaternion & Camera::GetOrientation()
	{
		return myRotation;
	}

	inline const Quaternion & Camera::GetOrientation() const
	{
		return myRotation;
	}
}
