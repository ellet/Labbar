#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Engine\Text\Text.h>

class Objective;
class ObjectiveHandlerComponent;
struct ObjectiveIdentifierInfo;

class ObjectiveComponent : public SB::BaseComponent
{
public:
	ObjectiveComponent();
	~ObjectiveComponent();

	const std::string &GetIdentity()const;
	const std::string &GetDescription()const;
	void SetCounter(unsigned short aCounter);
	void IncrementCounter(unsigned short aIncrementValue);
	void DecrementCounter(unsigned short aDecrementValue);
	virtual void Update(const SB::Time & aDeltaTime) override;
	
	virtual void Render() const override;


	virtual void Initialize() override;

	
	virtual void LoadData(SB::DataNode aProperties) override;


	virtual void ToJson() const override;

private:
	SB::ComponentPtr<ObjectiveHandlerComponent>myHandler;
	SB::Vector2us myChainAndPosition;
	std::string myIdentity;


	void OnObjectiveComplete();
};