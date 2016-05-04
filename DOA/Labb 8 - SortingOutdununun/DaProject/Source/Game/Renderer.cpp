#include "stdafx.h"
#include "Renderer.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	myStaples = new DX2D::CSpriteBatch(false);

	myStaples->Init("Sprites/square.dds");
}

void Renderer::AddSprite(DX2D::CSprite & aSpriteToAdd)
{
	myStaples->AddObject(&aSpriteToAdd);
}

void Renderer::Render()
{
	myStaples->Render();
}