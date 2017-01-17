#pragma once
#include <Engine\Component\BaseComponent.h>
#include <Engine\Text\Text.h>
#include "ObjectiveMessages.h"
#include <Engine/ObjectiveEnum.h>





namespace SB
{
	class MarkerComponent;
	class Objective;
	class ObjectiveHandlerComponent;
	struct ObjectiveIdentifierInfo;

	class ObjectiveComponent : public BaseComponent, public Subscriber<ObjectiveStateChangedMessage>
	{
	public:
		ObjectiveComponent();
		~ObjectiveComponent();

		const std::string &GetIdentity()const;
		const std::string &GetDescription()const;
		void SetCounter(unsigned short aCounter);
		void IncrementCounter(unsigned short aIncrementValue);
		void DecrementCounter(unsigned short aDecrementValue);
		virtual void Update(const Time & aDeltaTime) override;

		void AddObjectiveMarker();
		virtual void Initialize() override;


		virtual void LoadData(DataNode aProperties) override;

		SB::ReceiveResult Receive(const ObjectiveStateChangedMessage &aMessage)override;

		virtual void ToJson(JsonSerializer &aSerializer) const override;

	private:
		ComponentPtr<ObjectiveHandlerComponent>myHandler;
		Vector2us myChainAndPosition;
		std::string myIdentity;
		ObjectiveType myObjectiveType;
		void OnObjectiveComplete();
	};
};