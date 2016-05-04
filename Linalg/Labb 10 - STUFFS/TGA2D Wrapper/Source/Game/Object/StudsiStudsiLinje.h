#pragma once
#include <Intersection/Shapes2D/LineSegment2D.h>
#include <RendererManager/Commands/Lines/RenderCommandLine.h>
#include <CollisionManager/CollisionData/CollisionData.h>

class StudsiStudsiLinje
{
public:
	StudsiStudsiLinje();
	StudsiStudsiLinje(Vector2f aStartPos, Vector2f anEndPos);
	~StudsiStudsiLinje();

	void Init(Vector2f aStartPos, Vector2f anEndPos);

	void Update(const float aDeltaTime);

	void Draw() const;

private:
	Intersection2D::LineSegment2D myLine;
	RenderCommandLine myRenderCommand;

	CollisionData myCollisionData;
};

