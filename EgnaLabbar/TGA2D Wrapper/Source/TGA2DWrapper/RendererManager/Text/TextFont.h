#pragma once

#include <string>
#include <memory>

#include <StaticArray\StaticArray.h>
#include <Vectors\Vector4.h>
#include <DLDebug\DL_Debug.h>

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
}

class TextFont
{
public:

	TextFont();
	~TextFont();

	void LoadFont(const std::string &aFont);
	
	inline Vector4f GetCharacterLocation(const unsigned char aCharacter) const;
	inline DX2D::CSprite* GetFreeSpriteSheet();
	inline void ResetUsedSprites();

	inline unsigned short GetCharacterWidth() const;
	inline unsigned short GetCharacterHeight() const;

	inline float GetNormalCharacterWidth() const;
	inline float GetNormalCharacterHeight() const;

	inline std::shared_ptr<DX2D::CSpriteBatch> GetSpriteBatch() const;

private:

	unsigned short myColumns, myRows;
	unsigned short myCharacterWidth, myCharacterHeight;
	float myNormalCharacterWidth, myNormalCharacterHeight;

	static const unsigned short constMaxCharacterSprites = 512;

	unsigned short myUsedSpriteCount;
	CommonUtilities::StaticArray<std::shared_ptr<DX2D::CSprite>, constMaxCharacterSprites> mySpriteSheets;
	std::shared_ptr<DX2D::CSpriteBatch> mySpriteBatch;

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
inline DX2D::CSprite* TextFont::GetFreeSpriteSheet()
{
	DL_ASSERT(myUsedSpriteCount < constMaxCharacterSprites, "Sprite overflow. No free text characters, tell a coder to increase the max character count.");
	return mySpriteSheets[myUsedSpriteCount++].get();
}
inline void TextFont::ResetUsedSprites()
{
	myUsedSpriteCount = 0;
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

inline std::shared_ptr<DX2D::CSpriteBatch> TextFont::GetSpriteBatch() const
{
	return mySpriteBatch;
}
