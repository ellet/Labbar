#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Utilities\Container\Heap\Heap.h>


namespace SB
{
	template <typename TComponentType>
	class ComponentPtr;

	class ObjectiveComponent;
	class Objective;
	struct ObjectiveIdentifierInfo;


	class ObjectiveHandlerComponent :
		public SB::BaseComponent
	{
	public:
		ObjectiveHandlerComponent();
		~ObjectiveHandlerComponent();

		void ObjectiveComplete(const SB::Vector2us &aObjective);


		const std::shared_ptr<Objective> &GetObjective(const SB::Vector2us &aChainAndPos);

		SB::Vector2us GetObjectiveChainAndPos(const char *aObjective);
		bool SetCounter(const SB::Vector2us &aChainAndPos, unsigned short aCounter);
		bool IncrementCounter(const SB::Vector2us &aChainAndPos, unsigned short aIncrementValue);
		bool DecrementCounter(const SB::Vector2us &aChainAndPos, unsigned short aDecrementValue);

		const std::string &GetIdentity(const SB::Vector2us &aChainAndPos)const;
		const std::string &GetDescription(const SB::Vector2us &aChainAndPos)const;

		void ActivateChain(unsigned short aChain);
		void ActivateObjective(const char * aObjective);
		virtual void LoadData(SB::DataNode aProperties) override;

		virtual void Initialize() override;

		virtual void Render(const Camera & aCamera) const override;

		virtual void Update(const SB::Time & aDeltaTime) override;

		bool GetIsActive(const SB::Vector2us &aChainAndPosition)const;
		virtual void ToJson(JsonSerializer &aSerializer) const override;

	private:
		bool CheckTargetReached(const SB::Vector2us & aChainAndPos);

		void DefaultOnObjectiveComplete(const SB::Vector2us& aChainAndPos);


		std::shared_ptr<SB::Text> myText;

		//SB::GrowingArray<SB::GrowingArray<std::string>>myPriorityKeeper;
		SB::GrowingArray<short> myObjectiveProgress;
		SB::GrowingArray<SB::GrowingArray<std::shared_ptr<Objective>>>myObjectives;
		SB::GrowingArray<SB::Vector2us>myCompletedObjectives;

		SB::GUIElement *myObjectiveGUI;

	};

};