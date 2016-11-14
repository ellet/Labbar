#pragma once
#include "Engine\Scene\Scene.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"
#include "..\MessageBlocker.h"
#include "..\Input\InputListener.h"

namespace ENGINE_NAMESPACE
{

	class JsonScene : public Scene
	{
	public:
		JsonScene(PostMasterState & aPostMasterState, const char* aFilePath = "");
		virtual ~JsonScene();

		virtual void Update(const Time & aDeltaTime) override;
		void Render() override;
		void RenderGui() override;

		virtual void OnEnter() override;
	};

}
