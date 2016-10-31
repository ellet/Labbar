#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Engine\Text\Text.h>
class ObjectiveComponent : public SB::BaseComponent, public SB::IFormattable
{
public:
	ObjectiveComponent();
	~ObjectiveComponent();
	const std::string &GetIdentity()const;
	const std::string &GetDescription()const;
	const std::string &GetObjectiveChain()const;

	void SetCounter(int aCounter);
	virtual void Update(const SB::Time & aDeltaTime) override;


	virtual void Render() const override;


	virtual void Initialize() override;

	
	virtual void LoadData(SB::DataNode aProperties) override;

	
	virtual std::string ToString() const override;


	virtual std::string ToString(const std::string &aFormat) const override;

private:

	std::string myObjectiveChain;
	std::string myIdentity;
	std::string myObjectiveDescription;
	int myCounterTarget;
	int myCounter;


};