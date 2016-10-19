#include "stdafx.h"
#include "Sprite.h"
#include "Engine/Rendering/SpriteRenderer.h"

namespace ENGINE_NAMESPACE
{
	Sprite::Sprite()
	{
		myColor = Vector4f(1.f, 1.f, 1.f, 1.f);
		myScale = Vector2f(1.f, 1.f);
		myRotation = 0.f;
		myTextureSize = Vector2f::One;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::Render()
	{
		Engine::GetRenderer().GetSpriteRenderer().Render(*this);
	}

	void Sprite::SetTexture(const std::shared_ptr<const Texture> & aTexture)
	{
		myTexture = aTexture;

		if (myTexture != nullptr)
		{
			myTextureTopLeft = Vector2f::Zero;
			myTextureSize = myTexture->GetSize();
		}
	}

	const std::shared_ptr<const Texture> & Sprite::GetTexture() const
	{
		return myTexture;
	}

	void Sprite::SetColor(const Vector4f & aColor)
	{
		myColor = aColor;
	}

	const Vector4f & Sprite::GetColor() const
	{
		return myColor;
	}

	void Sprite::SetRotation(const float aRotation)
	{
		myRotation = aRotation;
	}

	float Sprite::GetRotation() const
	{
		return myRotation;
	}

	void Sprite::SetOrigin(const Vector2f & aOrigin)
	{
		myOrigin = aOrigin;
	}

	const Vector2f & Sprite::GetOrigin() const
	{
		return myOrigin;
	}

	void Sprite::SetScale(const Vector2f & aScale)
	{
		myScale = aScale;
	}

	const Vector2f & Sprite::GetScale() const
	{
		return myScale;
	}

	Matrix44f Sprite::GenerateMatrix() const
	{
		Vector2f renderSize = Vector2f(1280.f, 720.f);
		Vector2f textureSize = myTextureSize;

		return Matrix44f::CreateScale(textureSize.x * myScale.x, textureSize.y * myScale.y, 1.f)
			* Matrix44f::CreateTranslation(myPosition.x - myOrigin.x - renderSize.x / 2.f, myPosition.y - myOrigin.y - renderSize.y / 2.f, 0.f)
			* Matrix44f::CreateRotateAroundZ(myRotation)
			* Matrix44f::CreateScale(2.0f / renderSize.x, -2.0f / renderSize.y, 1.f);
	}

	void Sprite::SetEffect(const std::shared_ptr<const Effect> & aEffect)
	{
		myEffect = aEffect;
	}

	const std::shared_ptr<const Effect> & Sprite::GetEffect() const
	{
		return myEffect;
	}

	void Sprite::SetTextureRect(const Vector2f& aTopLeft, const Vector2f& aSize)
	{
		myTextureTopLeft = aTopLeft;
		myTextureSize = aSize;
	}

	const Vector2f & Sprite::GetTextureRectTopLeft() const
	{
		return myTextureTopLeft;
	}

	const Vector2f & Sprite::GetTextureRectSize() const
	{
		return myTextureSize;
	}



	ENGINE_NAMESPACE::Vector4f Sprite::GetBorderPositions() const
	{
		Vector4f myPositions;

		myPositions.x = myPosition.x;
		myPositions.y = myPosition.y;
		myPositions.z = myPosition.x + (myTexture->GetSize().x * myScale.x);
		myPositions.w = myPosition.y + (myTexture->GetSize().y * myScale.y);
		return myPositions;
	}






}
