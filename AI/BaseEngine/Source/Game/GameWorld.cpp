#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include "Rendering/BDRenderer.h"

CGameWorld::CGameWorld()
{
	BDRenderer::Create();
}


CGameWorld::~CGameWorld()
{
	BDRenderer::Destroy();
}


void CGameWorld::Init()
{
	myInputListener.SetAsListener();
	//mySprite = new DX2D::CSprite("sprites/tga_logo.dds");
	mySprite = std::make_unique<BDSprite>();
	mySprite->Init("sprites/tga_logo.dds");
	mySprite->SetPosition(SB::Vector2f(100.f, 250.f));
}



void CGameWorld::Update(float /*aTimeDelta*/)
{ 
	//mySprite->Render();
	mySprite->Render();

	//DX2D::CColor color = mySprite->GetPixelColor(7, 7);
	//CEngine::GetInstance()->GetLightManager().SetAmbience(1.0f);
}
