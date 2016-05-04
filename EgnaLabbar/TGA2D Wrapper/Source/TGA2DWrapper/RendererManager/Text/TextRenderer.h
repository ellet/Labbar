#pragma once

#include <string>

#include <Vectors\vector2.h>

#include "TextFont.h"

class TextRenderer
{
public:

	TextRenderer();
	~TextRenderer();

	void LoadFont(const std::string &aFontPath);
	
	size_t GetNextNewLine(const std::string &aText, const size_t aStartIndex = 0, const size_t anEndIndex = static_cast<size_t>(-1)) const;
	size_t GetNextLine(const std::string &aText, const float aSize, const float aMaxWidth, const size_t aStartIndex = 0) const;

	size_t MaxWidthCharacter(const float aSize, const float aWidth) const;
	size_t MaxHeightCharacter(const float aSize, const float aHeight) const;

	float TextWidth(const std::string &aText, const float aSize, const size_t aStartIndex = 0, const size_t anEndIndex = static_cast<size_t>(-1)) const;
	float TextHeight(const float aSize) const;

	void Draw(
		const std::string &aText, const Vector2f &aPosition, const float aSize,
		const Vector4f &aColor = Vector4f::One,
		const float aMaxWidth = 1920.f, const float aMaxHeight = 1080.f,
		const size_t aStartIndex = 0, const size_t anEndIndex = static_cast<size_t>(-1)
	);

private:

	TextFont myFont;

};
