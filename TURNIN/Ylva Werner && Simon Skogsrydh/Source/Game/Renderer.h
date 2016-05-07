#pragma once

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
}

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();

	void AddSprite(DX2D::CSprite & aSpriteToAdd);

	void Render();

private:
	DX2D::CSpriteBatch * myStaples;
};

