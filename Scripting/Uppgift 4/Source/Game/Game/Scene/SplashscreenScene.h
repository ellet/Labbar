#pragma once

enum eSplashscreenState
{
	eFadeInTGALogo = 0,
	eStayTGALogo,
	eFadeOutTGALogo,
	eFadeInSandcastleLogo,
	eStaySandcastleLogo,
	eFadeOutSandcastleLogo,
	eStop
};

class SplashscreenScene : public SB::Scene, public SB::Subscriber<SB::AnyMouseButtonUpMessage>
{
public:
	SplashscreenScene(SB::PostMasterState & aPostMasterState);
	~SplashscreenScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;

	SB::ReceiveResult Receive(const SB::AnyMouseButtonUpMessage & aMessage) override;


	virtual void OnEnter() override;

private:
	void PoppingMyself();
	std::shared_ptr<SB::Sprite> myTGALogo;
	std::shared_ptr<SB::Sprite> mySandcastleLogo;
	std::shared_ptr<SB::InputListener> myInputListener;
	SB::Time myTimer;
	SB::Time myStateTimer;
	eSplashscreenState myState;
	float myProgress;

	bool myIsPopped;
};

