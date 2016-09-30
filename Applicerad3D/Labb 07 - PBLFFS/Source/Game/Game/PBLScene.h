#pragma once

#include <Engine/Scene/Scene.h>

class PBLScene : public Scene, public Subscriber<AnyKeyDownMessage>, public Subscriber<AnyKeyUpMessage>
{
public:
	PBLScene();
	~PBLScene();

	virtual void Update(const Time & aDeltaTime) override;


	virtual void Render() override;

	ReceiveResult Receive(const AnyKeyDownMessage & aMessage) override;
	ReceiveResult Receive(const AnyKeyUpMessage & aMessage) override;

private:
	void CreateFactories();
	bool myRotateLeft;
	bool myRotateRight;
	bool myMoveLeft;
	bool myMoveRight;
	bool myMoveForward;
	bool myMoveBackward;

	bool myPitchForward;
	bool myPitchBackward;
	bool myRollLeft;
	bool myRollRight;
	bool myMoveDown;
	bool myMoveUp;

};