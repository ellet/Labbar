#include "stdafx.h"
#include "GameWorld.h"
#include "Controllers\PlayerController.h"
#include "Controllers\TeamBasedGameController.h"

CGameWorld::CGameWorld()
{
	
}


CGameWorld::~CGameWorld()
{
	
}


void CGameWorld::Init()
{
	mySprites.Resize(10);

	for (unsigned short iSprite = 0; iSprite < mySprites.Size(); ++iSprite)
	{
		mySprites[iSprite].Init("Sprites/daFace.dds");
		mySprites[iSprite].SetPosition({ 100.f + iSprite * 100.f, 100.f });
	}
}



void CGameWorld::Update(float aDeltaTime)
{
	
}

void CGameWorld::Render() const
{
	for (unsigned short iSprite = 0; iSprite < mySprites.Size(); ++iSprite)
	{
		mySprites[iSprite].Render();
	}
}
