#include "TextRenderCommand.h"

#include <tga2d/engine.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>

#include "TextFont.h"

TextRenderCommand::TextRenderCommand()
	: mySize(0.f), myFont(nullptr)
{
}
TextRenderCommand::~TextRenderCommand()
{
}

void TextRenderCommand::Render(const Vector2f &aParentPosition, const Vector2f &aParentSize)
{

	std::shared_ptr<DX2D::CSpriteBatch> batch = myFont->GetSpriteBatch();

	batch->ClearAll();
	myFont->ResetUsedSprites();

	const DX2D::Vector2ui virtualScreenSize = DX2D::CEngine::GetInstance()->GetWindowSize();
	Vector2f position = Vector2f((myPosition.x / virtualScreenSize.x) * aParentSize.x + aParentPosition.x, (myPosition.y / virtualScreenSize.y) * aParentSize.y + aParentPosition.y);

	const DX2D::Vector2f size(mySize * myFont->GetNormalCharacterWidth() * aParentSize.x, mySize * myFont->GetNormalCharacterHeight() * aParentSize.y);
	const float xOffset = mySize * (myFont->GetCharacterWidth() / static_cast<float>(virtualScreenSize.x)) * aParentSize.x;

	for (unsigned short i = 0; i < myText.size(); ++i)
	{

		DX2D::CSprite *sprite = myFont->GetFreeSpriteSheet();
		sprite->SetPosition(DX2D::Vector2f(position.x + i * xOffset, position.y));
		sprite->SetSize(size);

		Vector4f rectangle = myFont->GetCharacterLocation(myText[i]);
		sprite->SetTextureRect(rectangle.x, rectangle.y, rectangle.z, rectangle.w);

		batch->AddObject(sprite);

	}

	batch->Render();

}
