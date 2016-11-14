#include "stdafx.h"
#include "GUIOverheatBar.h"

namespace ENGINE_NAMESPACE
{
	GUIOverheatBar::GUIOverheatBar(const char* aTexturePath, const Vector2f& aPosition, const Vector2f& aScale, const Vector2f& aSize, const bool aPrimary) : GUIElement(aTexturePath, aPosition, aScale, aSize)
	{
		myMaxOverheat = 100.f;
		myTextureRect.x = mySprite->GetTextureRectTopLeft().x;
		myTextureRect.y = mySprite->GetTextureRectTopLeft().y;
		myTextureRect.z = mySprite->GetTextureRectSize().x;
		myTextureRect.w = mySprite->GetTextureRectSize().y;
		myIsPrimary = aPrimary;
	}

	GUIOverheatBar::~GUIOverheatBar()
	{
	}

	void GUIOverheatBar::Render()
	{
		GUIElement::Render();
	}

	ReceiveResult GUIOverheatBar::Receive(const OverheatChangedMessage& aMessage)
	{
		if (aMessage.myIsPrimary == myIsPrimary) //If primary/secondary weapon states match between message and overheat bar; set fill amount
		{
			SetFillAmount(aMessage.myCurrentOverheatValue);
			float xScale = GetCurrentFillAmount();
			mySprite->SetTextureRect(Vector2f(myTextureRect.x, myTextureRect.y), Vector2f(myTextureRect.z * xScale, myTextureRect.w));
		}
		
		return ReceiveResult::eContinue;
	}

	void GUIOverheatBar::SetFillAmount(const float aNewValue)
	{
		myCurrentOverheat = aNewValue;

		const float FillAmount = GetCurrentFillAmount();
		if (FillAmount < 0.1)
		{
			mySprite->SetColor(Vector4f(0.76f, 0.82f, 1.0f, 1.0f));
		}
		else if (FillAmount < 0.25)
		{
			mySprite->SetColor(Vector4f(0.45f, 0.65f, 1.0f, 1.0f));
		}
		else if (FillAmount < 0.5)
		{
			mySprite->SetColor(Vector4f(1.0f, 0.75f, 0.5f, 1.0f));
		}
		else if (FillAmount < 0.75)
		{
			mySprite->SetColor(Vector4f(1.0f, 0.57f, 0.38f, 1.0f));
		}
		else if (FillAmount < 0.99)
		{
			mySprite->SetColor(Vector4f(1.0f, 0.38f, 0.34f, 1.0f));
		}
		else
		{
			mySprite->SetColor(Vector4f(1.0f, 0.15f, 0.2f, 1.0f));
		}
	}

}
