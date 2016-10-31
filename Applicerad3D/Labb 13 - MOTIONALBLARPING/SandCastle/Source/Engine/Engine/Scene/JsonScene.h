#pragma once
#include "Engine\Scene\Scene.h"
#include "..\Utilities\Utilities\Randomizer\Randomizer.h"

namespace ENGINE_NAMESPACE
{

	

	class JsonScene : public Scene
	{
	public:
		JsonScene(const char* aFilePath = "");
		~JsonScene();

		virtual void Update(const Time & aDeltaTime) override;
		void Render() override;
		void CreateAIEnemy();

	private:
		ObjectPtr myEnemy;

		Randomizer myRandomizer;

	};

}
