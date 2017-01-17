#include "stdafx.h"
#include "ComponentList.h"
#include "Game\Objective\ObjectiveComponent.h"
#include "Game\Objective\ObjectiveHandlerComponent.h"
#include <Engine/ComponentList.h>
#include "Game/Scripting/GameLuaComponent.h"
#include "Game/Waves/WaveManagerComponent.h"
#include "Game/Waves/SpawnPointComponent.h"
#include "Game/Player/PlayerComponent.h"
#include "Game/Health/PlayerHealthComponent.h"
#include "Game/Health/EnemyHealthComponent.h"

SB::ComponentRegistration luaRegistration("LuaComponent", &SB::DefaultComponentCreator<GameLuaComponent>);
SB::ComponentRegistration objectiveRegistration("ObjectiveComponent", &SB::DefaultComponentCreator<SB::ObjectiveComponent>);
SB::ComponentRegistration objectiveHandlerRegistration("ObjectiveHandlerComponent", &SB::DefaultComponentCreator<SB::ObjectiveHandlerComponent>);
SB::ComponentRegistration waveManagerRegistration("WaveManagerComponent", &SB::DefaultComponentCreator<WaveManagerComponent>);
SB::ComponentRegistration spawnPointRegistration("SpawnPointComponent", &SB::DefaultComponentCreator<SpawnPointComponent>);
SB::ComponentRegistration playerRegistration("PlayerComponent", &SB::DefaultComponentCreator<PlayerComponent>);
SB::ComponentRegistration playerHealthRegistration("PlayerHealthComponent", &SB::DefaultComponentCreator<PlayerHealthComponent>);
SB::ComponentRegistration enemyHealthRegistration("EnemyHealthComponent", &SB::DefaultComponentCreator<EnemyHealthComponent>);

__declspec(noinline) void RegisterGameComponents()
{
	SB::RegisterEngineComponents();
}
