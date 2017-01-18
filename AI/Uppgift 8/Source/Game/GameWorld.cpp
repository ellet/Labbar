#include "stdafx.h"
#include "GameWorld.h"
#include "Controllers\PlayerController.h"
#include "Controllers\TeamBasedGameController.h"

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
	myEvilDudes.InitBase("Sprites/evilBase.dds", {100.f, 100.f});
	myEvilDudes.SetUnitSprite("Sprites/daFace.dds");
	myEvilDudes.SetUnitsTarget({ 500.f, 500.f });
}



void CGameWorld::Update(float aDeltaTime)
{
	if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eLeft) == true)
	{
		myEvilDudes.SetUnitsTarget(myInput.GetMousePosition());
	}

	myEvilDudes.Update(aDeltaTime);
}

void CGameWorld::Render() const
{
	myEvilDudes.Render();
}
