#pragma once
#include "Engine/Sprite/Sprite.h"
#include "Engine\GUI\GUIElement.h"
class Sprite;


namespace SB
{
	class SpriteGUIElement : public GUIElement
	{
	public:
		SpriteGUIElement(const char * aTexturePath, const Vector2f& aPosition = Vector2f::Zero, const bool aIsRoot = false, const Vector2f& aScale = Vector2f::One, const Vector2f& aSize = Vector2f::Zero);
		~SpriteGUIElement();
		void SetSprite(const char * aTexturePath);
		void SetIsHoverActivated(bool aValue);
		inline const Sprite & GetSprite() const;
		inline const std::string & GetCurrentSpritePath() const;
		inline float GetRotation() const;

		virtual void Update(const SB::Time &aDeltaTime) override;
		virtual void Render(const GuiRenderTarget & aRenderTarget) override;
		void HoverFunction();
		void ExitHoverFunction();
		void SetRotation(const float aRotation);
		void SetColor(const Vector4f & aColor);
	protected:
		std::shared_ptr<Sprite> mySprite;
		std::string myHoverSprite;
		std::string myNormalSpritePath;
		std::string myCurrentSpritePath;
		std::string myPreviousSpritePath;
		bool myIsHoverSpriteActivated;
	private:
		
	};

	const Sprite & SpriteGUIElement::GetSprite() const
	{
		return *mySprite;
	}

	float SpriteGUIElement::GetRotation() const
	{
		return mySprite->GetRotation();
	}

	const std::string & SpriteGUIElement::GetCurrentSpritePath() const
	{
		return myCurrentSpritePath;
	}
}
