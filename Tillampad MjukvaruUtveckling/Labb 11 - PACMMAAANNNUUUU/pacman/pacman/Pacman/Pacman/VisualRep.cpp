#include "VisualRep.h"

#include "HgeSingelton.h"

VisualRep::VisualRep()
{
}

VisualRep::~VisualRep()
{
	delete mySprite;
	mySprite = NULL;
}

void VisualRep::Init(char* aTexturePath)
{
	myTexture = HGES->Texture_Load(aTexturePath);


	myTextureSize.myY = static_cast<float>(HGES->Texture_GetHeight(myTexture));
	myTextureSize.myX = static_cast<float>(HGES->Texture_GetWidth(myTexture));

	mySprite = new hgeSprite(myTexture,0,0,myTextureSize.myX, myTextureSize.myY);
}

void VisualRep::Render(const CU::Vector2f& aPosition)
{
	mySprite->Render(aPosition.x,aPosition.y);
}

void VisualRep::CenterHotspot()
{
	mySprite->SetHotSpot(myTextureSize.x/2,myTextureSize.y/2);
}