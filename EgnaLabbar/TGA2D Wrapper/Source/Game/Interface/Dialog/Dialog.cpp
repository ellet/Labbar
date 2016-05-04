#include "stdafx.h"
#include "Dialog.h"

Dialog::Dialog()
{
}
Dialog::~Dialog()
{
}

void Dialog::SetText(const std::string &aText)
{
	myText = aText;
}
const std::string& Dialog::GetText() const
{
	return myText;
}

void Dialog::SetCharacterSprite(DX2D::CSprite *aCharacterSprite)
{
	myCharacterSprite = aCharacterSprite;
}
DX2D::CSprite* Dialog::GetCharacterSprite() const
{
	return myCharacterSprite;
}
