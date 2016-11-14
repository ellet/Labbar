#pragma once
#include <Engine\Component\BaseComponent.h>

namespace SB
{
	class Model;
	class Scene;
}
class WeaponComponent;
class WeaponMount;


enum class ePlayerWeaponType
{
	ePrimary,
	eSecondary
};


class PlayerShootComponent : public SB::BaseComponent, 
	public SB::Subscriber<SB::AnyKeyDownMessage>
{
public:
	virtual void Initialize() override;
	void OnRemoved() override;
	~PlayerShootComponent();

	void LoadData(SB::DataNode aProperties) override;
	virtual void Update(const SB::Time& aDeltaTime) override;
	void EquipWeapon(const ePlayerWeaponType aWeaponType, const std::string& aWeaponIdentifier);
	void EquipWeapon(const ePlayerWeaponType aWeaponType, const unsigned short aWeaponIndex);

	SB::ReceiveResult Receive(const SB::LeftMouseButtonDownMessage& aMessage);
	SB::ReceiveResult Receive(const SB::LeftMouseButtonUpMessage& aMessage);
	SB::ReceiveResult Receive(const SB::RightMouseButtonDownMessage& aMessage);
	SB::ReceiveResult Receive(const SB::RightMouseButtonUpMessage& aMessage);
	SB::ReceiveResult Receive(const SB::AnyKeyDownMessage& aMessage) override;
	void SetIsWeaponOwned(const SB::GrowingArray<bool> aOwnedFlags, const ePlayerWeaponType aWeaponType);
	SB::GrowingArray<bool> GetOwnedWeapons(const ePlayerWeaponType aWeaponType);

	int GetTimesFired() const;



	virtual void ToJson() const override;

private:
	void LoadWeapons();
	std::shared_ptr<WeaponComponent> LoadWeapon(SB::DataNode aWeaponData);
	void CreateWeaponNodes();
	void InitWeapons();
	void SetWeaponUser();
	void Reset();
	void UpdateWeaponMounts(const SB::Time& aDeltaTime);
	void FireWeapon(const ePlayerWeaponType aWeaponType);
	void EquipWeaponInstantly(const ePlayerWeaponType aWeaponType, const std::string& aWeaponIdentifier);
	void EquipWeaponInstantly(const ePlayerWeaponType aWeaponType, const unsigned short aWeaponIndex);


	SB::GrowingArray<std::shared_ptr<WeaponComponent>> myPrimaryWeapons;
	SB::GrowingArray<std::shared_ptr<WeaponComponent>> mySecondaryWeapons;
	SB::GrowingArray<std::shared_ptr<WeaponMount>> myWeaponMounts;
	SB::ObjectPtr myWeaponRoot;
	std::shared_ptr<SB::Subscription<SB::LeftMouseButtonDownMessage>> myLeftKeySubscription;
	std::shared_ptr<SB::Subscription<SB::RightMouseButtonDownMessage>> myRightKeySubscription;
	std::shared_ptr<SB::Subscription<SB::LeftMouseButtonUpMessage>> myLeftKeyUpSubscription;
	std::shared_ptr<SB::Subscription<SB::RightMouseButtonUpMessage>> myRightKeyUpSubscription;
	unsigned int myShotCounter; //TODO: Delete this once we remove the LuaScript function tied to it
};

