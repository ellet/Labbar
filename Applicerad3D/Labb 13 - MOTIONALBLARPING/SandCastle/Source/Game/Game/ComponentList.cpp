#include "stdafx.h"
#include "ComponentList.h"
#include "Game/Player/PlayerControllerComponent.h"
#include "Game/Player/PlayerShootComponent.h"
#include "Game/Component/Shooting/WeaponComponent.h"
#include "Game/Component/Health/HealthComponent.h"
#include "Game/Component/Enemy/EnemyComponent.h"
#include "Game/Player/PlayerComponent.h"
#include "Game\Objective\ObjectiveComponent.h"
#include "Game\Objective\ObjectiveHandlerComponent.h"
#include <Engine/ComponentList.h>
#include "Game\Component\Controller\AI\AIInterceptorComponent.h"


SB::ComponentRegistration playerControllerRegistration("PlayerControllerComponent", &SB::DefaultComponentCreator<PlayerControllerComponent>);
SB::ComponentRegistration playerShootRegistration("PlayerShootComponent", &SB::DefaultComponentCreator<PlayerShootComponent>);
SB::ComponentRegistration weaponRegistration("WeaponComponent", &SB::DefaultComponentCreator<WeaponComponent>);
SB::ComponentRegistration enemyRegistration("EnemyComponent", &SB::DefaultComponentCreator<EnemyComponent>);
SB::ComponentRegistration healthRegistration("HealthComponent", &SB::DefaultComponentCreator<HealthComponent>);
SB::ComponentRegistration objectiveRegistration("ObjectiveComponent", &SB::DefaultComponentCreator<ObjectiveComponent>);
SB::ComponentRegistration aIInterceptorRegistration("AIInterceptorComponent", &SB::DefaultComponentCreator<AIInterceptorComponent>);
SB::ComponentRegistration objectiveHandlerRegistration("ObjectiveHandlerComponent", &SB::DefaultComponentCreator<ObjectiveHandlerComponent>);
SB::ComponentRegistration playerRegistration("PlayerComponent", &SB::DefaultComponentCreator<PlayerComponent>);

__declspec(noinline) void RegisterGameComponents()
{
	SB::RegisterEngineComponents();
}
