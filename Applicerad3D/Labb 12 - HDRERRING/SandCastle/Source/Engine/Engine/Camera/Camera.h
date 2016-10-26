#pragma once

namespace ENGINE_NAMESPACE
{
	template<typename T>
	class ConstantBuffer;

	struct CameraCB
	{
		Matrix44f view;
		Matrix44f projection;
		Vector4f cameraPosition;
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		void CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane);

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
		
		Vector2f WorldToScreen(const Vector3f& aWorldPosition);

	private:
		std::unique_ptr<ConstantBuffer<CameraCB>> myCameraCB;
		Vector3f myPosition;
		Quaternion myRotation;
		Matrix44f myProjection;
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
