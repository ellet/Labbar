#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H


struct FreetypeBitmap;


class FreetypeText
{
public:
	FreetypeText();
	~FreetypeText();

	void PrintLetter(char aLetter);
	FT_Bitmap GetBitmap(char aLetter) const;
private:

	FT_Face myFace;

};
