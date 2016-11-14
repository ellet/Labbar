#pragma once

class ControllerComponent : public SB::BaseComponent
{
public:
	ControllerComponent();
	virtual ~ControllerComponent() = 0;

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void LoadData(SB::DataNode aProperties) override;
};
