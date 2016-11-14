#pragma once
#include "Engine\GUI\GUIElement.h"


namespace ENGINE_NAMESPACE
{
	

	class Font;

	class Text
	{
	public:
		Text();
		Text(const Vector2f & aPosition, const Vector2f & aScale, const char* aText);
		Text(const Vector2f & aPosition, const Vector2f & aScale, const std::string & aText);
		~Text();

		void Render()const;

		void operator= (const char* aText);
		void operator= (const std::string &aText);
		void operator+= (const char* aText);
		void operator+= (const std::string &aText);

		void SetPositionBottomLeft(const Vector2f &aPosition);
		void SetPositionTopLeft(const Vector2f &aPosition);
		const Vector2f & GetPosition() const;
		void SetText(const std::string &aText);
		void SetText(const char* aText);
		const std::string & GetText() const;
		void SetScale(const Vector2f &aScale);
		const Vector2f & GetScale() const;


		Vector4f GetBoundaries();
		const Vector2f &GetSize();
	private:
		std::shared_ptr<Font> myFont;
		std::string myText;
		Vector2f myPosition;
		Vector2f myScale;

		Vector2f mySize;
		void CalculateSize();
	};
}
