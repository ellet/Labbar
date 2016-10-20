#include "stdafx.h"
#include "RenderCommand.h"
#include "..\hgelibs\include\hgesprite.h"
#include "..\hgelibs\include\hgefont.h"


RenderCommand::RenderCommand()
{

}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::Render()
{
	mySprite->Render(myPosition.myX, myPosition.myY);
}

void StretchedRenderCommand::Render()
{
	mySprite->RenderStretch(myPosition.myX, myPosition.myY, myOtherPosition.myX, myOtherPosition.myY);
}

void TextRenderCommand::Render()
{
	myFont->Render(myPosition.myX, myPosition.myY, myAlignbullshit, myText.c_str());
}
