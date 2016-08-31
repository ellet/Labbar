#include "stdafx.h"
#include "PointOfView.h"

const float GlobalFarPlaneDistance = 130.f;
const float GlobalNearPlaneDistance = 30.f;

PointOfView::PointOfView()
	:myFrustum(CU::Vector3f(400.f, 400.f, 400.f), GlobalNearPlaneDistance, GlobalFarPlaneDistance, CU::Vector3f::Zero)
{
	mySprite = new StaticSprite();
	myRotation = CU::Vector3f(0.f, 0.f, 0.f);
	myPosition = CU::Vector3f(400.f, 400.f, 400.f);
}


PointOfView::~PointOfView()
{
}

void PointOfView::Init()
{
	mySprite->Init("Sprites/Muuuu.png", CU::Vector2f(0.f, 0.5f));
	mySprite->SetLayer(enumRenderLayer::ePoint);
}

void PointOfView::Update(const CU::Time & aDeltaTime)
{
	myFrustum = Intersection3D::Fov90Frustum(myPosition, GlobalNearPlaneDistance, GlobalFarPlaneDistance, myRotation);
}

void PointOfView::Draw() const
{
	DrawFrustum();
}

const CU::Vector2f & PointOfView::GetPosition() const
{
	return CU::Vector2f::Zero;
}


void PointOfView::SetPosition(const CU::Vector2f & aPosition)
{
	//myCircle.ChangePosition(aPosition);
	myPosition = aPosition;
}

void PointOfView::SetRotation(const CU::Vector3f & aRotation)
{
	myRotation += aRotation;
}

const CU::Vector3f & PointOfView::GetRotation() const
{
	return myRotation;
}

void PointOfView::DrawFrustum() const
{
	CU::Vector3f nearTopLeft = myFrustum.GetNearTopLeft();// +myPosition;
	CU::Vector3f nearTopRight = myFrustum.GetNearTopRight();// +myPosition;
	CU::Vector3f nearDownLeft = myFrustum.GetNearDownLeft();// +myPosition;
	CU::Vector3f nearDownRight = myFrustum.GetNearDownRight();// +myPosition;
	CU::Vector3f farTopLeft = myFrustum.GetFarTopLeft();// + myPosition;
	CU::Vector3f farTopRight = myFrustum.GetFarTopRight();// + myPosition;
	CU::Vector3f farDownLeft = myFrustum.GetFarDownLeft();// + myPosition;
	CU::Vector3f farDownRight = myFrustum.GetFarDownRight();// + myPosition;


	CU::Vector2f nearTopLeftCornerProjection = CU::Vector2f(nearTopLeft.x, nearTopLeft.y);
	CU::Vector2f nearTopRightCornerProjection = CU::Vector2f(nearTopRight.x, nearTopRight.y);
	CU::Vector2f nearDownLeftCornerProjection = CU::Vector2f(nearDownLeft.x, nearDownLeft.y);
	CU::Vector2f nearDownRightCornerProjection = CU::Vector2f(nearDownRight.x, nearDownRight.y);
	CU::Vector2f farTopLeftCornerProjection = CU::Vector2f(farTopLeft.x, farTopLeft.y);
	CU::Vector2f farTopRightCornerProjection = CU::Vector2f(farTopRight.x, farTopRight.y);
	CU::Vector2f farDownLeftCornerProjection = CU::Vector2f(farDownLeft.x, farDownLeft.y);
	CU::Vector2f farDownRightCornerProjection = CU::Vector2f(farDownRight.x, farDownRight.y);


	//near top line
	RenderConverter::DrawLine(nearTopLeftCornerProjection, nearTopRightCornerProjection);
	//near right line
	RenderConverter::DrawLine(nearTopRightCornerProjection, nearDownRightCornerProjection);
	//near down line
	RenderConverter::DrawLine(nearDownRightCornerProjection, nearDownLeftCornerProjection);
	//near left line
	RenderConverter::DrawLine(nearTopLeftCornerProjection, nearDownLeftCornerProjection);

	//far top line
	RenderConverter::DrawLine(farTopLeftCornerProjection, farTopRightCornerProjection);
	//far right line
	RenderConverter::DrawLine(farTopRightCornerProjection, farDownRightCornerProjection);
	//far down line
	RenderConverter::DrawLine(farDownRightCornerProjection, farDownLeftCornerProjection);
	//far left line
	RenderConverter::DrawLine(farTopLeftCornerProjection, farDownLeftCornerProjection);


	//diagonal top line
	RenderConverter::DrawLine(farTopLeftCornerProjection, nearTopLeftCornerProjection);
	//diagonal right line
	RenderConverter::DrawLine(farTopRightCornerProjection, nearTopRightCornerProjection);
	//diagonal down line
	RenderConverter::DrawLine(farDownRightCornerProjection, nearDownRightCornerProjection);
	//diagonal left line
	RenderConverter::DrawLine(farDownLeftCornerProjection, nearDownLeftCornerProjection);
}

