#include "TextFont.h"

#include <fstream>

#include <tga2d\sprite\sprite.h>
#include <tga2d\sprite\sprite_batch.h>

TextFont::TextFont()
	:myColumns(0), myRows(0),
	myCharacterWidth(0), myCharacterHeight(0),
	myNormalCharacterWidth(0.f), myNormalCharacterHeight(0.f),
	myUsedSpriteCount(0)
{
	for (unsigned char i = 0; i < CHAR_MAX; ++i)
	{
		myCharacterLocations[i] = '\0';
	}
}
TextFont::~TextFont()
{
}

void TextFont::LoadFont(const std::string &aFont)
{
	
	std::ifstream fontFile(aFont);

	std::string inputString;

	std::getline(fontFile, inputString);

	myUsedSpriteCount = 0;
	for (unsigned short i = 0; i < constMaxCharacterSprites; ++i)
	{
		mySpriteSheets[i] = std::make_shared<DX2D::CSprite>(DX2D::CSprite(inputString.c_str()));
	}
	
	mySpriteBatch = std::make_shared<DX2D::CSpriteBatch>(DX2D::CSpriteBatch(false));
	mySpriteBatch->Init(inputString.c_str());

	std::getline(fontFile, inputString);
	myColumns = static_cast<unsigned short>(std::stoi(inputString));

	std::getline(fontFile, inputString);
	myRows = static_cast<unsigned short>(std::stoi(inputString));

	std::getline(fontFile, inputString);
	unsigned short emtpyCharacter = static_cast<unsigned short>(std::stoi(inputString));
	for (unsigned char i = 0; i < CHAR_MAX; ++i)
	{
		myCharacterLocations[i] = emtpyCharacter;
	}

	unsigned char character;
	unsigned char characterNumber = 0;

	while (fontFile.eof() == false)
	{
		fontFile >> std::noskipws >> character;
		myCharacterLocations[character] = characterNumber;
		++characterNumber;
	}

	fontFile.close();

	myNormalCharacterWidth = 1.f / myColumns;
	myNormalCharacterHeight = 1.f / myRows;

	myCharacterWidth = static_cast<unsigned short>(myNormalCharacterWidth * mySpriteSheets[0]->GetImageSize().x);
	myCharacterHeight = static_cast<unsigned short>(myNormalCharacterHeight * mySpriteSheets[0]->GetImageSize().y);

}
