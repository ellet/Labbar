#pragma once
#include <Engine\Scripting\LuaComponent.h>
#include "Game\Scripting\GameLuaSubscription.h"

class GameLuaSubscription;

class GameLuaComponent :
	public SB::LuaComponent
{
public:
	GameLuaComponent();
	~GameLuaComponent();


	virtual void Initialize() override;

private:
	std::unique_ptr<GameLuaSubscription>mySubscription;
};