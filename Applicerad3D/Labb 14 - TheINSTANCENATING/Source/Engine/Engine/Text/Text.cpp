#include "stdafx.h"
#include "Text.h"

#include "Engine\Text\Font.h"
namespace ENGINE_NAMESPACE
{
	Text::Text() : Text(Vector2f(0.f, 0.f), Vector2f(1.f, 1.f), "")
	{
	}

	Text::Text(const Vector2f & aPosition, const Vector2f & aScale, const char* aText)
	{
		myPosition = aPosition;
		myScale = aScale;
		myText = aText;
		myFont = std::make_shared<Font>();

		mySize = Vector2f(0.f, 0.f);
	}

	Text::Text(const Vector2f & aPosition, const Vector2f & aScale, const std::string & aText) : Text(aPosition, aScale, aText.c_str())
	{
	}

	Text::~Text()
	{
	}
	void Text::Render() const
	{
		myFont->RenderText(*this);
	}

	

	void Text::operator+=(const std::string &aText)
	{
		myText += aText;
		mySize = Vector2f(0.f, 0.f);
	}

	void Text::operator+=(const char* aText)
	{
		myText += aText;
		mySize = Vector2f(0.f, 0.f);
	}

	void Text::operator=(const std::string &aText)
	{
		myText = aText;
		mySize = Vector2f(0.f, 0.f);
	}

	void Text::operator=(const char* aText)
	{
		myText = aText;
		mySize = Vector2f(0.f, 0.f);
	}

	void Text::SetPositionBottomLeft(const Vector2f &aPosition)
	{
		myPosition = aPosition;
	}

	void Text::SetPositionTopLeft(const Vector2f &aPosition)
	{
		myPosition = aPosition;
		myPosition.y += GetSize().y;
	}

	const Vector2f & Text::GetPosition() const
	{
		return myPosition;
	}

	void Text::SetText(const std::string &aText)
	{
		myText = aText;
		mySize = Vector2f(0.f, 0.f);
	}

	void Text::SetText(const char* aText)
	{
		myText = aText;
		mySize = Vector2f(0.f, 0.f);
	}

	const std::string & Text::GetText() const
	{
		return myText;
	}

	void Text::SetScale(const Vector2f &aSize)
	{
		myScale = aSize;
		mySize = Vector2f(0.f, 0.f);
	}

	const Vector2f & Text::GetScale() const
	{
		return myScale;
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
		if (mySize == Vector2f(0.f, 0.f) && myText.size() > 0)
		{
			CalculateSize();
		}

		return mySize;
	}

	void Text::CalculateSize()
	{
		mySize = myFont->GetSizeOfText(*this);
	}

}

