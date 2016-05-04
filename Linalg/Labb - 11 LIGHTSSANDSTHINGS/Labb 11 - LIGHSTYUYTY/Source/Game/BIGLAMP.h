#pragma once
#include <Vectors/vector3.h>
#include <Vectors/vector4.h>

class BIGLAMP
{
public:
	static void Create(const Vector3f aDirection, const Vector4f aColor);
	static void Destroy();

	static inline Vector3f GetDirection();
	static inline Vector4f GetColor();

	static inline void RotateLight(const float aDeltaTime);

private:
	BIGLAMP(const Vector3f aDirection, const Vector4f aColor);
	~BIGLAMP();

	void InsideRotateLight(const float aDeltaTime);

	static BIGLAMP * ourInstance;

	static inline BIGLAMP & GetInstance();


	Vector3f myDirection;
	Vector4f myColor;
};


inline Vector3f BIGLAMP::GetDirection()
{
	return GetInstance().myDirection;
}

inline Vector4f BIGLAMP::GetColor()
{
	return GetInstance().myColor;
}


inline BIGLAMP & BIGLAMP::GetInstance()
{
	return *ourInstance;
}

void BIGLAMP::RotateLight(const float aDeltaTime)
{
	GetInstance().InsideRotateLight(aDeltaTime);
}