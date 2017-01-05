
#pragma once

namespace SB
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void SetTexture(const std::shared_ptr<const Texture> & aTexture);
		const std::shared_ptr<const Texture> & GetTexture() const;

		void SetPosition(const Vector2f & aPosition);
		const Vector2f & GetPosition() const;

		void SetColor(const Vector4f & aColor);
		const Vector4f & GetColor() const;

		void SetRotation(const float aRotation);
		float GetRotation() const;

		void SetOrigin(const Vector2f & aOrigin);
		const Vector2f & GetOrigin() const;

		void SetScale(const Vector2f & aScale);
		const Vector2f & GetScale() const;
		void SetPositionInNormalizedSpace(const Vector2f& aPosition);
		void SetEffect(const std::shared_ptr<const Effect> & aEffect);
		const std::shared_ptr<const Effect> & GetEffect() const;

		Vector4f GetBorderPositions() const;
		void SetTextureRect(const Vector2f& aTopLeft, const Vector2f& aSize);
		const Vector2f & GetTextureRectTopLeft() const;
		const Vector2f & GetTextureRectSize() const;

		Vector2f GetRenderSize() const;

		Matrix44f GenerateMatrix() const;

	private:
		std::shared_ptr<const Texture> myTexture;
		std::shared_ptr<const Effect> myEffect;

		Vector4f myColor;
		Vector2f myPosition;
		Vector2f myOrigin;
		Vector2f myScale;
		Vector2f myTextureTopLeft;
		Vector2f myTextureSize;
		float myRotation;
	};

	inline void Sprite::SetPosition(const Vector2f & aPosition)
	{
		myPosition = aPosition;
	}

	inline const Vector2f & Sprite::GetPosition() const
	{
		return myPosition;
	}
}
