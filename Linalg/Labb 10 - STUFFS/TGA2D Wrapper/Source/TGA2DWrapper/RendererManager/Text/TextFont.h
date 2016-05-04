#pragma once

#include <string>
#include <memory>

#include <StaticArray\StaticArray.h>
#include <Vectors\Vector4.h>

namespace DX2D
{
	class CSprite;
}

class TextFont
{
public:

	TextFont();
	~TextFont();

	void LoadFont(const std::string &aFont);
	
	inline Vector4f GetCharacterLocation(const unsigned char aCharacter) const;
	inline DX2D::CSprite* GetSpriteSheet() const;

	inline unsigned short GetCharacterWidth() const;
	inline unsigned short GetCharacterHeight() const;

	inline float GetNormalCharacterWidth() const;
	inline float GetNormalCharacterHeight() const;

private:

	unsigned short myColumns, myRows;
	unsigned short myCharacterWidth, myCharacterHeight;
	float myNormalCharacterWidth, myNormalCharacterHeight;

	std::shared_ptr<DX2D::CSprite> mySpriteSheet;

	CommonUtilities::StaticArray<unsigned short, CHAR_MAX> myCharacterLocations;

};

inline Vector4f TextFont::GetCharacterLocation(const unsigned char aCharacter) const
{
	
	const unsigned short x = myCharacterLocations[aCharacter] % myColumns;
	const unsigned short y = myCharacterLocations[aCharacter] / myColumns;
	
	float characterSpriteWidth = 1.f / myColumns;
	float characterSpriteHeight = 1.f / myRows;

	return Vector4f(
		characterSpriteWidth * x,
		characterSpriteHeight * y,
		characterSpriteWidth * (x + 1),
		characterSpriteHeight * (y + 1)
	);

}
inline DX2D::CSprite* TextFont::GetSpriteSheet() const
{
	return mySpriteSheet.get();
}

inline unsigned short TextFont::GetCharacterWidth() const
{
	return myCharacterWidth;
}
inline unsigned short TextFont::GetCharacterHeight() const
{
	return myCharacterHeight;
}

inline float TextFont::GetNormalCharacterWidth() const
{
	return myNormalCharacterWidth;
}
inline float TextFont::GetNormalCharacterHeight() const
{
	return myNormalCharacterHeight;
}
