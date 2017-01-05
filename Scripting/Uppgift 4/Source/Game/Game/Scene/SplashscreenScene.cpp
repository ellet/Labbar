#include "stdafx.h"
#include "SplashscreenScene.h"
#include <Engine/Scene/Messages/PopSceneMessage.h>
#include <Engine\GUI\GUILoader.h>
#include <Engine/Texture/GuiRenderTarget.h>

SplashscreenScene::SplashscreenScene(SB::PostMasterState & aPostMasterState) : SB::Scene(aPostMasterState, "Splashscreen")
{
	myTimer = 0;
	myStateTimer = 1.f;
	myState = eSplashscreenState::eFadeInTGALogo;

	SB::Vector2f windowSize(1080.f * (SB::Engine::GetRenderer().GetRenderTargetResolution().x / SB::Engine::GetRenderer().GetRenderTargetResolution().y), 1080.f);
	windowSize /= 2.f;

	SB::Engine::GetEngineSettings().ToggleBloom();

	std::shared_ptr<SB::Texture> tga;
	tga = SB::Engine::GetInstance().GetResourceManager().Get<SB::Texture>("Assets/Textures/Logo/tga.dds");
	myTGALogo = std::make_shared<SB::Sprite>();
	myTGALogo->SetOrigin(tga->GetSize() / 2.f);
	myTGALogo->SetPosition(windowSize);
	myTGALogo->SetTexture(tga);
	tga = nullptr;

	std::shared_ptr<SB::Texture> sandcastle;
	sandcastle = SB::Engine::GetInstance().GetResourceManager().Get<SB::Texture>("Assets/Textures/Logo/sandcastle.dds");
	mySandcastleLogo = std::make_shared<SB::Sprite>();
	mySandcastleLogo->SetOrigin(sandcastle->GetSize() / 2.f);
	mySandcastleLogo->SetPosition(windowSize);
	mySandcastleLogo->SetTexture(sandcastle);
	sandcastle = nullptr;

	myInputListener = std::make_shared<SB::InputListener>();

	myProgress = 0;
	myIsPopped = false;
}


SplashscreenScene::~SplashscreenScene()
{
}

void SplashscreenScene::Update(const SB::Time & aDeltaTime)
{
	myTimer += aDeltaTime;
	if (myTimer >= myStateTimer)
	{
		myTimer = 0.f;
		int temp = static_cast<int>(myState) + 1;
		myState = static_cast<eSplashscreenState>(temp);
	}

	myProgress = (myTimer.InSeconds() / myStateTimer.InSeconds());
	
	if (myState == eSplashscreenState::eStop || myInputListener->GetPressedThisFrame(SB::KeyboardKey::eEscape))
	{
		PoppingMyself();
	}
}

void SplashscreenScene::Render()
{
	SB::Vector4f color = SB::Vector4f::One;

	switch (myState)
	{
	case eSplashscreenState::eFadeInTGALogo:
		color.w = myProgress;
		myTGALogo->SetColor(color);
		myGuiRenderTarget->Render(*myTGALogo);
		break;
	case eSplashscreenState::eStayTGALogo:
		myGuiRenderTarget->Render(*myTGALogo);
		break;
	case eSplashscreenState::eFadeOutTGALogo:
		color.w = 1.f - myProgress;
		myTGALogo->SetColor(color);
		myGuiRenderTarget->Render(*myTGALogo);
		break;
	case eSplashscreenState::eFadeInSandcastleLogo:
		color.w = myProgress;
		mySandcastleLogo->SetColor(color);
		myGuiRenderTarget->Render(*mySandcastleLogo);
		break;
	case eSplashscreenState::eStaySandcastleLogo:
		myGuiRenderTarget->Render(*mySandcastleLogo);
		break;
	case eSplashscreenState::eFadeOutSandcastleLogo:
		color.w = 1.f - myProgress;
		mySandcastleLogo->SetColor(color);
		myGuiRenderTarget->Render(*mySandcastleLogo);
		break;
	case eSplashscreenState::eStop:
		break;
	default:
		break;
	}
}

SB::ReceiveResult SplashscreenScene::Receive(const SB::AnyMouseButtonUpMessage & aMessage)
{
	PoppingMyself();
	return SB::ReceiveResult::eContinue;
}

void SplashscreenScene::OnEnter()
{
	SB::Engine::GetGUILoader().DisableGUI();
}

void SplashscreenScene::PoppingMyself()
{
	if (myIsPopped == false)
	{
		SB::PostMaster::Post(SB::PopSceneMessage(SB::ePopType::eCurrent));
		SB::Engine::GetEngineSettings().ToggleBloom();
		myIsPopped = true;
	}
}
