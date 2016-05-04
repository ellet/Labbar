#pragma once

#include <string>

#include <Vectors\Vector2.h>

class TextFont;

class TextRenderCommand
{
public:

	TextRenderCommand();
	inline TextRenderCommand(const std::string &aText, const Vector2f &aPosition, const float aSize, TextFont &aTextFont);
	~TextRenderCommand();

	void Render(const Vector2f &aParentPosition, const Vector2f &aParentSize);

private:

	std::string myText;

	Vector2f myPosition;
	float mySize;

	TextFont *myFont;

};

inline TextRenderCommand::TextRenderCommand(const std::string &aText, const Vector2f &aPosition, const float aSize, TextFont &aTextFont)
	: myText(aText), myPosition(aPosition), mySize(aSize), myFont(&aTextFont)
{
}
