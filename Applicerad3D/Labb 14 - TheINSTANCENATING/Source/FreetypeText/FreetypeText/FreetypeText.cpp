#include "stdafx.h"
#include "FreetypeText.h"




#ifdef _DEBUG
#pragma comment (lib, "..\\..\\extlibs\\freetype27d.lib")
#else
#pragma comment (lib, "..\\..\\extlibs\\freetype27.lib")
#endif

FreetypeText::FreetypeText()
{
	FT_Library library;


	FT_Error error;

	error = FT_Init_FreeType(&library);

	if (error)
	{
		//error happened. abort! abort!

	}

	error = FT_New_Face(library, "fonts\\AmaticSC-Regular.ttf", 0, &myFace);

	if (error == FT_Err_Unknown_File_Format)
	{
		 
	}
	else if (error)
	{
		//error happened. abort! abort!
	}

	error = FT_Set_Char_Size(myFace, 0, 16 * 64, 800, 800);
	if (error)
	{
		//error happened. abort! abort!
	}

}


FreetypeText::~FreetypeText()
{
}

void FreetypeText::PrintLetter(char aLetter)
{
	FT_UInt glyphIndex = FT_Get_Char_Index(myFace, aLetter);

	FT_Error error;

	error = FT_Load_Glyph(myFace, glyphIndex, FT_LOAD_DEFAULT);
	if (error)
	{
		//FAIL
	}
	FT_Vector origin;
	origin.x = 32;
	origin.y = 0;

	FT_Glyph glyph;

	error = FT_Get_Glyph(myFace->glyph, &glyph);

	if (error)
	{
		//FAIL
	}
	error = FT_Glyph_To_Bitmap(&glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL, &origin, true);
	if (error)
	{
		//FAIL
	}
	myFace->glyph->bitmap;
}

FT_Bitmap FreetypeText::GetBitmap(char aLetter) const
{
	FT_UInt glyphIndex = FT_Get_Char_Index(myFace, aLetter);

	FT_Error error;

	error = FT_Load_Glyph(myFace, glyphIndex, FT_LOAD_DEFAULT);
	if (error)
	{
		//FAIL
	}
	FT_Vector origin;
	origin.x = 32;
	origin.y = 0;

	FT_Glyph glyph;

	error = FT_Get_Glyph(myFace->glyph, &glyph);

	if (error)
	{
		//FAIL
	}
	error = FT_Glyph_To_Bitmap(&glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL, &origin, true);
	if (error)
	{
		//FAIL
	}

	FT_BitmapGlyph bitmap = (FT_BitmapGlyph)glyph;
	return bitmap->bitmap;
}