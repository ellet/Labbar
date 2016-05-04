#include "stdafx.h"
#include "DialogRenderer.h"

#include <tga2d/sprite/sprite.h>

#include <RendererManager/RenderManager.h>
#include <RendererManager\Text\TextRenderer.h>

#include "Dialog.h"

DialogRenderer::DialogRenderer()
	:myTextRenderer(new TextRenderer()), myBackgroundSprite(nullptr), myFontSize(1.f)
{
}
DialogRenderer::~DialogRenderer()
{
	delete myBackgroundSprite;
	myBackgroundSprite = nullptr;
	delete myTextRenderer;
	myTextRenderer = nullptr;
}

size_t DialogRenderer::NextDialogIndex(const Dialog &aDialog, const size_t aStartIndex)
{

	size_t currentIndex = aStartIndex;

	for (size_t i = 0; i < myMaxDialogRows; ++i)
	{
		currentIndex = myTextRenderer->GetNextLine(aDialog.GetText(), myFontSize, myTextSize.x, currentIndex);
	}

	return currentIndex;

}

void DialogRenderer::LoadFont(const std::string &aFontPath)
{

	myTextRenderer->LoadFont(aFontPath);

	myMaxDialogRows = static_cast<unsigned short>(myTextSize.y / myTextRenderer->TextHeight(myFontSize));

}
void DialogRenderer::DrawDialog(const Dialog &aDialog, const size_t aStartIndex) const
{

	if (myBackgroundSprite != nullptr)
	{
		RenderManager::AddRenderCommand(RenderCommand(myBackgroundSprite, myPosition, Vector2f::One, Vector2f::Zero, 0.f, Vector4f::One, Vector4f(0.f, 0.f, 1.f, 1.f)));
	}

	myTextRenderer->Draw(aDialog.GetText(), myTextPosition, myFontSize, Vector4f::One, myTextSize.x, myTextSize.y, aStartIndex);

	DX2D::CSprite *aAvatar = aDialog.GetCharacterSprite();

	if (aAvatar != nullptr)
	{
		RenderManager::AddRenderCommand(RenderCommand(aAvatar, myAvatarPosition, Vector2f::One, Vector2f::Zero, 0.f, Vector4f::One, Vector4f(0.f, 0.f, 1.f, 1.f)));
	}

}

void DialogRenderer::LoadBackground(const std::string &aSpritePath)
{
	myBackgroundSprite = new DX2D::CSprite(aSpritePath.c_str());
}
