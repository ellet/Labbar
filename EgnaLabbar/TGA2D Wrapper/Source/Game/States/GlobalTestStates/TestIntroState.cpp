#include "stdafx.h"
#include "TestIntroState.h"
#include "../../Levels\LevelManager.h"
#include "../../EventManager\EventManager.h"
#include <InputWrapper/InputWrapper.h>
#include <StateManager/StateManager.h>
#include <Input/MouseInput/MouseInput.h>
#include <CollisionManager/CollisionManager.h>
#include <Utility\MouseInputResolutionAdaption.h>
#include <BaseClasses\FactoryGameObject\FactoryGameObject.h>

TestIntroState::TestIntroState()
{

	myTimer = 0;

	myMainBackground = FactoryGameObject::CreateObject<BaseGameObject>();
	myMainBackground->LoadSprite("Sprites/Backgrounds/Intro/intro_bg.png");
	myMainBackground->SetPivot(Vector2f(0.f, 0.f));
	myMainBackground->SetPosition(Vector2f(0.f, 0.f));

	myBlackAlpha = 0;
	myBlackScreen = FactoryGameObject::CreateObject<BaseGameObject>();
	myBlackScreen->LoadSprite("Sprites/Levels/Intro/black.png");
	myBlackScreen->SetPivot(Vector2f(0.5f, 0.5f));
	myBlackScreen->SetPosition(Vector2f(900.f, 500.f));
	myBlackScreen->SetSize(Vector2f(30.f, 20.f));
	myBlackScreen->SetColor(Vector4f(0, 0, 0, myBlackAlpha));

	myMainCharacter = FactoryGameObject::CreateObject<BaseGameObject>();
	myMainCharacter->LoadSprite("Sprites/Levels/Intro/gubbe.png");

	myScene2BadGuys = FactoryGameObject::CreateObject<BaseGameObject>();
	myScene2BadGuys->LoadSprite("Sprites/Levels/Intro/badguys.png");
	myScene2BadGuys->SetColor(Vector4f(0, 0, 0, 0.f));

	myScene1Prop1 = FactoryGameObject::CreateObject<BaseGameObject>();
	myScene1Prop1->LoadSprite("Sprites/Levels/Intro/badguys.png");

	myScene2Prop1 = FactoryGameObject::CreateObject<BaseGameObject>();
	myScene2Prop1->LoadSprite("Sprites/Levels/Intro/snurra.png");

	myScene1Background1 = FactoryGameObject::CreateObject<BaseGameObject>();
	myScene1Background1->LoadSprite("Sprites/Levels/Intro/cliff_path.png");

	myScene1Background2 = FactoryGameObject::CreateObject<BaseGameObject>();
	myScene1Background2->LoadSprite("Sprites/Levels/Intro/cliff_bg.png");

	myScene1BadGuys = FactoryGameObject::CreateObject<BaseGameObject>();
	myScene1BadGuys->LoadSprite("Sprites/Levels/Intro/soldiers.png");
	myScene1BadGuys->SetColor(Vector4f(0, 0, 0, 0.f));

	myCreditsButton = FactoryGameObject::CreateObject<BaseGameObject>();
	myCreditsButton->LoadSprite("Sprites/Levels/Intro/menucreditstemp.png");


	myCreditsButton->SetPosition(Vector2f(400, 530));

	myGameObjectArray.Init(20);

	myGameObjectArray.Add(myScene1BadGuys1);
	//myGameObjectArray.Add(myScene1BadGuys2);
	//myGameObjectArray.Add(myScene1BadGuys3);
	//myGameObjectArray.Add(myScene1BadGuys4);
	//myGameObjectArray.Add(myScene1BadGuys5);
	//myGameObjectArray.Add(myScene1BadGuys6);
	//myGameObjectArray.Add(myScene1BadGuys7);
	//myGameObjectArray.Add(myScene1BadGuys8);
	for (unsigned short i = 0; i < myGameObjectArray.Size(); i++)
	{
		myGameObjectArray[i] = FactoryGameObject::CreateObject<BaseGameObject>();
		myGameObjectArray[i]->LoadSprite("Sprites/Levels/Intro/soldiers.png");
		myGameObjectArray[i]->SetColor(Vector4f(0, 0, 0, 0));
	}

	myPlayButton.SetPosition(Vector2f(400.f, 400.f));
	myPlayButton.Inut();

	myExitButton.SetPosition(Vector2f(400.f, 660.f));
	myExitButton.Inut();

	LoadScene1();
	myCurrentScene = eScenes::Scene1;
}


