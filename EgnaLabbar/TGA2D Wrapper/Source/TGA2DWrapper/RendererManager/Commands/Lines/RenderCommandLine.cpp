#include "RenderCommandLine.h"

#include <tga2d\engine.h>
#include <tga2d\drawers\debug_drawer.h>

#include "..\..\..\Utility\TGA2DConversions.h"

RenderCommandLine::RenderCommandLine()
{
}
RenderCommandLine::RenderCommandLine(const Vector2f &aStartPosition, const Vector2f &anEndPosition, const Vector4f aColors)
	:myStartPosition(aStartPosition), myEndPosition(anEndPosition), myColors(aColors)
{
}
RenderCommandLine::~RenderCommandLine()
{
}

void RenderCommandLine::Render(const Vector2f &aParentPosition, const Vector2f &aParentSize)
{

	const DX2D::Vector2ui virtualScreenSize = DX2D::CEngine::GetInstance()->GetWindowSize();

	DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(
		DX2D::Vector2f((myStartPosition.x / virtualScreenSize.x) * aParentSize.x + aParentPosition.x, (myStartPosition.y / virtualScreenSize.y) * aParentSize.y + aParentPosition.y),
		DX2D::Vector2f((myEndPosition.x / virtualScreenSize.x) * aParentSize.x + aParentPosition.x, (myEndPosition.y / virtualScreenSize.y) * aParentSize.y + aParentPosition.y),
		DX2D::Vector4f(myColors.r, myColors.g, myColors.b, myColors.a)
		);

}
