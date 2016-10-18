#pragma once

#include "hgesprite.h"
#include "CU_Vector.h"

class VisualRep
{
public:
	VisualRep();
	~VisualRep();
	void Init(char* aTexturePath);
	void Render(const CU::Vector2f& aPosition);
	void CenterHotspot();


private:
	HTEXTURE myTexture;
	hgeSprite* mySprite;
	CU::Vector2f myTextureSize;
	char* myPath;
};
