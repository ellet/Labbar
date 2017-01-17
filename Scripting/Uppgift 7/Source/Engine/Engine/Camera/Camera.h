#pragma once
#include "..\GenericEngineMessages.h"
#include "Engine/Camera/CameraConstantBuffer.h"

namespace SB
{
	class Camera : public Subscriber<EndOfFrameMessage>, public Subscriber<WindowSizeChangedMessage>
	{
	public:
		Camera(const char * aSkyboxPath = nullptr);
		~Camera();

		void RenderScene(const Scene & aScene, const ParticleSystem * const aParticleSystem = nullptr);

		void CreatePerspective(float aVerticalFoVInDegrees, float aProjectionWidth, float aProjectionHeight, float aNearPlane, float aFarPlane);
		void SetPosition(const Vector3f & aPosition);
		void AddPosition(const Vector3f & aPositionToAdd);
		const Vector3f & GetPosition() const;

		void LookAt(const Vector3f & aLookAt);

		void SetOrientation(const Quaternion& aOrientation);
		Quaternion& GetOrientation();
		const Quaternion& GetOrientation() const;

		void ApplyToVS() const;
		CameraConstantBuffer GenerateCameraData() const;
		
		Vector2f WorldToScreen(const Vector3f& aWorldPosition) const;
		Vector3f ScreenToWorld(const Vector3f& aScreenPosition) const;

		const Matrix44f & GetProjectionMatrix() const;
		const Matrix44f GetTransformation() const;

		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;
		virtual ReceiveResult Receive(const WindowSizeChangedMessage & aMessage) override;

		const std::shared_ptr<WorldRenderTexture> & GetRenderTexture() const;
		void SetSkybox(const char* aSkyboxPath);
		void RenderBuffer();

	private:
		void UpdateCache();

		Vector3f myPosition;
		Quaternion myRotation;

		Matrix44f myProjection;

		Matrix44f myPreviousProjection;
		Matrix44f myPreviousView;
		float myVerticalFieldOfView;
		float myHorizontalFieldOfView;

		Matrix44f myCachedViewProjection;
		Vector3f myCachedPosition;
		Quaternion myCachedRotation;

		std::unique_ptr<ModelInstance> mySkybox;
		std::shared_ptr<WorldRenderTexture> myRenderTexture;
		std::shared_ptr<TextureCube> mySkyboxTexture;
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
