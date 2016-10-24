#pragma once
#include <Engine\Component\BaseComponent.h>

namespace SB
{
	class Model;
	class Scene;
}
class WeaponComponent;

enum class ePlayerWeaponNodeIndex
{
	ePrimaryLeft,
	ePrimaryRight,
	eSecondaryLeft,
	eSecondaryRight
};

enum class eWeaponEquipState
{
	eUnequipped,
	eEquipping,
	eEquipped,
	eUnequipping
};


class PlayerShootComponent : public SB::BaseComponent, 
	public SB::Subscriber<SB::KeyDownMessage<SB::KeyboardKey::eNum1>>, public SB::Subscriber<SB::KeyDownMessage<SB::KeyboardKey::eNum2>>,
	public SB::Subscriber<SB::KeyDownMessage<SB::KeyboardKey::eNum3>>, public SB::Subscriber<SB::KeyDownMessage<SB::KeyboardKey::eNum4>>
{
public:
	virtual void Initialize() override;
	~PlayerShootComponent();

	void LoadData(SB::DataNode aProperties) override;
	virtual void Update(const SB::Time& aDeltaTime) override;
	void EquipPrimaryWeapon(const std::string& aWeaponIdentifier);
	void EquipPrimaryWeapon(const unsigned short aWeaponIndex);
	void EquipSecondaryWeapon(const std::string& aWeaponIdentifier);
	void EquipSecondaryWeapon(const unsigned short aWeaponIndex);

	SB::ReceiveResult Receive(const SB::LeftMouseButtonDownMessage& aMessage);
	SB::ReceiveResult Receive(const SB::LeftMouseButtonUpMessage& aMessage);
	SB::ReceiveResult Receive(const SB::RightMouseButtonDownMessage& aMessage);
	SB::ReceiveResult Receive(const SB::RightMouseButtonUpMessage& aMessage);
	SB::ReceiveResult Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum1>& aMessage) override;
	SB::ReceiveResult Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum2>& aMessage) override;
	SB::ReceiveResult Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum3>& aMessage) override;
	SB::ReceiveResult Receive(const SB::KeyDownMessage<SB::KeyboardKey::eNum4>& aMessage) override;

	int GetTimesFired()const;


private:
	void CreateWeaponNodes();
	void LoadWeapons();
	std::shared_ptr<WeaponComponent> LoadWeapon(SB::DataNode aWeaponData);
	void InitWeapons();
	void UpdateEquippingWeapons(const SB::Time& aDeltaTime);
	void UpdatePrimaryWeapon(const SB::Time& aDeltaTime);
	void UpdateSecondaryWeapon(const SB::Time& aDeltaTime);
	void FireWeapon(std::shared_ptr<WeaponComponent> aWeapon, const bool aIsPrimaryWeapon);

	SB::GrowingArray<std::shared_ptr<WeaponComponent>> myPrimaryWeapons;
	SB::GrowingArray<std::shared_ptr<WeaponComponent>> mySecondaryWeapons;
	SB::GrowingArray<SB::ObjectPtr> myWeaponNodes;
	SB::ObjectPtr myWeaponRoot;
	std::shared_ptr<SB::Subscription<SB::LeftMouseButtonDownMessage>> myLeftKeySubscription;
	std::shared_ptr<SB::Subscription<SB::RightMouseButtonDownMessage>> myRightKeySubscription;
	std::shared_ptr<SB::Subscription<SB::LeftMouseButtonUpMessage>> myLeftKeyUpSubscription;
	std::shared_ptr<SB::Subscription<SB::RightMouseButtonUpMessage>> myRightKeyUpSubscription;
	std::shared_ptr<WeaponComponent> myEquippedPrimaryWeapon;
	std::shared_ptr<WeaponComponent> myEquippedSecondaryWeapon;
	std::shared_ptr<WeaponComponent> myQueuedEquippedPrimaryWeapon;
	std::shared_ptr<WeaponComponent> myQueuedEquippedSecondaryWeapon;
	SB::Time myPrimaryShotCooldown;
	SB::Time mySecondaryShotCooldown;
	eWeaponEquipState myPrimaryWeaponEquipState;
	eWeaponEquipState mySecondaryWeaponEquipState;
	unsigned int myShotCounter;
	bool myIsShootingPrimary;
	bool myIsShootingSecondary;
};

