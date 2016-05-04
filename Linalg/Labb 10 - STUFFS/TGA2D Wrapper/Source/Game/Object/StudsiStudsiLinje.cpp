#include "stdafx.h"
#include "StudsiStudsiLinje.h"

#include <tga2d/engine.h>
#include <Utility/TGA2DConversions.h>

#include <RendererManager/RenderManager.h>
#include <CollisionManager/CollisionManager.h>
#include <CollisionManager/CollisionShapes/LineShape.h>


StudsiStudsiLinje::StudsiStudsiLinje()
{
}


StudsiStudsiLinje::StudsiStudsiLinje(Vector2f aStartPos, Vector2f anEndPos)
{
	Init(aStartPos, anEndPos);
}

StudsiStudsiLinje::~StudsiStudsiLinje()
{
}

void StudsiStudsiLinje::Init(Vector2f aStartPos, Vector2f anEndPos)
{
	myLine.myStartPos = aStartPos;
	myLine.myEndPos = anEndPos;

	myRenderCommand = RenderCommandLine(myLine.myStartPos, myLine.myEndPos, Vector4f::One);

	myCollisionData.myObject = nullptr;
	myCollisionData.myCollisionShape = new LineShape(myLine.myStartPos, myLine.myEndPos);
}

void StudsiStudsiLinje::Update(const float aDeltaTime)
{
	(aDeltaTime);
	CollisionManager::AddWorldCollisionData(myCollisionData);
}

void StudsiStudsiLinje::Draw() const
{
	RenderManager::AddRenderCommandLine(myRenderCommand);
}
