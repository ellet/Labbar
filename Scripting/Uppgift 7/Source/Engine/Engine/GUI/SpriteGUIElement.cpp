#include "stdafx.h"
#include "SpriteGUIElement.h"
#include "Engine/GenericEngineMessages.h"
#include "Engine/Texture/GuiRenderTarget.h"

namespace SB
{
	SpriteGUIElement::SpriteGUIElement(const char * aTexturePath, const Vector2f& aPosition, const bool aIsRoot, const Vector2f& aScale, const Vector2f& aSize) :
		GUIElement(aPosition, aSize, aIsRoot)
	{
		mySprite = nullptr;
		myIsHoverSpriteActivated = false;
		myCurrentSpritePath = "";
		myPreviousSpritePath = "";

		myNormalSpritePath = aTexturePath;
		myCurrentSpritePath = myNormalSpritePath;
		myHoverSprite = aTexturePath;
		if (myHoverSprite.find_first_of(".") != std::string::npos)
		{
			myHoverSprite = myHoverSprite.substr(0, myHoverSprite.find_first_of("."));
			myHoverSprite += "Hover.dds";
		}
		mySprite = std::make_shared<Sprite>();
		mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(aTexturePath));
		mySprite->SetScale(aScale);
		mySize = mySprite->GetTextureRectSize() * aScale;
		myPosition = mySprite->GetPosition();
		if (aSize != Vector2f::Zero)
		{
			mySize = aSize * aScale;
		}
		else if (aSize == Vector2f(-1, -1))
		{
			mySize = Vector2f(1080.f * (Engine::GetRenderer().GetRenderTargetResolution().x / Engine::GetRenderer().GetRenderTargetResolution().y), 1080.f);
		}
		myPosition += aPosition;
		myNormalizedPosition.x = aPosition.x;
		myNormalizedPosition.y = aPosition.y;
		myScale = aScale;
		myIsHoverSpriteActivated = false;

	}

	SpriteGUIElement::~SpriteGUIElement()
	{
	}

	void SpriteGUIElement::SetSprite(const char * aTexturePath)
	{
		if (mySprite != nullptr)
		{
			myCurrentSpritePath = aTexturePath;
			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(myCurrentSpritePath, nullptr, true));
		}
	}

	void SpriteGUIElement::SetIsHoverActivated(bool aValue)
	{
		myIsHoverSpriteActivated = aValue;
	}

	void SpriteGUIElement::HoverFunction()
	{
		if (mySprite != nullptr && myIsHoverSpriteActivated == true)
		{
			PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eHover));
			myPreviousSpritePath = myCurrentSpritePath;

			if (myCurrentSpritePath.find_first_of(".") != std::string::npos)
			{
				myHoverSprite = myCurrentSpritePath.substr(0, myCurrentSpritePath.find_first_of("."));
				myHoverSprite += "Hover.dds";
			}


			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(myHoverSprite));
		}
		GUIElement::HoverFunction();
	}

	void SpriteGUIElement::ExitHoverFunction()
	{
		if (mySprite != nullptr && myIsHoverSpriteActivated == true)
		{
			PostMaster::Post<ChangeCursorMessage>(ChangeCursorMessage(eCursorState::eNormal));
			mySprite->SetTexture(Engine::GetResourceManager().Get<Texture>(myCurrentSpritePath));
		}
	}

	void SpriteGUIElement::SetRotation(const float aRotation)
	{
		mySprite->SetRotation(aRotation);
	}

	void SpriteGUIElement::SetColor(const Vector4f & aColor)
	{
		mySprite->SetColor(aColor);
	}

	void SpriteGUIElement::Update(const SB::Time &aDeltaTime)
	{
		GUIElement::Update(aDeltaTime);
	}

	void SpriteGUIElement::Render(const GuiRenderTarget & aRenderTarget)
	{
		if (mySprite != nullptr)
		{
			mySprite->SetPosition(Vector2f(myPosition.x, myPosition.y));
			aRenderTarget.Render(*mySprite);
		}

		GUIElement::Render(aRenderTarget);
	}

}
