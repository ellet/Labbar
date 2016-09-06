#include "stdafx.h"
#include "primitives/line_primitive.h"
#include "engine.h"
#include "render/Renderer.h"

using namespace Tga2D;

LinePrimitive::LinePrimitive(void)
{
}


LinePrimitive::~LinePrimitive(void)
{
}

void Tga2D::LinePrimitive::Render()
{
	CEngine::GetInstance()->GetRenderer().AddToRender(this);
}

void Tga2D::CLineMultiPrimitive::Render()
{
	CEngine::GetInstance()->GetRenderer().AddToRender(this);
}

void Tga2D::CLineMultiPrimitive::Draw(CDirectEngine* aRenderer)
{
	aRenderer->DoDraw(this);
}
