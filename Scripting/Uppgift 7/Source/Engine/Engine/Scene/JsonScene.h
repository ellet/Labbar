#pragma once
#include "Engine\Scene\Scene.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"
#include "..\MessageBlocker.h"
#include "..\Input\InputListener.h"

namespace SB
{

	class JsonScene : public Scene
	{
	public:
		JsonScene(PostMasterState & aPostMasterState, const char* aFilePath = "", const char* aSkyBoxFilePath = "");
		virtual ~JsonScene();

		virtual void Update(const Time & aDeltaTime) override;
		void RenderGui() override;

		virtual void OnEnter() override;		
	private:
		std::shared_ptr<SB::ModelInstance> myHead;
		ObjectPtr myModel;	
	};

}