//aTimeToFade in seconds.
bool TestIntroState::FadeInFadeOut(float aTimeToFade, float aDeltatime)
{
	myTimer += aDeltatime;
	if (aTimeToFade / 2 > myTimer)
	{
		myBlackAlpha += ((aDeltatime / aTimeToFade) * 2);
	}
	else if (aTimeToFade > myTimer)
	{
		myBlackAlpha -= (aDeltatime / aTimeToFade);

	}
	if (myTimer >= aTimeToFade)
	{
		myTimer = 0;
		return true;
	}
	myBlackScreen->SetColor(Vector4f(0, 0, 0, myBlackAlpha));
	return false;
}
bool TestIntroState::Delay(float aTimeToDelay, float aDeltaTime)
{
	myTimer += aDeltaTime;
	if (aTimeToDelay < myTimer)
	{
		myTimer = 0;
		return true;
	}
	return false;
}
//aTimeToFade in seconds.
bool TestIntroState::FadeIn(float aTimeToFade, float aDeltatime)
{
	myTimer += aDeltatime;
	if (aTimeToFade > myTimer && myBlackAlpha >= 0)
	{
		myBlackAlpha -= (aDeltatime / aTimeToFade);
	}
	else if (myBlackAlpha < 0 || myTimer > aTimeToFade)
	{
		myTimer = 0;
		return true;
	}
	myBlackScreen->SetColor(Vector4f(0, 0, 0, myBlackAlpha));
	return false;
}
//aTimeToFade in seconds.
bool TestIntroState::FadeOut(float aTimeToFade, float aDeltatime)
{

	myTimer += aDeltatime;
	if (aTimeToFade > myTimer && myBlackAlpha <= 1)
	{
		myBlackAlpha += (aDeltatime / aTimeToFade);
	}
	if (myBlackAlpha >= 1 || myTimer > aTimeToFade)
	{
		myTimer = 0;
		return true;
	}
	myBlackScreen->SetColor(Vector4f(0, 0, 0, myBlackAlpha));
	return false;
}


TestIntroState::~TestIntroState()
{

}

void TestIntroState::Update(const float aDeltaTime)
{

	switch (myCurrentScene)
	{
	case eScenes::Scene1:
		Scene1(aDeltaTime);
		break;
	case eScenes::Scene2:
		Scene2(aDeltaTime);
		break;
	case eScenes::Scene3:
		break;
	default:
		break;
	}
	CheckForInput();
	MouseInput::Update();
	CollisionManager::Update();

}

void TestIntroState::CheckForInput()
{
	if (CU::InputWrapper::GetKeyDown((DIK_SPACE)) == true)
	{
		LoadScene2();
		myCurrentScene = eScenes::Scene2;
	}
}

//Så hårdkodat så det är galet

void TestIntroState::LoadScene1()
{
	myScene1Background1->SetPivot(Vector2f(0.0f, 0.0f));
	myScene1Background2->SetPivot(Vector2f(0.0f, 0.0f));
	myScene1BadGuys->SetPivot(Vector2f(0.0f, 0.0f));

	myScene1Background1->SetPosition(Vector2f(1030, 840));
	myScene1Background2->SetPosition(Vector2f(400, 200));
	myScene1BadGuys->SetPosition(Vector2f(1400, 750));

	for (unsigned short i = 0; i < myGameObjectArray.Size(); i++)
	{
		myGameObjectArray[i]->SetPivot(Vector2f(0.0f, 0.0f));
		myGameObjectArray[i]->SetPosition(Vector2f(1400, 750));
	}
}

