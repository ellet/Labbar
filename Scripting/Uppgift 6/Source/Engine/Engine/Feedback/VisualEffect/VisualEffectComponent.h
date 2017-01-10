#pragma once
#include "Engine\Component\BaseComponent.h"

namespace SB
{
	template<typename T>
	class VertexBuffer;

	struct VisualEffectVertex;

	class VisualEffectComponent : public BaseComponent
	{
	public:
		VisualEffectComponent();
		~VisualEffectComponent();

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render(const Camera & aCamera) const override;

	private:
		std::shared_ptr<VertexBuffer<VisualEffectVertex>> myVertexBuffer;
		std::shared_ptr<VisualEffect> myVisualEffect;
		Time myRunTime;
	};

}