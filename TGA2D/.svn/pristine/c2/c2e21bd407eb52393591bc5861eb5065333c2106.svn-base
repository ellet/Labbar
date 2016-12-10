#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/sprite/sprite.h>

CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;
}


void CGameWorld::Init()
{
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga2d.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });

}



void CGameWorld::Update(float /*aTimeDelta*/)
{ 
	myTga2dLogoSprite->Render();
}
