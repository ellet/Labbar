#pragma once
#include <Engine\Scene\Scene.h>


class PauseMenuScene : public SB::Scene
{
public:
	PauseMenuScene(SB::PostMasterState & aPostMasterState);
	~PauseMenuScene();

	void OnEnter() override;

	virtual void Render() override;

	virtual void Update(const SB::Time & aDeltaTime) override;

private:
	void ReturnToMainMenu();
	void Resume();
	void RunOptions();
	std::shared_ptr<SB::Sprite> myBackgroundSprite;
	std::shared_ptr<SB::InputListener> myInputListener;

protected:
	void BindGUIFunctions() override;
};

