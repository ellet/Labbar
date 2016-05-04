#include "BoxShape.h"
#include "PointShape.h"
//#include <tga2d/drawers/debug_drawer.h>
//#include <tga2d/engine.h>
//#include "../../Utility/TGA2DConversions.h"
#include "../../RendererManager/Commands/Lines/RenderCommandLine.h"
#include "../../RendererManager/RenderManager.h"

BoxShape::BoxShape()
{
}


BoxShape &BoxShape::operator=(BoxShape &aOtherBox)
{
	myCollisionBox = Intersection2D::AABB2D(aOtherBox.myCollisionBox.myMainPoint, aOtherBox.myCollisionBox.myExtents);
	return *this;
}

BoxShape::~BoxShape()
{
}

BoxShape::BoxShape(const Vector2f aCenterPosition, const Vector2f aExtents)
{
	myCollisionBox = Intersection2D::AABB2D(aCenterPosition, aExtents);
}



bool BoxShape::CheckCollision(const BaseCollisionShape & aCollisionShape) const
{
	return aCollisionShape.CheckShapeVsBox((*this));
}

bool BoxShape::CheckShapeVsBox(const BoxShape & aCollisionShape) const
{
	if (Intersection2D::AABBVsAABB2D(myCollisionBox, aCollisionShape.myCollisionBox) == true)
	{
		return true;
	}

	return false;
}

bool BoxShape::CheckShapeVsPoint(const PointShape & aPointShape) const
{
	if (Intersection2D::PointInsideAABB2D(myCollisionBox, aPointShape.GetMyPoint()) == true)
	{
		return true;
	}

	return false;
}

void BoxShape::ChangePosition(const Vector2f aPosition)
{
	myCollisionBox.ChangePosition(aPosition);
}

void BoxShape::DrawCollisionBox() const
{
	Vector2f lineStart = myCollisionBox.myMaxPos;
	Vector2f lineEnd = myCollisionBox.myMaxPos;
	lineStart.x = myCollisionBox.myMinPos.x;

	RenderManager::AddRenderCommandLine(RenderCommandLine(lineStart, lineEnd, Vector4f::One));
	//DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(DX2D::Vector2f() << lineStart, DX2D::Vector2f() << lineEnd);

	lineStart = lineEnd;
	lineEnd.y = myCollisionBox.myMinPos.y;

	RenderManager::AddRenderCommandLine(RenderCommandLine(lineStart, lineEnd, Vector4f::One));
	//DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(DX2D::Vector2f() << lineStart, DX2D::Vector2f() << lineEnd);

	lineStart = lineEnd;
	lineEnd.x = myCollisionBox.myMinPos.x;

	RenderManager::AddRenderCommandLine(RenderCommandLine(lineStart, lineEnd, Vector4f::One));
	//DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(DX2D::Vector2f() << lineStart, DX2D::Vector2f() << lineEnd);

	lineStart = lineEnd;
	lineEnd.y = myCollisionBox.myMaxPos.y;

	RenderManager::AddRenderCommandLine(RenderCommandLine(lineStart, lineEnd, Vector4f::One));
	//DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(DX2D::Vector2f() << lineStart, DX2D::Vector2f() << lineEnd);
}
