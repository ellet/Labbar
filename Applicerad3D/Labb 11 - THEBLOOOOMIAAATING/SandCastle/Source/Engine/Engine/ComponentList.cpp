#include "stdafx.h"
#include "ComponentList.h"
#include "Scripting/LuaComponent.h"
#include "Component/ModelComponent.h"
#include "Component/Collider/ColliderComponent.h"
#include "Component/CircleMovementComponent.h"
#include "Engine/ParticleSystem/ParticleComponent.h"
#include "Streak/StreakComponent.h"
#include "Physics/PhysicsComponent.h"
#include "Lighting/PointLightComponent.h"

namespace ENGINE_NAMESPACE
{
	class StreakComponent;
	ComponentRegistration luaRegistration("LuaComponent", &SB::DefaultComponentCreator<LuaComponent>);
	ComponentRegistration modelRegistration("ModelComponent", &SB::DefaultComponentCreator<ModelComponent>);
	ComponentRegistration colliderRegistration("ColliderComponent", &SB::DefaultComponentCreator<ColliderComponent>);
	ComponentRegistration circleMovementRegistration("CircleMovementComponent", &SB::DefaultComponentCreator<CircleMovementComponent>);
	ComponentRegistration streakComponentRegistration("StreakComponent", &SB::DefaultComponentCreator<StreakComponent>);
	ComponentRegistration PhysicsComponentRegistration("PhysicsComponent", &SB::DefaultComponentCreator < PhysicsComponent >);
	ComponentRegistration particleRegistration("ParticleComponent", &SB::DefaultComponentCreator<ParticleComponent>);
	ComponentRegistration pointLightComponentRegistration("PointLightComponent", &SB::DefaultComponentCreator<PointLightComponent>);

	__declspec(noinline) void RegisterEngineComponents()
	{
	}
}
