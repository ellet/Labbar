#include "stdafx.h"
#include "PointOfView.h"


PointOfView::PointOfView()
{
	mySprite = new StaticSprite();
}


PointOfView::~PointOfView()
{
}

void PointOfView::Init()
{
	myCircle.myRadius = 300.f;
	myCircle.ChangePosition(CU::Vector2f(300.f, 300.f));

	mySprite->Init("Sprites/pointofviewCircle.dds");
	mySprite->SetLayer(enumRenderLayer::ePoint);
}

void PointOfView::Update()
{

}

void PointOfView::Draw() const
{
	mySprite->Draw(myCircle.myMainPoint);
}

void PointOfView::SetPosition(const CU::Vector2f & aPosition)
{
	myCircle.ChangePosition(aPosition);
}
