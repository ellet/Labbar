#include "stdafx.h"
#include "TestState.h"
#include <CollisionManager/CollisionManager.h>
#include <RendererManager/Commands/Text/RenderText.h>
#include <RendererManager/RenderManager.h>

#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/engine.h>

#include <sstream>

const size_t LineAmount = 3;

TestState::TestState()
{
}


TestState::~TestState()
{
}

void TestState::Init()
{
	myBallCount = 0;
	mySpawnTimer.SetAlarmTimeLength(0.1f);
	mySpawnTimer.SetResetBool(true);

	myLines.Init(3);

	myLines.Add(new StudsiStudsiLinje(Vector2f(100.f, 100.f), Vector2f(550.f, 100.f)));
	myLines.Add(new StudsiStudsiLinje(Vector2f(550.f, 100.f), Vector2f(550.f, 550.f)));
	myLines.Add(new StudsiStudsiLinje(Vector2f(550.f, 550.f), Vector2f(100.f, 550.f)));
	myLines.Add(new StudsiStudsiLinje(Vector2f(100.f, 550.f), Vector2f(100.f, 100.f)));

	myRandomizerPosX.SetMinMax(250.f, 300.f);
	myRandomizerPosY.SetMinMax(150.f, 200.f);
	myRandomizerSpeed.SetMinMax(-500.f, 500.f);

	myBallz.Init(100);
	for (unsigned int i = 0; i < 0; ++i)
	{
		SpawnBall();
	}

	myText = myText = new DX2D::CText("Text/calibril.ttf_sdf");
	myText->myText = "Hello future";
	myText->myPosition = DX2D::Vector2f(0.1f, 0.15f);


	//myLine.Init(Vector2f(50.f, 50.f), Vector2f(50.f, 250.f));
}

void TestState::Update(const float aDeltaTime)
{
	if (mySpawnTimer.GetProgress() >= 1.f)
	{
		SpawnBall();
	}

	for (unsigned short i = 0; i < myLines.Size(); ++i)
	{
		myLines[i]->Update(aDeltaTime);
	}

	for (unsigned short i = 0; i < myBallz.Size(); ++i)
	{
		myBallz[i]->Update(aDeltaTime);
	}

	CollisionManager::Update();
}

void TestState::Draw() const
{
	
	for (unsigned short i = 0; i < myLines.Size(); ++i)
	{
		myLines[i]->Draw();
	}
	for (unsigned short i = 0; i < myBallz.Size(); ++i)
	{
		myBallz[i]->Draw();
	}

	myText->Render();
}

void TestState::DoOnChangeFrom()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void TestState::DoOnChangeTo()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void TestState::SpawnBall()
{
	TestObject * ball = new TestObject();
	ball->Init(Vector2f(myRandomizerPosX.GetRandomValue(), myRandomizerPosY.GetRandomValue()), Vector2f(myRandomizerSpeed.GetRandomValue(), myRandomizerSpeed.GetRandomValue()));
	myBallz.Add(ball);
	++myBallCount;

	std::stringstream temp;

	temp << myBallCount;

	myText->myText = temp.str();
}
