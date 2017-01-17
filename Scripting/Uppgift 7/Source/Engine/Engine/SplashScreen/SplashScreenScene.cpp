#include "stdafx.h"
#include "Engine\SplashScreen\SplashScreenScene.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Texture\Texture.h"
#include "Engine\SplashScreen\SplashScreenEffect.h"
#include <Engine\GUI\GUILoader.h>
#include "Engine/Texture/GuiRenderTarget.h"

namespace SB
{
	SplashScreenScene::SplashScreenScene(PostMasterState & aPostMasterState)
		: Scene(aPostMasterState, "Splash Screen")
	{
		myConstantBuffer = std::make_unique<ConstantBuffer<SplashScreenCBuffer>>();
		mySprite.SetTexture(Engine::GetResourceManager().Get<Texture>("textures/intrologo.dds"));
		mySprite.SetEffect(std::make_shared<SplashScreenEffect>());
	}

	SplashScreenScene::~SplashScreenScene()
	{
	}

	void SplashScreenScene::Update(const Time & aDeltaTime)
	{
		Scene::Update(aDeltaTime);
	}

	void SplashScreenScene::Render()
	{
		myConstantBuffer->UpdateData(SplashScreenCBuffer{ Vector4f(myTime.InSeconds(), 0.f, 0.f, 0.f) });
		myConstantBuffer->BindToPS(2);
		Vector2f pos = Engine::GetRenderer().GetRenderTargetResolution() / 2.f;
		pos.x = std::floorf(pos.x);
		pos.y = std::floorf(pos.y);
		mySprite.SetPosition(pos);
		mySprite.SetOrigin(mySprite.GetTexture()->GetSize() / 2.f);
		myGuiRenderTarget->Render(mySprite);

		Scene::Render();
	}

	void SplashScreenScene::OnEnter()
	{
		SB::Engine::GetGUILoader().DisableGUI();
	}

	void SplashScreenScene::OnExit()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}
