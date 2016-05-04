#include "TextFont.h"

#include <fstream>

#include <tga2d\sprite\sprite.h>

TextFont::TextFont()
	:myColumns(0), myRows(0), myCharacterWidth(0), myCharacterHeight(0), myNormalCharacterWidth(0.f), myNormalCharacterHeight(0.f)
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
	mySpriteSheet = std::make_shared<DX2D::CSprite>(DX2D::CSprite(inputString.c_str()));

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
		fontFile >> character;
		myCharacterLocations[character] = characterNumber;
		++characterNumber;
	}

	fontFile.close();

	myNormalCharacterWidth = 1.f / myColumns;
	myNormalCharacterHeight = 1.f / myRows;

	myCharacterWidth = static_cast<unsigned short>(myNormalCharacterWidth * mySpriteSheet->GetImageSize().x);
	myCharacterHeight = static_cast<unsigned short>(myNormalCharacterHeight * mySpriteSheet->GetImageSize().y);

}
