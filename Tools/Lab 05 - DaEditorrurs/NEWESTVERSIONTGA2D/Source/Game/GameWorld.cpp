#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include <tga2d/text/text.h>
#include <tga2d/drawers/debug_drawer.h>

#include <CU/Camera/Camera2D.h>

#include <Message/SetMainCameraMessage.h>
#include <Rend/RenderConverter.h>

using namespace DX2D;
CGameWorld::CGameWorld()
{
	myCamera = new Camera2D();
}


CGameWorld::~CGameWorld()
{
	SAFE_DELETE(myCamera);
}


void CGameWorld::Init()
{
	myCamera->Init(CU::Vector2f(800.f, 800.f), CU::Vector2f::Zero);
	SendAPostMessage(SetMainCameraMessage(RecieverTypes::eCamera, *myCamera));
	//SingletonPostMaster::PostMessage(SetMainCameraMessage(RecieverTypes::eCamera, *myCamera));

	mySprite.Init("Sprites/palm.dds");
}



void CGameWorld::Update(float /*aTimeDelta*/)
{
	DRAWISOMETRICLINE(CU::Vector2f(0.f, 0.f), CU::Vector2f(5.f, 5.f));
	DRAWISOMETRICLINE(CU::Vector2f(0.f, 0.f), CU::Vector2f(5.f, 5.f));

	CU::Vector2f tempPosition = IsometricInput::GetMouseWindowPositionIsometric();
	DRAWISOMETRICLINE(CU::Vector2f(0.f, 0.f), IsometricInput::GetMouseWindowPositionIsometric());
}

void CGameWorld::Draw()
{
	mySprite.Draw(CU::Vector2f(-4.f, 2.f));
}