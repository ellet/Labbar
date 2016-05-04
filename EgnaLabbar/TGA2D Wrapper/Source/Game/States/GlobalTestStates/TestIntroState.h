#pragma once
#include <BaseClasses\BaseGameObject\BaseGameObject.h>
#include <BaseClasses\BaseState\BaseState.h>

#include "../../Object/MenuObjects/TestPlayButton.h"
#include "../../Object/MenuObjects/TestExitButton.h"

enum class eScenes
{
	Scene1,
	Scene2,
	Scene3
};


class TestIntroState :public BaseState
{
public:
	TestIntroState();
	~TestIntroState();

	void Update(const float aDeltaTime) override;
	void Draw() const override;

	void Scene1(float aDeltaTime);
	void Scene2(float aDeltaTime);

	void LoadScene1();
	void LoadScene2();

	void CheckForInput();

	bool FadeIn(float aTimeToFade, float aDeltatime);
	bool FadeOut(float aTimeToFade, float aDeltatime);
	bool FadeInFadeOut(float aTimeToFade, float aDeltatime);
	bool Delay(float aTimeToDelay, float aDeltaTime);

private:

	float myTimer;

	BaseGameObject* myMainBackground;
	BaseGameObject* myBlackScreen;
	BaseGameObject* myCreditsButton;
	float myBlackAlpha;

	BaseGameObject* myMainCharacter;
	BaseGameObject* myScene1BadGuys;
	BaseGameObject* myScene2BadGuys;

	BaseGameObject* myScene1BadGuys1;
	BaseGameObject* myScene1BadGuys2;
	BaseGameObject* myScene1BadGuys3;
	BaseGameObject* myScene1BadGuys4;
	BaseGameObject* myScene1BadGuys5;
	BaseGameObject* myScene1BadGuys6;
	BaseGameObject* myScene1BadGuys7;
	BaseGameObject* myScene1BadGuys8;

	BaseGameObject* myScene1Prop1;
	BaseGameObject* myScene2Prop1;

	BaseGameObject* myScene1Background1;
	BaseGameObject* myScene1Background2;

	CU::GrowingArray<BaseGameObject*> myGameObjectArray;

	eScenes myCurrentScene;

	TestPlayButton myPlayButton;
	TestExitButton myExitButton;

	bool myIntro1;
	bool myIntro2;
	
};