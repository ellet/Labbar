#pragma once


class EnemyComponent : public SB::BaseComponent
{
public:
	EnemyComponent();
	~EnemyComponent();

	void Initialize() override;
	void Update(const SB::Time& aDeltaTime) override;

	virtual void LoadData(SB::DataNode aProperties) override;
	void ToJson(SB::JsonSerializer& aSerializer) const override;


private:
};
