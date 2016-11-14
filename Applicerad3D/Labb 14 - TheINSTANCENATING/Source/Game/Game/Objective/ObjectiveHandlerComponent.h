#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Utilities\Container\Heap\Heap.h>
class ObjectiveComponent;
class Objective;
struct ObjectiveIdentifierInfo;

namespace SB
{
	template <typename TComponentType>
	class ComponentPtr;
}


class ObjectiveHandlerComponent :
	public SB::BaseComponent
{
public:
	ObjectiveHandlerComponent();
	~ObjectiveHandlerComponent();

	void ObjectiveComplete(const SB::Vector2us &aObjective);


	const std::shared_ptr<Objective> &GetObjective(const SB::Vector2us &aChainAndPos);

	SB::Vector2us GetObjectiveChainAndPos(const char *aObjective);
	bool SetCounter (const SB::Vector2us &aChainAndPos, unsigned short aCounter);
	bool IncrementCounter (const SB::Vector2us &aChainAndPos, unsigned short aIncrementValue);
	bool DecrementCounter (const SB::Vector2us &aChainAndPos, unsigned short aDecrementValue);

	const std::string &GetIdentity(const SB::Vector2us &aChainAndPos)const;
	const std::string &GetDescription(const SB::Vector2us &aChainAndPos)const;

	void ActivateChain(unsigned short aChain);
	void ActivateObjective(const char * aObjective);
	virtual void LoadData(SB::DataNode aProperties) override;


	virtual void Initialize() override;


	virtual void Render() const override;


	virtual void Update(const SB::Time & aDeltaTime) override;


	virtual void ToJson() const override;

private:
	bool CheckTargetReached(const SB::Vector2us & aChainAndPos);

	void DefaultOnObjectiveComplete(const SB::Vector2us& aChainAndPos);


	std::shared_ptr<SB::Text> myText;

	//SB::GrowingArray<SB::GrowingArray<std::string>>myPriorityKeeper;
	SB::GrowingArray<short> myObjectiveProgress;
	SB::GrowingArray<SB::GrowingArray<std::shared_ptr<Objective>>>myObjectives;
	SB::GrowingArray<SB::Vector2us>myCompletedObjectives;

	std::shared_ptr<SB::GUIElement> myObjectiveGUI;

};

