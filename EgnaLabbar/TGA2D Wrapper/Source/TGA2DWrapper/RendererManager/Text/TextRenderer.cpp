#include "TextRenderer.h"

#include <DLDebug\DL_Debug.h>

#include "..\RenderManager.h"
#include "TextRenderCommand.h"

TextRenderer::TextRenderer()
{
}
TextRenderer::~TextRenderer()
{
}

void TextRenderer::LoadFont(const std::string &aFontPath)
{
	myFont.LoadFont(aFontPath);
}

size_t TextRenderer::GetNextNewLine(const std::string &aText, const size_t aStartIndex, const size_t anEndIndex) const
{
	
	bool run = true;
	
	for (size_t i = aStartIndex; run == true; ++i)
	{
		if (i >= anEndIndex || i >= aText.size() - 1 || aText[i] == '\n')
		{
			return i + 1;
		}
	}

	DL_ASSERT(run, "TextRenderer::GetNextLine() died.");
	return 0;

}
size_t TextRenderer::GetNextLine(const std::string &aText, const float aSize, const float aMaxWidth, const size_t aStartIndex) const
{
	
	size_t lastIndex = MaxWidthCharacter(aSize, aMaxWidth) + aStartIndex;
	if (lastIndex >= aText.size())
	{
		return aText.size();
	}

	for (size_t i = aStartIndex; i < lastIndex; ++i)
	{
		if (aText[i] == '\n')
		{
			return i + 1;
		}
	}

	for (size_t i = lastIndex - 1; i >= aStartIndex; --i)
	{
		if (i > lastIndex)
		{
			return lastIndex;
		}
		if (aText[i] == ' ')
		{
			return i + 1;
		}
	}

	return lastIndex;

}

size_t TextRenderer::MaxWidthCharacter(const float aSize, const float aWidth) const
{
	return static_cast<size_t>(aWidth / (myFont.GetCharacterWidth() * aSize));
}
size_t TextRenderer::MaxHeightCharacter(const float aSize, const float aHeight) const
{
	return static_cast<size_t>(aHeight / (myFont.GetCharacterHeight() * aSize));
}

float TextRenderer::TextWidth(const std::string &aText, const float aSize, const size_t aStartIndex, const size_t anEndIndex) const
{
	
	size_t numberOfCharacters = anEndIndex + 1;
	if (aText.size() < anEndIndex)
	{
		numberOfCharacters = aText.size();
	}
	numberOfCharacters -= aStartIndex;

	return myFont.GetCharacterWidth() * aSize * numberOfCharacters;

}
float TextRenderer::TextHeight(const float aSize) const
{
	return myFont.GetCharacterHeight() * aSize;
}

void TextRenderer::Draw(const std::string &aText, const Vector2f &aPosition, const float aSize,
	const Vector4f &aColor, const float aMaxWidth, const float aMaxHeight,
	const size_t aStartIndex, const size_t anEndIndex)
{
	
	(aPosition);
	(aColor);

	size_t maxHeight = MaxHeightCharacter(aSize, aMaxHeight);
	
	size_t currentIndex = aStartIndex;
	size_t lastIndex;

	for (size_t i = 0; i < maxHeight; ++i)
	{

		lastIndex = currentIndex;
		currentIndex = GetNextLine(aText, aSize, aMaxWidth, currentIndex);

		if (currentIndex > anEndIndex)
		{
			currentIndex = anEndIndex;
		}

		RenderManager::AddRenderCommandText(TextRenderCommand(aText.substr(lastIndex, currentIndex - lastIndex), Vector2f(aPosition.x, aPosition.y + myFont.GetCharacterHeight() * i * aSize), aSize, myFont));

		//for (size_t j = lastIndex; j < currentIndex; ++j)
		//{
		//	RenderManager::AddRenderCommand(RenderCommand(myFont.GetSpriteSheet(),
		//		Vector2f(
		//			//love.graphics.rectangle("fill", x, 0, width, font:getHeight() * #text + 2 + 2 * #text)
		//			aPosition.x + myFont.GetCharacterWidth() * (j - lastIndex) * aSize,
		//			aPosition.y + myFont.GetCharacterHeight() * i * aSize
		//		),
		//		size, Vector2f::Zero, 0.f, aColor, myFont.GetCharacterLocation(aText[j])
		//	));
		//}

	}

}
