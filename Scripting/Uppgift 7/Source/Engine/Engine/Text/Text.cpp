#include "stdafx.h"
#include "Text.h"

#include "Engine\Text\Font.h"

#include <Utilities/HelperFunctions/BoolHandling.h>
namespace SB
{
	Text::Text(bool aTypeChactersOneByOne) : Text(Vector2f(0.f, 0.f), Vector2f(1.f, 1.f), "", aTypeChactersOneByOne)
	{
	}

	Text::Text(const Vector2f & aPosition, const Vector2f & aScale, const char* aText, bool aTypeChactersOneByOne)
	{
		SetPositionTopLeft(aPosition);
		SetText(aText);
		myScale = aScale;

		myColor = Vector4f::One;
		myTypeCharactersOneByOne = aTypeChactersOneByOne;

		myTypingTimer = 0;
		if (aTypeChactersOneByOne == true)
		{
			myLastCharacterToRender = 0;
		}
		else
		{
			unsigned short charLength = 0;

			while (aText[charLength] != '\0')
			{
				charLength++;
			}
			myLastCharacterToRender = charLength;
		}
	}

	Text::Text(const Vector2f & aPosition, const Vector2f & aScale, const std::string & aText, bool aTypeChactersOneByOne) : Text(aPosition, aScale, aText.c_str(), aTypeChactersOneByOne)
	{
	}

	Text::~Text()
	{
	}

	void Text::SetFont(const std::shared_ptr<Font> &aFont)
	{
		myFont = aFont;
	}

	void Text::Update(const SB::Time &aDeltaTime)
	{
		myTypingTimer += aDeltaTime;

		while (myTypingTimer.InSeconds() >= 1.f / myCharactersPerSecond && myLastCharacterToRender < myText.length())
		{
			myLastCharacterToRender++;
			myTypingTimer = 0.f;

		}
	}

	void Text::ForceRender(const GuiRenderTarget & aRenderTarget) const
	{
		if (myFont == nullptr)
		{
			Error("Trying to render the text " + myText + " without a font.");
		}
		myFont->Prepare(false);
		myFont->SetFontColor(myColor);
		myFont->RenderText(aRenderTarget, *this);
	}

	void Text::Render(const GuiRenderTarget & aRenderTarget) const
	{
		if (myFont == nullptr)
		{
			Error("Trying to render the text " + myText + " without a font.");
		}
		if (myFont->Prepare(true) == true)
		{
			myFont->SetFontColor(myColor);
			myFont->RenderText(aRenderTarget, *this);
		}
	}
	

	void Text::operator+=(const std::string &aText)
	{
		SetText(myText + aText);
	}

	void Text::operator+=(const char* aText)
	{
		SetText(myText + aText);
	}

	void Text::operator=(const std::string &aText)
	{
		SetText(aText);
	}

	void Text::operator=(const char* aText)
	{
		SetText(aText);
	}

	void Text::SetMaxPosition(Vector2f aSize)
	{
		myAllowedSpace = aSize;
	}

	void Text::SetPositionBottomLeft(const Vector2f &aPosition)
	{
		myPosition = aPosition;
	}

	void Text::SetPositionTopLeft(const Vector2f &aPosition)
	{
		myPosition = aPosition;
		if (myText.size() > 0)
		{
			if (myFont->Prepare(true) == true)
			{
				myPosition.y += GetSize().y;
			}
		}
	}

	const Vector2f & Text::GetPosition() const
	{
		return myPosition;
	}

	void Text::SetText(const std::string &aText)
	{
		SetText(aText.c_str());		
	}

	void Text::SetText(const char* aText)
	{
		myText = aText;

		if (myTypeCharactersOneByOne == true)
		{
			myLastCharacterToRender = 0;
		}
		else
		{
			myLastCharacterToRender = static_cast<unsigned short> (myText.length() - 1);
		}

		myHasChanged = true;
	}

	const std::string & Text::GetText() const
	{
		return myText;
	}

	void Text::SetScale(const Vector2f &aSize)
	{
		myScale = aSize;
		myHasChanged = true;
	}

	const Vector2f & Text::GetScale() const
	{
		return myScale;
	}

	void Text::SetFontColor(const Vector4f& aColor)
	{
		if (myFont == nullptr)
		{
			Error("Trying to set color to the text " + myText + ", but it doesn't have a font.");
		}
		myFont->SetFontColor(aColor);
	}

	const Vector4f& Text::GetColor() const
	{
		return myColor;
	}

	void Text::SetColor(const Vector4f &aColor)
	{
		myColor = aColor;
	}

	void Text::SetCharactersPerSecond(float aCharactersPerSecond)
	{
		myCharactersPerSecond = aCharactersPerSecond;
	}

	Vector4f Text::GetBoundaries()
	{
		CalculateSize();

		Vector4f boundaries;
		boundaries.x = myPosition.x;
		boundaries.y = myPosition.y - GetSize().y;
		boundaries.z = boundaries.x + GetSize().x;
		boundaries.w = boundaries.y + GetSize().y;
		return boundaries;
	}

	const Vector2f & Text::GetSize()
	{
		if (myHasChanged == true && myText.size() > 0)
		{
			CalculateSize();
			myHasChanged = false;
		}

		return mySize;
	}

	void Text::CalculateSize()
	{
		if (myFont == nullptr)
		{
			Error("Trying to calculate size of the text " + myText + ", but it doesn't have a font.");
		}
		myFont->CalculateMaxHeight();
		mySize = myFont->GetSizeOfText(*this);
	}

	const SB::Vector2f & Text::GetMaxPosition() const
	{
		return myAllowedSpace;
	}

	unsigned short Text::GetLastCharacterToRender() const
	{
		return myLastCharacterToRender;
	}

	bool Text::GetAndResetHasChanged()
	{
		return SB::HelperFunction::GetAndResetBool(myHasChanged);
	}

}

