#pragma once
#include "Vector2.h"
#include <string>

class hgeSprite;
class hgeFont;

class BaseRenderCommand
{
public:
	virtual ~BaseRenderCommand()
	{}
	virtual void Render() = 0;

};

class RenderCommand : public BaseRenderCommand
{
public:
	RenderCommand();
	RenderCommand(hgeSprite & aSprite, const CommonUtilities::Vector2f & aPosition) : mySprite(&aSprite), myPosition(aPosition)
	{}

	~RenderCommand();

	void Render() override;

private:
	hgeSprite * mySprite;
	CommonUtilities::Vector2f myPosition;
};

class StretchedRenderCommand : public BaseRenderCommand
{
public:
	StretchedRenderCommand()
	{}
	StretchedRenderCommand(hgeSprite & aSprite, const CommonUtilities::Vector2f & aPosition, const CommonUtilities::Vector2f & aOtherPosition) : mySprite(&aSprite), myPosition(aPosition), myOtherPosition(aOtherPosition)
	{}

	~StretchedRenderCommand()
	{}

	void Render() override;

private:
	hgeSprite * mySprite;
	CommonUtilities::Vector2f myPosition;
	CommonUtilities::Vector2f myOtherPosition;
};

class TextRenderCommand : public BaseRenderCommand
{
public:
	TextRenderCommand()
	{}
	TextRenderCommand(hgeFont & aFont, const CommonUtilities::Vector2f & aPosition, const unsigned int aAlignID, const std::string & aText) : myFont(&aFont), myPosition(aPosition), myAlignbullshit(aAlignID), myText(aText)
	{}

	~TextRenderCommand()
	{}

	void Render() override;

private:
	hgeFont* myFont;
	CommonUtilities::Vector2f myPosition;
	unsigned int myAlignbullshit;
	std::string myText;
};