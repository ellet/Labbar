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
	myEnemyUnit.SetSprite("Sprites/daFace.dds");
	myEnemyUnit.SetPosition({ 100.f, 100.f });
	enemyController = &myEnemyUnit.SetController<TeamBasedGameController>();

	myActor.SetSprite("Sprites/daFace.dds");
	myActor.SetPosition({ 300.f, 300.f });
	myActor.SetController<PlayerController>();
}



void CGameWorld::Update(float aDeltaTime)
{
	if (myInput.GetIfMouseButtonPressed(SB::MouseKey::eLeft) == true)
	{
		enemyController->SetTargetPosition(myInput.GetMousePosition());
	}

	myEnemyUnit.Update(aDeltaTime);
	myActor.Update(aDeltaTime);
}

void CGameWorld::Render() const
{
	myEnemyUnit.Render();
	//myActor.Render();
}
