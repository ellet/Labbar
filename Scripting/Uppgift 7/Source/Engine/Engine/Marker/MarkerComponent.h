#pragma once
#include "Engine\Component\BaseComponent.h"
#include "Engine/ObjectiveEnum.h"

namespace SB
{
	class GUIMarker;
	

	class MarkerComponent : public BaseComponent
	{
	public:
		MarkerComponent();
		~MarkerComponent();

		virtual void EndUpdate(const Time & aDeltaTime) override;


		void ToJson(JsonSerializer &aSerializer) const override;

		virtual void Initialize() override;

		void SetColor(const Vector4f &aColor);

		virtual void OnRemoved() override;

		void SetActive(bool aValue);

		bool GetActive() const;

		
		void SetIsObjective(bool aValue);
		void SetSprite(const ObjectiveType & aObjectiveType);


	private:
		const Vector2f GetScreenPosition(const Vector3f & aPosition) const;
		std::shared_ptr<GUIMarker> myGUIMarker;
		bool myIsObjectiveMarker;
	};

}




