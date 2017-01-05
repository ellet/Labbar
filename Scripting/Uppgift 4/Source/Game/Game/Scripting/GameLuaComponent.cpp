#include "stdafx.h"
#include "GameLuaComponent.h"
#include "GameLuaSubscription.h"

GameLuaComponent::GameLuaComponent()
{
}


GameLuaComponent::~GameLuaComponent()
{
}

void GameLuaComponent::Initialize()
{
	mySubscription = std::make_unique<GameLuaSubscription>(*this);
	LuaComponent::Initialize();
}
