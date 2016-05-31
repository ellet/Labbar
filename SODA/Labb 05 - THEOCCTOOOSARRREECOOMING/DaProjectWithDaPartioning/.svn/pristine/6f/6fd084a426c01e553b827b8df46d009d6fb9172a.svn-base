#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>

using namespace DX2D;
CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
}


void CGameWorld::Init()
{
	mySprite = new DX2D::CSprite("sprites/tga_logo.dds");
}



void CGameWorld::Update(float /*aTimeDelta*/)
{ 
	mySprite->Render();

	DX2D::CColor color = mySprite->GetPixelColor(7, 7);
	CEngine::GetInstance()->GetLightManager().SetAmbience(1.0f);
}
