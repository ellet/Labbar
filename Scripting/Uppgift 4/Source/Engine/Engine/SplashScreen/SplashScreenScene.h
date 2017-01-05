#pragma once
#include "Engine\Scene\Scene.h"

namespace SB
{
	template<typename T>
	class ConstantBuffer;
	class SplashScreenEffect;

	struct SplashScreenCBuffer
	{
		Vector4f time;
	};

	class SplashScreenScene : public Scene
	{
	public:
		SplashScreenScene(PostMasterState & aPostMasterState);
		~SplashScreenScene();

		void Update(const Time & aDeltaTime) override;
		void Render() override;

		virtual void OnEnter() override;

		virtual void OnExit() override;

	private:
		std::unique_ptr<ConstantBuffer<SplashScreenCBuffer>> myConstantBuffer;
		std::shared_ptr<SplashScreenEffect> mySplashScreenEffect;
		Sprite mySprite;
	};
}
