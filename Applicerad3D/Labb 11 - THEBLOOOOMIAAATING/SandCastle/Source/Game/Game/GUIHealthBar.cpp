#include "stdafx.h"
#include "GUIHealthBar.h"


namespace ENGINE_NAMESPACE
{
	GUIHealthBar::GUIHealthBar(const char * aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize) : GUIElement(aTexturePath, aPosition, aScale, aSize)
	{
		myPlayerMaxHealth = 100.f;
		myPlayerCurrentHealth = myPlayerMaxHealth;
		myTextureRect.x = mySprite->GetTextureRectTopLeft().x;
		myTextureRect.y = mySprite->GetTextureRectTopLeft().y;
		myTextureRect.z = mySprite->GetTextureRectSize().x;
		myTextureRect.w = mySprite->GetTextureRectSize().y;
	}


	GUIHealthBar::~GUIHealthBar()
	{
	}

	ENGINE_NAMESPACE::ReceiveResult GUIHealthBar::Receive(const PlayerHealthChangedMessage & aMessage)
	{
		myPlayerCurrentHealth = aMessage.aCurrentHealth;
		float xScale = aMessage.aCurrentHealth / myPlayerMaxHealth;
		mySprite->SetTextureRect(Vector2f(myTextureRect.x, myTextureRect.y), Vector2f(myTextureRect.z * xScale, myTextureRect.w));
		return ReceiveResult::eContinue;
	}

	void GUIHealthBar::Update()
	{
		GUIElement::Update();
	}

	void GUIHealthBar::Render()
	{
		
		mySprite->SetColor(Vector4f(1.0f, 0.0f, 0.0f, 1.0f));

		GUIElement::Render();
	}

}