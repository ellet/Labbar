#include "stdafx.h"
#include "TextScene.h"
#
TextScene::TextScene()
{
	myText = "aelo!";
	myText.SetPositionBottomLeft(SB::Vector2f(300.f, 300.f));

	myText2 = "Hi again!";

	float text2YPos = myText.GetBoundaries().w;
	myText2.SetPositionBottomLeft(SB::Vector2f(300.f, text2YPos));
}


TextScene::~TextScene()
{
}

void TextScene::Update(const SB::Time & aDeltaTime)
{
}

void TextScene::Render()
{
	myText.Render();
	myText2.Render();
}
