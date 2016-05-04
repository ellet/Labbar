#include "stdafx.h"
#include "Renderer.h"

#include <vector>
#include <tga2d/Engine.h>

#include <tga2d/math/vector2.h>
#include <tga2d/math/vector4.h>
#include <tga2d/math/matrix44.h>
#include <tga2d/math/color.h>
#include <tga2d/shaders/shader.h>

#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/line_drawer.h>
#include <tga2d/sprite/sprite.h>



Renderer::Renderer()
{
	//myNodesToDraw = new DX2D::CSpriteBatch(false);
	//myNodesToDraw->Init("Sprites/nodesprite.dds");
	
	//myLinksToDraw.Init(300);
}


Renderer::~Renderer()
{
}
//
//void Renderer::AddNodeToDraw(DX2D::CSprite & aSpriteToAdd)
//{
//	//myNodesToDraw->AddObject(&aSpriteToAdd);
//}
//
////void Renderer::AddLinkToDraw(const LineData & aLinkToDraw)
//{
//	//myLinksToDraw.Add(aLinkToDraw);
//}
//
//void Renderer::Draw()
//{
//	RenderLines();
//	//myNodesToDraw->Render();
//}
//
//void Renderer::RenderLines()
//{
//	//for (unsigned short iLine = 0; iLine < myLinksToDraw.Size(); ++iLine)
//	{
//		//RenderLine(myLinksToDraw[iLine]);
//	}
//}
//
////void Renderer::RenderLine(const LineData & aLineToDraw)
//{
//	//DX2D::Vector2f startPosition(aLineToDraw.myStartPosition.x, aLineToDraw.myStartPosition.y);
//	//DX2D::Vector2f endPosition(aLineToDraw.myEndPosition.x, aLineToDraw.myEndPosition.y);
//
//	//DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(startPosition, endPosition);
//}
