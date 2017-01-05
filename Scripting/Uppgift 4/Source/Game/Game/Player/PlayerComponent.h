#pragma once
#include <Engine\Component\BaseComponent.h>
class PlayerComponent : public SB::BaseComponent
{
public:
	PlayerComponent();
	~PlayerComponent();

	void Initialize() override;
	void Update(const SB::Time& aDeltaTime) override;

	virtual void LoadData(SB::DataNode aProperties) override;
	void ToJson(SB::JsonSerializer& aSerializer) const override;


private:
	SB::InputListener myInput;
	float mySpeed;
};

