#include "stdafx.h"
#include "PointOfView.h"


PointOfView::PointOfView()
{
	mySprite = new StaticSprite();
	myRotation = 0.f;
}


PointOfView::~PointOfView()
{
}

void PointOfView::Init()
{
	myCircle.myRadius = 300.f;
	myCircle.ChangePosition(CU::Vector2f(300.f, 300.f));

	mySprite->Init("Sprites/Muuuu.png", CU::Vector2f(0.f, 0.5f));
	mySprite->SetLayer(enumRenderLayer::ePoint);

	SetRotation(90.f);
}

void PointOfView::Update()
{

}

void PointOfView::Draw() const
{
	mySprite->Draw(myCircle.myMainPoint);
}

const CU::Vector2f & PointOfView::GetPosition() const
{
	return myCircle.myMainPoint;
}


void PointOfView::SetPosition(const CU::Vector2f & aPosition)
{
	myCircle.ChangePosition(aPosition);
}

void PointOfView::SetRotation(const float aRotation)
{
	mySprite->SetRotation(aRotation);
	myRotation = aRotation;
}

const float PointOfView::GetRotation() const
{
	return myRotation;
}