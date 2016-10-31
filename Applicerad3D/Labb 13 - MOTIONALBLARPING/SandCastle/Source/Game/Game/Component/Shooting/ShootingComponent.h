#pragma once
#include <Engine\Component\BaseComponent.h>


class ShootingComponent :
	public SB::BaseComponent
{
public:
	ShootingComponent();
	~ShootingComponent();

	void Update(const SB::Time &aDeltaTime)override;
	void Shoot();
	void Shoot(const SB::Vector3f & aDirection);

	virtual void Initialize() override;

	int GetTimesFired()const;
private:
	std::shared_ptr<SB::Model> myModel;
	int myTimesFired;
};

