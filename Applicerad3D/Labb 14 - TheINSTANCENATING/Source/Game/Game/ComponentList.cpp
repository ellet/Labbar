#include "stdafx.h"
#include "ComponentList.h"
#include "Game/Player/PlayerControllerComponent.h"
#include "Game/Player/PlayerShootComponent.h"
#include "Game/Component/Shooting/Weapons/WeaponComponent.h"
#include "game/Component/Shooting/Projectiles/ShotComponent.h"
#include "game/Component/Shooting/Projectiles/HomingShotComponent.h"
#include "Game/Component/Enemy/ExplosionComponent.h"
#include "Game/Component/Health/HealthComponent.h"
#include "Game/Component/Enemy/EnemyComponent.h"
#include "Game/Player/PlayerComponent.h"
#include "Game\Objective\ObjectiveComponent.h"
#include "Game\Objective\ObjectiveHandlerComponent.h"
#include <Engine/ComponentList.h>
#include "Game\Component\Controller\AI\AIInterceptorComponent.h"
#include "Component/Controller/AI/AISwarmerComponent.h"
#include "Component/Controller/AI/Mothership/AIMothershipComponent.h"
#include "Game/Component/Enemy/EnemyMineComponent.h"
#include "Game/Component/Controller/AI/AITurretComponent.h"
#include "Game/Component/Controller/AI/Mothership/AIMothershipTurretComponent.h"

SB::ComponentRegistration playerControllerRegistration("PlayerControllerComponent", &SB::DefaultComponentCreator<PlayerControllerComponent>);
SB::ComponentRegistration playerShootRegistration("PlayerShootComponent", &SB::DefaultComponentCreator<PlayerShootComponent>);
SB::ComponentRegistration weaponRegistration("WeaponComponent", &SB::DefaultComponentCreator<WeaponComponent>);
SB::ComponentRegistration shotRegistration("ShotComponent", &SB::DefaultComponentCreator<ShotComponent>);
SB::ComponentRegistration homingShotRegistration("HomingShotComponent", &SB::DefaultComponentCreator<HomingShotComponent>);
SB::ComponentRegistration enemyRegistration("EnemyComponent", &SB::DefaultComponentCreator<EnemyComponent>);
SB::ComponentRegistration healthRegistration("HealthComponent", &SB::DefaultComponentCreator<HealthComponent>);
SB::ComponentRegistration objectiveRegistration("ObjectiveComponent", &SB::DefaultComponentCreator<ObjectiveComponent>);
SB::ComponentRegistration aIInterceptorRegistration("AIInterceptorComponent", &SB::DefaultComponentCreator<AIInterceptorComponent>);
SB::ComponentRegistration aISwarmerRegistration("AISwarmerComponent", &SB::DefaultComponentCreator<AISwarmerComponent>);
SB::ComponentRegistration aIMothershipRegistration("AIMothershipComponent", &SB::DefaultComponentCreator<AIMothershipComponent>);
SB::ComponentRegistration aITurretRegistration("AITurretComponent", &SB::DefaultComponentCreator<AITurretComponent>);
SB::ComponentRegistration aIMothershipTurretRegistration("AIMothershipTurretComponent", &SB::DefaultComponentCreator<AIMothershipTurretComponent>);
SB::ComponentRegistration objectiveHandlerRegistration("ObjectiveHandlerComponent", &SB::DefaultComponentCreator<ObjectiveHandlerComponent>);
SB::ComponentRegistration playerRegistration("PlayerComponent", &SB::DefaultComponentCreator<PlayerComponent>);
SB::ComponentRegistration enemyMineRegistration("EnemyMineComponent", &SB::DefaultComponentCreator<EnemyMineComponent>);
SB::ComponentRegistration explosionRegistration("ExplosionComponent", &SB::DefaultComponentCreator<ExplosionComponent>);

__declspec(noinline) void RegisterGameComponents()
{
	SB::RegisterEngineComponents();
}
