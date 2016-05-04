#pragma once

#include <string>
#include <memory>

#include <Vectors\vector2.h>
#include <Vectors\vector4.h>

namespace DX2D
{
	class CSprite;
}

class BaseGameObject
{
public:

	BaseGameObject();
	virtual ~BaseGameObject();

	virtual void Update(const float aDeltaTime);
	virtual void Draw() const;

	inline DX2D::CSprite* GetSprite() const;
	void SetSprite(std::shared_ptr<DX2D::CSprite> aSprite);
	void LoadSprite(const std::string &aPathToSprite);

	inline const Vector2f& GetPosition() const;
	inline void SetPosition(const Vector2f &aPosition);

	inline const Vector2f& GetSize() const;
	inline void SetSize(const Vector2f &aSize);

	inline const Vector2f& GetPivot() const;
	inline void SetPivot(const Vector2f &aPivot);

	inline float GetRotation() const;
	inline void SetRotation(const float aRotation);

	inline const Vector4f& GetColor() const;
	inline void SetColor(const Vector4f &aColor);
	
	inline void SetIsActive(bool aIsActive);
	inline bool IsActive();

	inline void SetRenderPriority(const float aPriority);
	inline float GetRenderPriority() const;

private:

	std::shared_ptr<DX2D::CSprite> mySprite;

	Vector2f myPosition;
	Vector2f mySize;
	Vector2f myPivot;

	float myRotation;

	Vector4f myColors;
protected:
	
	bool myIsActive;
	float myRenderPriority;

};


inline DX2D::CSprite* BaseGameObject::GetSprite() const
{
	return mySprite.get();
}

inline const Vector2f& BaseGameObject::GetPosition() const
{
	return myPosition;
}
inline void BaseGameObject::SetPosition(const Vector2f &aPosition)
{
	myPosition = aPosition;
}

inline const Vector2f& BaseGameObject::GetSize() const
{
	return mySize;
}
inline void BaseGameObject::SetSize(const Vector2f &aSize)
{
	mySize = aSize;
}

inline const Vector2f& BaseGameObject::GetPivot() const
{
	return myPivot;
}
inline void BaseGameObject::SetPivot(const Vector2f &aPivot)
{
	myPivot = aPivot;
}

inline float BaseGameObject::GetRotation() const
{
	return myRotation;
}
inline void BaseGameObject::SetRotation(const float aRotation)
{
	myRotation = aRotation;
}

inline const Vector4f& BaseGameObject::GetColor() const
{
	return myColors;
}
inline void BaseGameObject::SetColor(const Vector4f &aColor)
{
	myColors = aColor;
}

inline void BaseGameObject::SetIsActive(bool aIsActive)
{
	myIsActive = aIsActive;
}

inline bool BaseGameObject::IsActive()
{
	return myIsActive;
}


inline void BaseGameObject::SetRenderPriority(const float aPriority)
{
	myRenderPriority = aPriority;
}

float BaseGameObject::GetRenderPriority() const
{
	return myRenderPriority;
}