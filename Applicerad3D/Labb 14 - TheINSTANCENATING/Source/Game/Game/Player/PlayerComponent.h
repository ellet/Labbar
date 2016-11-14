#pragma once
#include "Engine/Component/BaseComponent.h"
#include "Game/Player/PlayerMessages.h"
#include "../Engine/Engine/Time/Stopwatch.h"
#include "Game/GenericGameMessages.h"

namespace SB
{
	struct CollisionEvent;
	struct TriggerCollisionEvent;
	class GUIMarker;
}

struct ObjectOutOfHealthMessage;

class PlayerComponent :
	public SB::BaseComponent, public SB::EventSubscriber<SB::CollisionEvent>, public SB::EventSubscriber<SB::TriggerCollisionEvent>, 
	public SB::EventSubscriber<ObjectOutOfHealthMessage>, public SB::Subscriber<SetPlayerDataMessage>,
	public SB::Subscriber<OnSceneExitMessage>,
	public SB::Subscriber<PlayerTakenDamageMessage>
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Initialize() override;
	static void ToggleGodMode()
	{
		ourGodMode = !(ourGodMode);
	}
	virtual void Update(const SB::Time& aDeltaTime) override;
	virtual void LoadData(SB::DataNode aProperties) override;
	void ToJson()const  override;

private:
	void UpdateHealthRecovery(const SB::Time& aDeltaTime);
	void UpdateRespawnCounter(const SB::Time& aDeltaTime);
	void SendPlayerData();
	void Respawn();
	SB::ReceiveResult Receive(const SetPlayerDataMessage& aMessage) override;
	SB::ReceiveResult Receive(const OnSceneExitMessage& aMessage) override;
	SB::ReceiveResult Receive(const PlayerTakenDamageMessage& aMessage) override;
	const SB::Vector2f GetScreenPosition(const SB::Vector3f & aPosition) const;
	void RecieveEvent(const SB::CollisionEvent & aEvent) override;
	void RecieveEvent(const ObjectOutOfHealthMessage & aEvent) override;
	void RecieveEvent(const SB::TriggerCollisionEvent & aEvent) override;

	void CalculateDamageTakenDirection(const SB::Vector3f & aObjectPosition);
	static SavedPlayerData mySavedData;
	SB::Time myRespawnTimer;
	SB::Time myHealthRecoveryTimer; //Resets upon taking damage
	SB::Time myCollisionCooldown; //TODO: This should be on enter collision instead of a cooldown
	bool myCanCollide; //TODO: This should be on enter collision instead of a cooldown
	float myRespawnCooldown;
	float myHealthRecoveryPerSecond;
	float myHealthRecoveryCooldown;
	float myCShakePlayerCollision;
	float myCShakePlayerShotDamage;
	std::shared_ptr<SB::GUIMarker> myGUIMarker;
	SB::Time myMarkerTimer;

	static bool ourGodMode;
};
