#include "stdafx.h"
#include "Border.h"
#include "../TGA2DWrapper/RendererManager/RenderManager.h"


Border::Border(Vector2f aNode1, Vector2f aNode2)
{
	myNode1 = aNode1;
	myNode2 = aNode2;
	myColour = Vector4f(1, 1, 1, 1);
}

Border::Border()
{

}

void Border::SetColour(Vector4f aColour)
{
	myColour = aColour;
}

void Border::MoveLine(Vector2f /*aNewPosition*/)
{

}

void Border::Render() const
{
	RenderManager::AddRenderCommandLine(RenderCommandLine(myNode1, myNode2, myColour));
}

void Border::DragNode1(Vector2f aNewPosition)
{
	myNode1 = aNewPosition;
}
void Border::DragNode2(Vector2f aNewPosition)
{
	myNode2 = aNewPosition;
}
float Border::GetLength(void)
{
	return sqrt((myNode2.x - myNode1.x)*(myNode2.x - myNode1.x) + (myNode2.y - myNode1.y)*(myNode2.y - myNode1.y));
}

const Vector2f &Border::GetNode1() const
{
	return myNode1;
}
const Vector2f &Border::GetNode2() const
{
	return myNode2;
}

Border::~Border()
{
}
