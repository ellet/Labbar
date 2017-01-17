#pragma once
#include "Engine\GUI\GUIElement.h"


namespace SB
{
	class Font;

	class Text
	{
	public:
		Text(bool aTypeChactersOneByOne = false);
		Text(const Vector2f & aPosition, const Vector2f & aScale, const char* aText, bool aTypeChactersOneByOne = false);
		Text(const Vector2f & aPosition, const Vector2f & aScale, const std::string & aText, bool aTypeChactersOneByOne = false);
		~Text();

		void SetFont(const std::shared_ptr<Font> &aFont);

		void Update(const SB::Time &aDeltaTime);

		//Waits until the font is fully loaded until render
		void ForceRender(const GuiRenderTarget & aRenderTarget)const;

		//Renders only if font is fully loaded
		void Render(const GuiRenderTarget & aRenderTarget) const;

		void operator= (const char* aText);
		void operator= (const std::string &aText);
		void operator+= (const char* aText);
		void operator+= (const std::string &aText);

		void SetMaxPosition(Vector2f aSize);
		void SetPositionBottomLeft(const Vector2f &aPosition);
		void SetPositionTopLeft(const Vector2f &aPosition);
		const Vector2f & GetPosition() const;
		void SetText(const std::string &aText);
		void SetText(const char* aText);
		const std::string & GetText() const;
		void SetScale(const Vector2f &aScale);
		const Vector2f & GetScale() const;
		void SetFontColor(const Vector4f& aColor);
		const Vector4f& GetColor() const;
		void SetColor(const Vector4f &aColor);

		void SetCharactersPerSecond(float aCharactersPerSecond);
		Vector4f GetBoundaries();
		const Vector2f &GetSize();
		const SB::Vector2f & GetMaxPosition() const;

		unsigned short GetLastCharacterToRender() const;

		bool GetAndResetHasChanged();
	private:
		std::shared_ptr<Font> myFont;
		std::string myText;
		Vector4f myColor;
		Vector2f myPosition;
		Vector2f myAllowedSpace;
		Vector2f myScale;
		Vector2f mySize;
		bool myHasChanged;
		void CalculateSize();
		unsigned short myLastCharacterToRender;
		bool myTypeCharactersOneByOne;

		float myCharactersPerSecond;
		SB::Time myTypingTimer;
	};
}
