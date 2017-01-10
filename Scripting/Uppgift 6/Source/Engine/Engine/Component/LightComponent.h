#pragma once
#include "Engine\Component\BaseComponent.h"

namespace SB
{
	
	class LightComponent : public BaseComponent
	{
	public:
		LightComponent();
		~LightComponent();

		virtual void Initialize() override;

	};
}
