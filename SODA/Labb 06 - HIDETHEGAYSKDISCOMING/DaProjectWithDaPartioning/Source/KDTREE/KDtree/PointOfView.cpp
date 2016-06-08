#include "stdafx.h"
#include "PointOfView.h"
#include <Rend/RenderConverter.h>

PointOfView::PointOfView()
{
	myPosition = CU::Vector2f::Zero;
	myPositionEnd = CU::Vector2f::Zero;
	myBPosition = CU::Vector2f::Zero;
	myCPosition = CU::Vector2f::Zero;
}

PointOfView::~PointOfView()
{

}

void PointOfView::Init()
{

}

void PointOfView::Update(const CU::Time & aDeltaTime)
{

}

void PointOfView::Draw() const
{
	DRAWLINE(myPosition, myBPosition);
	DRAWLINE(myPosition, myCPosition);
	DRAWLINE(myCPosition, myBPosition);
}

void PointOfView::SetPointOfView(const CU::Vector2f & aPosition, const CU::Vector2f & aEndPosition)
{
	myPosition = aPosition;
	
	CU::Vector2f tempLine = aEndPosition - myPosition;
	CU::Vector2f tempLineNormal(-tempLine.y, tempLine.x);
	tempLine.Normalize();
	
	myBPosition = aEndPosition + tempLineNormal * tempLine.Length();
	myCPosition = aEndPosition - tempLineNormal * tempLine.Length();
	myFOV.Init(myPosition, myBPosition, myCPosition);

	myCircle = Intersection2D::Circle2D(aPosition, (myBPosition - aPosition).Length());
}

const CU::Vector2f & PointOfView::GetPosition() const
{
	return myPosition;
}

const Intersection2D::Triangle & PointOfView::GetTriangle() const
{
	return myFOV;
}

const Intersection2D::Circle2D & PointOfView::GetCircle() const
{
	return myCircle;
}
