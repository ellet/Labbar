#include "stdafx.h"
#include "Renderer.h"

#include <tga2d/Engine.h>
#include <tga2d/sprite/sprite_batch.h>


#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>

#include "WrappedSprite.h"

Renderer::Renderer()
{
	
	//mySpritesToDraw.Init(100);
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	myNodesToDraw = new DX2D::CSpriteBatch(true);
	myNodesToDraw->Init("Sprites/hestfan.png");

	myLinksToDraw.Init(300);
}

void Renderer::AddNodeToDraw(WrappedSprite & aSpriteToAdd)
{
	DX2D::CSprite & tempSprite( *aSpriteToAdd.GetSprite());

	Vector2f tempPosition = aSpriteToAdd.GetPosition();

	tempPosition.x /= static_cast<float>(myWindowSize.x);
	tempPosition.y /= static_cast<float>(myWindowSize.y);

	DX2D::Vector2f drawPosition(tempPosition.x, tempPosition.y);

	tempSprite.SetPosition(drawPosition);

	myNodesToDraw->AddObject(&tempSprite);
}

void Renderer::Draw()
{
	RenderLines();

	myNodesToDraw->Render();
}


void Renderer::ResetRender()
{
	myLinksToDraw.RemoveAll();
	myNodesToDraw->DeleteAll();
	myNodesToDraw->ClearAll();
}

void Renderer::AddLinkToDraw(const LineData & aLinkToDraw)
{
	myLinksToDraw.Add(aLinkToDraw);
}

void Renderer::RenderLines()
{
	for (unsigned short iLine = 0; iLine < myLinksToDraw.Size(); ++iLine)
	{
		RenderLine(myLinksToDraw[iLine]);
	}
	myLinksToDraw.RemoveAll();
}

void Renderer::RenderLine(const LineData & aLineToDraw)
{
	Vector2f startPos = aLineToDraw.myStartPosition;
	Vector2f endPos = aLineToDraw.myEndPosition;

	startPos.x /= static_cast<float>(myWindowSize.x);
	startPos.y /= static_cast<float>(myWindowSize.y);

	endPos.x /= static_cast<float>(myWindowSize.x);
	endPos.y /= static_cast<float>(myWindowSize.y);

	DX2D::Vector2f startPosition(startPos.x, startPos.y);
	DX2D::Vector2f endPosition(endPos.x, endPos.y);
	DX2D::Vector4f color(aLineToDraw.myColor.r, aLineToDraw.myColor.g, aLineToDraw.myColor.b, aLineToDraw.myColor.a);

	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(startPosition, endPosition, color);
}
