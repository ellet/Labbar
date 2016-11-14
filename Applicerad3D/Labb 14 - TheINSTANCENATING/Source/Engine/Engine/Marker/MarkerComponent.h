#pragma once
#include "Engine\Component\BaseComponent.h"
namespace ENGINE_NAMESPACE
{
	class GUIMarker;


	class MarkerComponent : public BaseComponent
	{
	public:
		MarkerComponent();
		~MarkerComponent();

		virtual void Update(const Time & aDeltaTime) override;


		void ToJson() const override;
		virtual void Render() const override;

		virtual void Initialize() override;


		virtual void OnRemoved() override;

	private:
		const Vector2f GetScreenPosition(const Vector3f & aPosition) const;
		std::shared_ptr<GUIMarker> myGUIMarker;
	};
}


