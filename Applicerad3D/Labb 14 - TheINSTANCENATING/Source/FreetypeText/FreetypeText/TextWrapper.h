#pragma once
#include <memory>
#include "FreetypeBitmap.h"

class FreetypeText;



class TextWrapper
{
public:
	TextWrapper();
	~TextWrapper();

	FreetypeBitmap GetBitmap(char aLetter);
private:
	std::shared_ptr <FreetypeText> myFreetypeText;
};

