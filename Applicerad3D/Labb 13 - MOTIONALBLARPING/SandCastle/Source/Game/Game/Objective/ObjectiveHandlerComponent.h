#pragma once
#include <Engine\Component\BaseComponent.h>
class ObjectiveComponent;

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

	void RemoveObjective(ObjectiveComponent *aObjective);

	void ObjectiveComplete();

	void AddObjective(ObjectiveComponent *aObjective);
	void ActivateObjective(ObjectiveComponent *aObjective);

	virtual void LoadData(SB::DataNode aProperties) override;


	virtual void Initialize() override;


	virtual void Render() const override;

private:
	ObjectiveComponent * myCurrentObjective;

	std::shared_ptr<SB::Text> myText;

	SB::GrowingArray<std::string>myObjectiveNames;
	SB::GrowingArray<ObjectiveComponent*>myObjectives;

	std::shared_ptr<SB::GUIElement> myObjectiveGUI;

};

