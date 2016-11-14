#pragma once

struct WarpDriveData
{
	SB::Vector2f resolution;
	float timer;
	float junk;
};

class MainMenuScene : public SB::Scene
{
public:
	MainMenuScene(SB::PostMasterState & aPostMasterState);
	~MainMenuScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void Render() override;


	virtual void OnEnter() override;


	virtual void OnExit() override;

private:
	void StartGame();
	void RunLevelSelect();
	void RunCredits();
	void RunOptions();
	void QuitGame();
	void PlayHoverOverButtonSound();
	std::shared_ptr<SB::Texture> myNoiseTexture;
	std::shared_ptr<SB::Effect> myWarpdriveExitEffect;
	std::shared_ptr<SB::Effect> myWarpdriveEnterEffect;
	std::shared_ptr<SB::ConstantBuffer<WarpDriveData>> myWarpDriveCBuffer;
	SB::Time myWarpDriveTimer;


protected:
	virtual void BindGUIFunctions() override;

};