void TestIntroState::LoadScene2()
{
	myMainCharacter->SetPivot(Vector2f(0.5f, 0.5f));
	myScene2BadGuys->SetPivot(Vector2f(0.5f, 0.5f));
	myScene2Prop1->SetPivot(Vector2f(0.5f, 0.5f));

	myMainCharacter->SetPosition(Vector2f(950, 500));
	myScene2BadGuys->SetPosition(Vector2f(950, 800));
	myScene2Prop1->SetPosition(Vector2f(850.f, 400.f));
	myScene2BadGuys->SetSize(Vector2f(1.2f, 1.2f));
}
void TestIntroState::Scene1(float aDeltaTime)
{
	//myMainBackground->SetPosition(Vector2f(myMainBackground->GetPosition().x - aDeltaTime * 2, myMainBackground->GetPosition().y));
	//myScene1Background2->SetPosition(Vector2f(myScene1Background2->GetPosition().x - aDeltaTime * 2, myScene1Background2->GetPosition().y));
	//myScene1Background1->SetPosition(Vector2f(myScene1Background1->GetPosition().x - aDeltaTime * 2, myScene1Background1->GetPosition().y));
	myTimer += aDeltaTime;

	myExitButton.Update(aDeltaTime);

	//Simon får förklara collision-click-trigger för mig sen.
	if (CommonUtilities::InputWrapper::GetMouseButtonPressed(CommonUtilities::enumMouseButtons::eRight) &&
		MouseFix::GetFixedMousePosition().x > (myPlayButton.GetPosition().x - 128) && MouseFix::GetFixedMousePosition().x < ((myPlayButton.GetPosition().x) + 128.f) &&
		MouseFix::GetFixedMousePosition().y >(myPlayButton.GetPosition().y - 128) && (MouseFix::GetFixedMousePosition().y) < (myPlayButton.GetPosition().y))
	{
		myIntro1 = true;
	}
	if (myIntro1 == true)
	{

		if ((FadeOut(3, aDeltaTime) == true))
		{
			myIntro1 = false;
			LoadScene2();
			myCurrentScene = eScenes::Scene2;
		}
	}
	//myPlayButton.Update(aDeltaTime);
	if (myTimer > 1.7f)
	{
		myScene1BadGuys2 = FactoryGameObject::CreateObject<BaseGameObject>();
		myScene1BadGuys2->LoadSprite("Sprites/Levels/Intro/soldiers.png");
		myScene1BadGuys2->SetColor(Vector4f(0, 0, 0, 0));
		myGameObjectArray.Add(myScene1BadGuys2);
		myScene1BadGuys2->SetPivot(Vector2f(0.0f, 0.0f));
		myScene1BadGuys2->SetPosition(Vector2f(1400, 750));
		myTimer = 0;
	}

	for (unsigned short i = 0; i < myGameObjectArray.Size(); i++)
	{
		//myGameObjectArray[i]->SetPosition(Vector2f(myGameObjectArray[i]->GetPosition().x - aDeltaTime * 35, myGameObjectArray[i]->GetPosition().y - aDeltaTime * 10));;

		if (myGameObjectArray[i]->GetPosition().x > 1200.f)
		{
			myGameObjectArray[i]->SetSize(Vector2f(myGameObjectArray[i]->GetSize().x - aDeltaTime / 20, myGameObjectArray[i]->GetSize().y - aDeltaTime / 20));
			myGameObjectArray[i]->SetColor(Vector4f(0, 0, 0, myGameObjectArray[i]->GetColor().w + aDeltaTime / 5));
			myGameObjectArray[i]->SetPosition(Vector2f(myGameObjectArray[i]->GetPosition().x - aDeltaTime * 35, myGameObjectArray[i]->GetPosition().y - aDeltaTime * 10));
		}
		if (myGameObjectArray[i]->GetPosition().x <= 1200.f)
		{
			myGameObjectArray[i]->SetPosition(Vector2f(myGameObjectArray[i]->GetPosition().x - aDeltaTime * 15, myGameObjectArray[i]->GetPosition().y + aDeltaTime * 15));
			myGameObjectArray[i]->SetSize(Vector2f(myGameObjectArray[i]->GetSize().x - aDeltaTime / 20, myGameObjectArray[i]->GetSize().y - aDeltaTime / 20));
		}
		if (myGameObjectArray[i]->GetPosition().x <= 1100.f)
		{
			//myGameObjectArray[i]->SetPosition(Vector2f(myGameObjectArray[i]->GetPosition().x - aDeltaTime, myGameObjectArray[i]->GetPosition().y));
			myGameObjectArray[i]->SetColor(Vector4f(0, 0, 0, myGameObjectArray[i]->GetColor().w - aDeltaTime / 4));
		}
		if (myGameObjectArray[i]->GetPosition().x <= 1000.f)
		{
			myGameObjectArray.RemoveCyclicAtIndex(i);
		}
	}
	//if (myScene1BadGuys->GetPosition().x > 1200.f)
	//{
	//	myScene1BadGuys->SetSize(Vector2f(myScene1BadGuys->GetSize().x - aDeltaTime / 20, myScene1BadGuys->GetSize().y - aDeltaTime / 20));
	//	myScene1BadGuys->SetColor(Vector4f(0, 0, 0, myScene1BadGuys->GetColor().w + aDeltaTime / 5));
	//	myScene1BadGuys->SetPosition(Vector2f(myScene1BadGuys->GetPosition().x - aDeltaTime * 35, myScene1BadGuys->GetPosition().y - aDeltaTime * 10));
	//}
	//if (myScene1BadGuys->GetPosition().x <= 1200.f)
	//{

	//	myScene1BadGuys->SetPosition(Vector2f(myScene1BadGuys->GetPosition().x - aDeltaTime * 25, myScene1BadGuys->GetPosition().y + aDeltaTime * 15));
	//	myScene1BadGuys->SetSize(Vector2f(myScene1BadGuys->GetSize().x - aDeltaTime / 20, myScene1BadGuys->GetSize().y - aDeltaTime / 20));
	//}
	//if (myScene1BadGuys->GetPosition().x <= 1100.f)
	//{
	//	myScene1BadGuys->SetColor(Vector4f(0, 0, 0, myScene1BadGuys->GetColor().w - aDeltaTime / 4));
	//}
}
void TestIntroState::Scene2(float aDeltaTime)
{

	if ((FadeIn(3, aDeltaTime) == true) && myIntro2 != true)
	{		
		myIntro2 = true;
		std::cout << "myIntro2 = true" << std::endl;
	}
	if (myIntro2 == true)
	{
		if (FadeOut(4, 0.09f) == true)
		{
				StateManager::SetActiveState(enumGameStates::eTestMainLoop);	
		}
	}

	


	myMainBackground->SetPosition(Vector2f(myMainBackground->GetPosition().x - aDeltaTime * 2, myMainBackground->GetPosition().y));
	myMainCharacter->SetPosition(Vector2f(myMainCharacter->GetPosition().x + aDeltaTime * 3, myMainCharacter->GetPosition().y));
	myScene2BadGuys->SetPosition(Vector2f(myScene2BadGuys->GetPosition().x + aDeltaTime * 10, myScene2BadGuys->GetPosition().y));
	//myScene2BadGuys->SetColor(Vector4f(0, 0, 0, 1.f));

	myScene2Prop1->SetPosition(Vector2f(myScene2Prop1->GetPosition().x + aDeltaTime * 3, myScene2Prop1->GetPosition().y));

	myScene2Prop1->SetRotation(myScene2Prop1->GetRotation() + aDeltaTime);
	myScene2BadGuys->SetSize(Vector2f(2.2f, 2.2f));
	if (myScene2BadGuys->GetSize().x >= 1)
	{
		myScene2BadGuys->SetColor(Vector4f(0, 0, 0, myScene2BadGuys->GetColor().w + (aDeltaTime / 5)));
		myScene2BadGuys->SetSize(Vector2f(myScene2BadGuys->GetSize().x - aDeltaTime / 20, myScene2BadGuys->GetSize().y - aDeltaTime / 20));
	}

	//if (myIntro2 == true)
	//{
	//	
	//	if (Delay(2, aDeltaTime))
	//	{
	//		StateManager::SetActiveState(enumGameStates::eTestMainLoop);
	//	}
	//}
}

void TestIntroState::Draw() const
{
	myMainBackground->Draw();

	switch (myCurrentScene)
	{
	case eScenes::Scene1:

		myScene1Background2->Draw();
		for (unsigned short i = 0; i < myGameObjectArray.Size(); i++)
		{
			myGameObjectArray[i]->Draw();
		}
		myScene1BadGuys->Draw();
		myScene1Background1->Draw();
		myPlayButton.Draw();
		myCreditsButton->Draw();
		myExitButton.Draw();

		break;
	case eScenes::Scene2:
		myMainCharacter->Draw();
		myScene2BadGuys->Draw();
		myScene2Prop1->Draw();
		break;
	case eScenes::Scene3:
		break;
	default:
		break;
	}

	myBlackScreen->Draw();

	MouseInput::Draw();

}

