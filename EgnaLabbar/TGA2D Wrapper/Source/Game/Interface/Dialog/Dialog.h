#pragma once

#include <string>

namespace DX2D
{
	class CSprite;
}

class Dialog
{
public:

	Dialog();
	~Dialog();

	void SetText(const std::string &aText);
	const std::string& GetText() const;

	void SetCharacterSprite(DX2D::CSprite *aCharacterSprite);
	DX2D::CSprite* GetCharacterSprite() const;

private:

	DX2D::CSprite *myCharacterSprite;

	std::string myText;

};
