#include "stdafx.h"
#include "ComponentList.h"
#include "Scripting/LuaComponent.h"
#include "Component/ModelComponent.h"
#include "Component/Collider/ColliderComponent.h"
#include "Component/CircleMovementComponent.h"
#include "Engine/ParticleSystem/ParticleComponent.h"
#include "Streak/StreakComponent.h"
#include "Lighting/PointLightComponent.h"
#include "Marker/MarkerComponent.h"
#include "SoundManager/SpeakerComponent.h"
#include "SoundManager/SceneSoundComponent.h"
#include "Engine/Component/Movement/RandomRotationComponent.h"
#include "Engine/Feedback/VisualEffect/VisualEffectComponent.h"

namespace SB
{
	class StreakComponent;
	//ComponentRegistration luaRegistration("LuaComponent", &SB::DefaultComponentCreator<LuaComponent>);
	ComponentRegistration modelRegistration("ModelComponent", &SB::DefaultComponentCreator<ModelComponent>);
	ComponentRegistration colliderRegistration("ColliderComponent", &SB::DefaultComponentCreator<ColliderComponent>);
	ComponentRegistration circleMovementRegistration("CircleMovementComponent", &SB::DefaultComponentCreator<CircleMovementComponent>);
	ComponentRegistration streakComponentRegistration("StreakComponent", &SB::DefaultComponentCreator<StreakComponent>);
	ComponentRegistration particleRegistration("ParticleComponent", &SB::DefaultComponentCreator<ParticleComponent>);
	ComponentRegistration pointLightComponentRegistration("PointLightComponent", &SB::DefaultComponentCreator<PointLightComponent>);
	ComponentRegistration markerComponentRegistration("MarkerComponent", &SB::DefaultComponentCreator<MarkerComponent>);
	ComponentRegistration speakerComponentRegistration("SpeakerComponent", &SB::DefaultComponentCreator<SpeakerComponent>);
	ComponentRegistration randomRotationComponentRegistration("RandomRotationComponent", &SB::DefaultComponentCreator<RandomRotationComponent>);
	ComponentRegistration musicComponentRegistration("SceneSoundComponent", &SB::DefaultComponentCreator<SceneSoundComponent>);
	ComponentRegistration visualEffectComponentRegistration("VisualEffectComponent", &SB::DefaultComponentCreator<VisualEffectComponent>);

	__declspec(noinline) void RegisterEngineComponents()
	{
	}
}
