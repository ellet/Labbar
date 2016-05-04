#pragma once
#include <stdlib.h>
#include <crtdbg.h>



#include "../Vectors/Vector.h"
#include "../Matriser/matrix.h"
#include "../Utility/Randomizer/Randomizer.h"

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void Init(const Vector2<float>* aResolutionPtr, const Vector2<float>& aPosition);

	const Matrix33<float> GetInverse() const;
	const Matrix33<float>& GetProjection() const;
	const Vector2<float> GetPosition() const;
	const Vector2<float> GetScreenOffset() const;
	const Vector2<float>& GetScreenResolution() const;
	const float GetResolutionScale() const;

	void Rotate(const float anAngle);
	void Move(Vector3<float> aVector);
	void Zoom(float aFraction);
	void SetPos(const Vector2<float> aPos);
	void SetTargetPos(const Vector2<float> aPos);
	void Update(float aDelta);
	bool IsShaking();
	void Shake(const float aDuration, const float aForce);
	void StopShaking();
private:
	void SetProjection();

	Randomizer myRandomizer;

	Matrix33<float> myOrientation;
	Matrix33<float> myProjection;
	const Vector2<float> *myResolutionPtr;
	Vector2<float> myTargetPos;
	float myResolutionScale;
	float myShakeDuration;
	float myShakeForce;
	bool myShaking;


};

inline const Vector2<float> Camera2D::GetPosition() const
{
	return myOrientation.GetPosition();
}

inline void Camera2D::SetPos(const Vector2<float> aPos)
{
	myTargetPos = aPos;
	myOrientation.SetPosition(aPos);
}

inline void Camera2D::SetTargetPos(const Vector2<float> aPos)
{
	myTargetPos = aPos;
}

inline const Vector2<float>& Camera2D::GetScreenResolution() const
{
	return *myResolutionPtr;
}

inline const float Camera2D::GetResolutionScale() const
{
	return myResolutionScale;
}

inline void Camera2D::Rotate(const float anAngle)
{
	myOrientation.Rotate2D(anAngle);
}

inline const Matrix33<float>& Camera2D::GetProjection() const
{
	return myProjection;
}

inline bool Camera2D::IsShaking()
{
	return myShaking;
}