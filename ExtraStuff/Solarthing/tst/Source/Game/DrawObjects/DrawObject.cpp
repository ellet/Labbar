#include "stdafx.h"
#include "DrawObject.h"


DrawObject::DrawObject()
{
}


DrawObject::~DrawObject()
{
}

void DrawObject::Init(const std::string & aFilePath)
{
	mySprite.Init(aFilePath);
	mySprite.SetPivot({ 0.5f, 0.5f });
	myPosition = { 300.f, 300.f };
}

void DrawObject::Draw() const
{
	mySprite.Draw(myPosition);
}

void DrawObject::SetSize(const float aSize)
{
	mySprite.SetSize(aSize);
}

void DrawObject::SetPosition(const PixelPositionFloat & aPosition)
{
	myPosition = aPosition;
}

void DrawObject::Update(const CU::Time & aDeltaTime)
{

}
