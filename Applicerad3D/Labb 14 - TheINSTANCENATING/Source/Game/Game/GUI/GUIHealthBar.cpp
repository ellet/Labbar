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
		mySprite->SetColor(Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
	}


	GUIHealthBar::~GUIHealthBar()
	{
	}

	ENGINE_NAMESPACE::ReceiveResult GUIHealthBar::Receive(const PlayerHealthChangedMessage & aMessage)
	{
		SetFillAmount(aMessage.myCurrentHealth);
		float xScale = GetCurrentFillAmount();
		mySprite->SetTextureRect(Vector2f(myTextureRect.x, myTextureRect.y), Vector2f(myTextureRect.z * xScale, myTextureRect.w));
		return ReceiveResult::eContinue;
	}

	void GUIHealthBar::SetFillAmount(const float aNewValue)
	{
		myPlayerCurrentHealth = aNewValue;

		const float FillAmount = GetCurrentFillAmount();
		if (FillAmount >= 0.9)
		{
			mySprite->SetColor(Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (FillAmount >= 0.75)
		{
			mySprite->SetColor(Vector4f(0.75f, 1.0f, 0.4f, 1.0f));
		}
		else if (FillAmount >= 0.5)
		{
			mySprite->SetColor(Vector4f(0.75f, 1.0f, 0.4f, 1.0f));
		}
		else if (FillAmount >= 0.25)
		{
			mySprite->SetColor(Vector4f(1.0f, 0.65f, 0.14f, 1.0f));
		}
		else if (FillAmount >= 0.1)
		{
			mySprite->SetColor(Vector4f(1.0f, 0.35f, 0.0f, 1.0f));
		}
		else
		{
			mySprite->SetColor(Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	void GUIHealthBar::Update()
	{
		GUIElement::Update();
	}

	void GUIHealthBar::Render()
	{
		GUIElement::Render();
	}

}