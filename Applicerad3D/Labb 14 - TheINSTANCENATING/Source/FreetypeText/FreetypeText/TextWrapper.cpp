#include "stdafx.h"
#include "TextWrapper.h"
#include "FreetypeText/FreetypeText.h"
#include "FreetypeBitmap.h"



TextWrapper::TextWrapper()
{
	myFreetypeText = std::make_shared<FreetypeText>();
}


TextWrapper::~TextWrapper()
{
}

FreetypeBitmap TextWrapper::GetBitmap(char aLetter)
{
	FreetypeBitmap converted;

	FT_Bitmap ftBitmap = myFreetypeText->GetBitmap(aLetter);

	converted.buffer = ftBitmap.buffer;
	converted.num_grays = ftBitmap.num_grays;
	converted.palette = ftBitmap.palette;
	converted.palette_mode = ftBitmap.palette_mode;
	converted.pitch = ftBitmap.pitch;
	converted.palette_mode = ftBitmap.palette_mode;
	converted.rows = ftBitmap.rows;
	converted.width = ftBitmap.width;


	return converted;
}
