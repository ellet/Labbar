#pragma once
#include "..\Engine\Engine\Input\InputListener.h"

class OptionsScene : public SB::Scene
{
public:
	OptionsScene(SB::PostMasterState & aPostMasterState);
	~OptionsScene();

	virtual void Update(const SB::Time & aDeltaTime) override;
	virtual void Render() override;
	virtual void OnEnter() override;

private:
	void Return();
	void ToggleBloom();
	void ToggleMotionBlur();
	void ToggleFullscreen();
	void ToggleSFX()const;
	void ToggleBGM()const;
	void ToggleDialog()const;
	void ToggleAmbient()const;

	std::shared_ptr<SB::InputListener> myInputListener;
	bool myBloomToggle;
	bool myMotionBlurToggle;

protected:
	void SetInitialCheckedStates();
	virtual void BindGUIFunctions() override;

private:
	bool myBGMToggle;
	bool mySFXToggle;
};

